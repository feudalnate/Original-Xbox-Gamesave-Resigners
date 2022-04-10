#include "main.h"

/*
Game: Ninja Gaiden Black
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x5443000D
Signature Key: FC3376488B3E5F00F65A6BDA9209CFE8

Alternate TitleID: 0x5443003 (for importing Ninja Gaiden saves/settings?)
Alternate Signature Key: A50114CA2B7C8198E829E7C937D6FC40 (for importing Ninja Gaiden saves/settings?)

Save file location: \UDATA\5443000D\<SaveID>\saveXXX.dat (replace XXX with 000-999)
Save file size: 0x174A8 (95,400) bytes (static)

Settings file location: \TDATA\5443000D\system.dat
Settings file size: 0x550 (1,360) bytes (static)

*/

#define XBOXHDKEY_TEXT_SIZE 32
#define XBOXHDKEY_BYTE_SIZE 16

//checks and markers
#define SAVE_FILE_SIZE 0x174A8 //includes hash and seed size
#define SETTINGS_FILE_SIZE 0x550 //includes hash and seed size

int main(int argc, char* argv[]) {

	PrintInfo();

	//per-title key
	const byte TitleSignatureKey[] = { 
		0xFC, 0x33, 0x76, 0x48, 0x8B, 0x3E, 0x5F, 0x00, 0xF6, 0x5A, 0x6B, 0xDA, 0x92, 0x09, 0xCF, 0xE8
	};

	utf8* file = 0;
	u32 file_size;
	byte* file_buffer = 0;
	FILE* file_handle = 0;
	utf8* XboxHDKey_string;
	byte* XboxHDKey;

	XCALCSIG_CONTEXT* context = 0;
	u32 signature_size;
	byte* signature = 0;

	//title specific variables
	u32 signature_offset;
	u32 signature_area_start;
	u32 signature_area_size;
	u32 signature_type = XCALCSIG_FLAG_NON_ROAMABLE;

	//check args
	if (argc != 3) {

		printf("Error: Invalid number of arguments provided");
		PrintUsage();
		goto exit;
	}

	if (!(argv[1])) {

		printf("Error: XboxHDKey not specified");
		PrintUsage();
		goto exit;
	}

	if (!(argv[2])) {

		printf("Error: File not specified");
		PrintUsage();
		goto exit;
	}

	//pull out args
	XboxHDKey_string = (utf8*)argv[1];
	file = (utf8*)argv[2];

	//--- file input / allocation begins ---

	//check XboxHDKey
	XboxHDKey = new byte[XBOXHDKEY_BYTE_SIZE];
	if (!CheckXboxHDKey(XboxHDKey_string, XboxHDKey)) {

		//error
		printf("\nError: Invalid XboxHDKey! Expected 32 hexadecimal characters\n");
		goto free_and_exit;
	}

	//check file
	file_size = GetFileSize(file);

	if (file_size == 0) {

		printf("Error: Failed to access file \"%s\"", file);
		goto free_and_exit;
	}

	//title specific file size check
	if (file_size != SAVE_FILE_SIZE && file_size != SETTINGS_FILE_SIZE) {

		printf("Error: Invalid file size \"%s\"", file);
		goto free_and_exit;
	}

	file_buffer = new byte[file_size];
	
	if ((file_handle = OpenFile(file, FILEMODE_READWRITE)) == NULL) {

		printf("Error: Failed to open file \"%s\"", file);
		goto free_and_exit;
	}

	if (ReadBytes(file_handle, 0, file_size, file_buffer) != file_size) {

		printf("Error: Failed to read file \"%s\"", file);
		goto free_and_exit;
	}

	//title specific signature offset/data area
	signature_offset = 0;
	signature_area_start = XCalculateSignatureGetSize(signature_type);
	signature_area_size = (file_size - XCalculateSignatureGetSize(signature_type));

	//--- data manipulation begins ---

	//do hashing/checksuming/signing

	signature_size = XCalculateSignatureGetSize(signature_type);
	signature = new byte[signature_size];

	context = XCalculateSignatureBegin(signature_type, (byte*)TitleSignatureKey, XboxHDKey);
	if (!(context)) {

		printf("Error: Failed to initialize XCALCSIG context");
		goto free_and_exit;
	}
	
	//do signature calculation

	if (XCalculateSignatureUpdate(context, (file_buffer + signature_area_start), signature_area_size) != XCALCSIG_SUCCESS) {

		printf("Error: Failed to update hash");
		goto free_and_exit;
	}

	if (XCalculateSignatureEnd(context, signature) != XCALCSIG_SUCCESS) {

		printf("Error: Failed to finalize hash");
		goto free_and_exit;
	}

	printf("Current   : ");
	PrintHex((file_buffer + signature_offset), signature_size, true);
	printf("Calculated: ");
	PrintHex(signature, signature_size, true);

	//copy signature into file buffer (could directly copy result into file buffer with XCalculateSignatureEnd instead. leaving it pulled out for now)
	memcpy((file_buffer + signature_offset), signature, signature_size);

	//--- file output ---

	if (WriteBytes(file_handle, 0, file_size, file_buffer) != file_size) {

		printf("Error: Failed to write file \"%s\"", file);
		goto free_and_exit;
	}

	CloseFile(file_handle);

	printf("\nFile signed successfully");


free_and_exit:

	if (XboxHDKey)
		delete[] XboxHDKey;

	if (file_buffer)
		delete[] file_buffer;

	if (file_handle)
		CloseFile(file_handle);

	if (signature)
		delete[] signature;

	if (context)
		XCalculateSignatureEnd(context, NULL);

exit:
	return 0;
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

void PrintInfo() {
	printf("\nXbox Gamesave Signing Tool (%s)\n\n", INFO_BUILD_DATE);
	printf("----------------------------------------------\n");
	printf("Game         : %s\n", INFO_GAME_NAME);
	printf("TitleID      : %s\n", INFO_TITLE_ID);
	printf("Region(s)    : %s\n\n", INFO_SUPPORTED_REGIONS);
	printf("%s\n", INFO_URL);
	printf("----------------------------------------------\n\n");
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