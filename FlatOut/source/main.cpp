#include "main.h"

/*
Game: FlatOut
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x454D0009
Signature Key: C8D3C3573CFAD039B9DBB54D742ED579
*/

#define XBOXHDKEY_TEXT_SIZE 32
#define XBOXHDKEY_BYTE_SIZE 16

//title specific file checks/markers
#define SAV_FILE_SIZE 0x2000

int main(int argc, char* argv[]) {

	//per-title key
	const byte TitleSignatureKey[] = { 0xC8, 0xD3, 0xC3, 0x57, 0x3C, 0xFA, 0xD0, 0x39, 0xB9, 0xDB, 0xB5, 0x4D, 0x74, 0x2E, 0xD5, 0x79 };

	utf8* file = 0;
	u32 file_size;
	byte* file_buffer = 0;
	FILE* file_handle = 0;
	utf8* XboxHDKey_string;
	byte* XboxHDKey;

	XCALCSIG_CONTEXT* context = 0;

	//title specific variables
	u32 signature_offset;
	u32 signature_area_start;
	u32 signature_area_length;
	u32 signature_type = XCALCSIG_FLAG_NON_ROAMABLE;
	u32 signature_size = XCalculateSignatureGetSize(signature_type);

	PrintInfo();

	//check args
	if (argc != 3) {

		printf("\nError: Invalid number of arguments provided\n");
		PrintUsage();
		goto exit;
	}

	if (!(argv[1])) {

		printf("\nError: XboxHDKey not specified\n");
		PrintUsage();
		goto exit;
	}

	if (!(argv[2])) {

		printf("\nError: File not specified\n");
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

		printf("\nError: Failed to access file \"%s\"\n", file);
		goto free_and_exit;
	}

	if (file_size != SAV_FILE_SIZE) {

		printf("\nError: Invalid file size \"%s\"\n", file);
		goto free_and_exit;
	}

	file_buffer = new byte[file_size];

	//--- file input ---

	if ((file_handle = OpenFile(file, FILEMODE_READWRITE)) == NULL) {

		printf("\nError: Failed to open file \"%s\"\n", file);
		goto free_and_exit;
	}

	if (ReadBytes(file_handle, 0, file_size, file_buffer) != file_size) {

		printf("\nError: Failed to read file \"%s\"\n", file);
		goto free_and_exit;
	}

	//sign file
	signature_area_start = 0;
	signature_area_length = (file_size - signature_size);
	signature_offset = (file_size - signature_size);

	printf("Current   : ");
	PrintHex((file_buffer + signature_offset), signature_size, true);

	context = XCalculateSignatureBegin(signature_type, (byte*)TitleSignatureKey, XboxHDKey);

	if (context == NULL) {

		printf("\nError: Failed to initialize XCALCSIG context!\n");
		goto free_and_exit;
	}

	if (XCalculateSignatureUpdate(context, (file_buffer + signature_area_start), signature_area_length) != XCALCSIG_SUCCESS) {

		printf("\nError: Failed to update hash!\n");
		goto free_and_exit;
	}

	if (XCalculateSignatureEnd(context, (file_buffer + signature_offset)) != XCALCSIG_SUCCESS) {

		printf("\nError: Failed to finalize hash!\n");
		goto free_and_exit;
	}


	printf("Calculated: ");
	PrintHex((file_buffer + signature_offset), signature_size, true);
	printf("\n");

	//--- file output ---

	if (WriteBytes(file_handle, 0, file_size, file_buffer) != file_size) {

		printf("\nError: Failed to write file \"%s\"\n", file);
		goto free_and_exit;
	}

	CloseFile(file_handle);

	printf("File signed successfully\n");


free_and_exit:

	if (XboxHDKey)
		delete[] XboxHDKey;

	if (file_buffer)
		delete[] file_buffer;

	if (file_handle)
		CloseFile(file_handle);

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