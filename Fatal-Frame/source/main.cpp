#include "main.h"

/*
Game: Fatal Frame / Project ZERO
Region: NTSC-U / PAL
TitleID: 0x54430004 / 0x4D530059
Signature Key: BD1E1C7B4DB4BA8D49E37EA24F80F14E / 0D07E43488A315BF1BDC3B47E0B46B24
*/

#define XBOXHDKEY_BYTE_SIZE 0x10
#define XBOXHDKEY_TEXT_SIZE 32

#define SAVE_FILE_SIZE 0x2945CC0 //absurd

//blocks
#define FIRST_BLOCK_SIZE 0x5414
#define SECONDARY_BLOCK_SIZE 0x60000
#define SECONDARY_BLOCK_COUNT 0x6E

#define GAME_UNKNOWN		0
#define GAME_FATAL_FRAME	1 //NTSC-U
#define GAME_PROJECT_ZERO	2 //PAL
//#define GAME_ZERO			3 //NTSC-J (unsupported for now)

int main(int argc, char* argv[]) {

	PrintInfo();

	//per-title key
	const byte FF_TitleSignatureKey[] = { 0xBD, 0x1E, 0x1C, 0x7B, 0x4D, 0xB4, 0xBA, 0x8D, 0x49, 0xE3, 0x7E, 0xA2, 0x4F, 0x80, 0xF1, 0x4E }; //Fatal Frame
	const byte PZ_TitleSignatureKey[] = { 0x0D, 0x07, 0xE4, 0x34, 0x88, 0xA3, 0x15, 0xBF, 0x1B, 0xDC, 0x3B, 0x47, 0xE0, 0xB4, 0x6B, 0x24 }; //Project ZERO
	//const byte Z_TitleSignatureKey[] = {  }; //ZERO

	u32 file_size = 0;
	utf8* file = 0;
	byte* file_buffer = 0;
	FILE* file_handle = 0;

	byte* TitleSignatureKey = 0;
	byte* XboxHDKey = 0;
	utf8* XboxHDKey_string = 0;
	u32 game_version = GAME_UNKNOWN;

	u32 block_offset = 0;
	u32 block_size = 0;
	u32 block_signature_size = XCalculateSignatureGetSize(XCALCSIG_FLAG_NON_ROAMABLE);

	//check args
	if (argc != 4) {

		printf("\nError: Invalid number of arguments provided\n");
		PrintUsage();
		goto exit;
	}

	if (!strcmp8((utf8*)argv[1], (utf8*)"na", 2) && !strcmp8((utf8*)argv[1], (utf8*)"pal", 3)) {

		printf("\nError: Invalid region specified\n");
		PrintUsage();
		goto exit;
	}

	if (!(argv[2])) {

		printf("\nError: XboxHDKey not specified\n");
		PrintUsage();
		goto exit;
	}

	if (!(argv[3])) {

		printf("\nError: File not specified\n");
		PrintUsage();
		goto exit;
	}

	//pull out args
	game_version = (strcmp8((utf8*)argv[1], (utf8*)"na", 2) ? GAME_FATAL_FRAME : GAME_PROJECT_ZERO); //TODO: Fix to support jp
	XboxHDKey_string = (utf8*)argv[2];
	file = (utf8*)argv[3];

	//--- file input / allocation begins ---

	XboxHDKey = new byte[XBOXHDKEY_BYTE_SIZE];
	if (!CheckXboxHDKey(XboxHDKey_string, XboxHDKey)) {

		printf("\nError: Invalid XboxHDKey. Expect 32 character hexadecimal string\n");
		goto free_and_exit;
	}

	//check file
	file_size = GetFileSize(file);

	if (file_size == 0) {

		printf("\nError: Failed to access file \"%s\"\n", file);
		goto free_and_exit;
	}

	if (file_size != SAVE_FILE_SIZE) {

		printf("\nError: Invalid file size \"%s\"\n", file);
		goto free_and_exit;
	}

	file_buffer = new byte[file_size];

	if ((file_handle = OpenFile(file, FILEMODE_READWRITE)) == NULL) {

		printf("\nError: Failed to open file \"%s\"\n", file);
		goto free_and_exit;
	}

	if (ReadBytes(file_handle, 0, file_size, file_buffer) != file_size) {

		printf("\nError: Failed to read file \"%s\"\n", file);
		goto free_and_exit;
	}

	//--- data manipulation begins ---

	//do hashing/checksuming/signing

	TitleSignatureKey = (byte*)(game_version == GAME_FATAL_FRAME ? FF_TitleSignatureKey : PZ_TitleSignatureKey); //TODO: Fix to support jp
	block_offset = 0;
	block_size = FIRST_BLOCK_SIZE;

	if (!SignBlock((file_buffer + block_offset), block_size, TitleSignatureKey, XboxHDKey))
		goto free_and_exit;

	block_offset = (FIRST_BLOCK_SIZE + block_signature_size);
	block_size = SECONDARY_BLOCK_SIZE;

	for (u32 i = 0; i < SECONDARY_BLOCK_COUNT; i++) {

		if (!SignBlock((file_buffer + block_offset), block_size, TitleSignatureKey, XboxHDKey))
			goto free_and_exit;

		block_offset += (SECONDARY_BLOCK_SIZE + block_signature_size);
	}


	//--- file output ---

	if (WriteBytes(file_handle, 0, file_size, file_buffer) != file_size) {

		printf("\nError: Failed to write file \"%s\"\n", file);
		goto free_and_exit;
	}

	CloseFile(file_handle);

	printf("\n\nSigned %d blocks. File signed successfully", SECONDARY_BLOCK_COUNT + 1);


free_and_exit:

	if (XboxHDKey)
		delete[] XboxHDKey;

	if (file_buffer)
		delete[] file_buffer;

	if (file_handle)
		CloseFile(file_handle);

exit:
	return 0;
}

