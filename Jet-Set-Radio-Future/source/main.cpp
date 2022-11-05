#include "main.h"

/*
Game: Jet Set Radio Future
Region: NTSC-U / NTSC-J
TitleID: 0x5345000A
Signature Key: E1D4118A91D20D24C0E3BBB16232964D
*/

/*
Game: Jet Set Radio Future
Region: PAL
TitleID: 0x49470018
Signature Key: 074BD1972F7BE074539F82143A722E4F
*/

#define GAMESAVE_FILE_SIZE 0xA080
#define SIGNATURE_OFFSET 0
#define DATA_OFFSET 0x14
#define DATA_LENGTH (GAMESAVE_FILE_SIZE - DATA_OFFSET)

int main(int argc, char* argv[]) {

	PrintInfo();

	XCALCSIG_CONTEXT* context = 0;
	u32 signature_region = 0;
	byte* signature_key = 0;
	byte signature[XCALCSIG_SIGNATURE_SIZE] = { 0 };
	bool signature_result = false;

	utf7* file_path = 0;
	u32 file_size = 0;
	FILE* file_handle = 0;
	byte* file_buffer = 0;

	if (argc != 3) {

		printf("\nError: Invalid number of arguments provided\n");
		PrintUsage();
		goto exit;
	}

	if (!(argv[1])) {

		printf("\nError: Region not specified\n");
		PrintUsage();
		goto exit;
	}

	if (!(argv[2])) {

		printf("\nError: File not specified\n");
		PrintUsage();
		goto exit;
	}

	signature_region = CheckRegionString(argv[1]);
	if (!signature_region) {

		printf("\nError: Invalid region specified\n");
		PrintUsage();
		goto exit;
	}

	signature_key = (byte*)(signature_region == 1 ? TitleSignatureKey : AlternateTitleSignatureKey);

	file_path = argv[2];
	file_size = GetFileSize(file_path);

	if (file_size == 0) {

		printf("\nError: Failed to access file \"%s\"\n", file_path);
		goto exit;
	}

	if (file_size != GAMESAVE_FILE_SIZE) {

		printf("\nError: Invalid file \"%s\"\n", file_path);
		goto exit;
	}

	file_handle = OpenFile(file_path, FILEMODE_READWRITE);
	if (file_handle == NULL) {

		printf("\nError: Failed to access file \"%s\"\n", file_path);
		goto exit;
	}

	file_buffer = new byte[file_size];
	if (ReadBytes(file_handle, 0, file_size, file_buffer) != file_size) {

		printf("\nError: Failed to read file \"%s\"\n", file_path);
		goto exit;
	}

	context = XCalculateSignatureBegin(XCALCSIG_FLAG_SAVE_GAME, signature_key);
	if (context)
		if (XCalculateSignatureUpdate(context, (file_buffer + DATA_OFFSET), DATA_LENGTH))
			if (XCalculateSignatureEnd(context, signature))
				signature_result = true;

	if (!signature_result) {

		printf("\nError: Failed to calculate signature\n");
		goto exit;
	}

	printf("\nCurrent   : ");
	PrintHex((file_buffer + SIGNATURE_OFFSET), XCALCSIG_SIGNATURE_SIZE, true);
	printf("Calculated: ");
	PrintHex(signature, XCALCSIG_SIGNATURE_SIZE, true);

	if (WriteBytes(file_handle, SIGNATURE_OFFSET, XCALCSIG_SIGNATURE_SIZE, signature) != XCALCSIG_SIGNATURE_SIZE) {

		printf("\nError: Failed to write file \"%s\"\n", file_path);
		goto exit;
	}

	CloseFile(file_handle);

	printf("\n\nSigned to %s region. File signed successfully", (signature_region == 1 ? "NTSC-U/J" : "PAL"));


exit:
	if (file_handle)
		CloseFile(file_handle);

	if (file_buffer)
		delete[] file_buffer;

	if (context)
		XCalculateSignatureEnd(context, 0);


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

/// <summary>
/// Check region string. Returns 1 for NTSC, 2 for PAL, 0 on error
/// </summary>
u32 CheckRegionString(char* string) {

	const char NTSCUpper[4] = { 'N', 'T', 'S', 'C' };
	const char NTSCLower[4] = { 'n', 't', 's', 'c' };
	const char PALUpper[3] = { 'P', 'A', 'L' };
	const char PALLower[3] = { 'p', 'a', 'l' };

	if (string) {

		u32 count = strlen7(string);
		if (count > 4 || count < 3)
			return 0;

		if (count == 4) {
			if ((string[0] == NTSCUpper[0] || string[0] == NTSCLower[0]) &&
				(string[1] == NTSCUpper[1] || string[1] == NTSCLower[1]) &&
				(string[2] == NTSCUpper[2] || string[2] == NTSCLower[2]) &&
				(string[3] == NTSCUpper[3] || string[3] == NTSCLower[3]))
				return 1;
		}
		else {
			if ((string[0] == PALUpper[0] || string[0] == PALLower[0]) &&
				(string[1] == PALUpper[1] || string[1] == PALLower[1]) &&
				(string[2] == PALUpper[2] || string[2] == PALLower[2]))
				return 2;
		}
	}

	return 0;
}