void PrintInfo() {
	printf("\nXbox Gamesave Signing Tool (%s)\n\n", INFO_BUILD_DATE);
	printf("---------------------------------------\n");
	printf("Game(s)         : %s\n", INFO_GAME_NAME);
	printf("TitleID(s)      : %s\n", INFO_TITLE_ID);
	printf("Region(s)       : %s\n\n", INFO_SUPPORTED_REGIONS);
	printf("%s\n", INFO_URL);
	printf("---------------------------------------\n\n");
}

void PrintUsage() {
	printf("\nUsage: %s\n", INFO_USAGE);
}

void PrintHex(byte* buffer, u32 length, bool newLine) {

	if (buffer && length > 0) {

		u32 string_length = HexLenFromByteCount(length, true);
		utf8* string = new utf8[string_length];
		BytesToHex(buffer, length, string);
		string[string_length - 1] = '\0';

		printf("%s", string);
		if (newLine)
			printf("\n");

		delete[] string;
	}

}

bool CheckXboxHDKey(utf8* input_XboxHDKey_string, byte* output_XboxHDKey_bytes) {

	if (input_XboxHDKey_string && output_XboxHDKey_bytes) {

		u32 num_bytes = ByteCountFromHexLen(input_XboxHDKey_string);
		if (num_bytes != XBOXHDKEY_BYTE_SIZE)
			return false;

		return HexToBytes(input_XboxHDKey_string, XBOXHDKEY_TEXT_SIZE, output_XboxHDKey_bytes);

	}

	return false;

}

bool SignBlock(byte* block, u32 block_size, byte* TitleSignatureKey, byte* XboxHDKey) {

	bool result = false;

	if (block && block_size > 0 && TitleSignatureKey && XboxHDKey) {

		u32 signature_size = XCalculateSignatureGetSize(XCALCSIG_FLAG_NON_ROAMABLE);
		byte* signature = new byte[signature_size];

		XCALCSIG_CONTEXT* context = XCalculateSignatureBegin(XCALCSIG_FLAG_NON_ROAMABLE, TitleSignatureKey, XboxHDKey);
		if (context) {

			if (XCalculateSignatureUpdate(context, block, block_size) == XCALCSIG_SUCCESS) {

				if (XCalculateSignatureEnd(context, signature) == XCALCSIG_SUCCESS) {

					printf("\nCurrent   : ");
					PrintHex((block + block_size), signature_size, true);
					printf("Calculated: ");
					PrintHex(signature, signature_size, true);

					copy((block + block_size), signature, signature_size);
					result = true;
				} 
				else { printf("\nError: Failed to finalize hash\n"); }
			} 
			else { printf("\nError: Failed to update hash\n"); }
		}
		else { printf("\nError: Failed to initialize XCALCSIG context\n"); }

		delete[] signature;
	}

	return result;
}