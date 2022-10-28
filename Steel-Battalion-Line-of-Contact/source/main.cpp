#include "main.h"

/*
Game: Steel Battalion: Line of Contact
Region: NTSC-U / PAL / NTSC-J
TitleID: 0x43430009
Signature Key: B91003CEC57E68A99AA961D10DC34C98
*/

int main(int argc, char* argv[]) {

	PrintInfo();

	XCALCSIG_CONTEXT* context = 0;
	byte signature[XCALCSIG_SIGNATURE_SIZE] = { 0 };
	bool success = false;

	utf7* file_path = 0;
	u32 file_size = 0;
	FILE* file_handle = 0;
	byte* file_buffer = 0;

	if (argc != 2) {

		printf("\nError: Invalid number of arguments provided\n");
		PrintUsage();
		goto exit;
	}

	if (!(argv[1])) {

		printf("\nError: File not specified\n");
		PrintUsage();
		goto exit;
	}

	file_path = argv[1];
	file_size = GetFileSize(file_path);

	if (file_size == 0) {

		printf("\nError: Failed to access file \"%s\"\n", file_path);
		goto exit;
	}

	if (file_size <= 0x18) {

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

	if (*(u32*)file_buffer != file_size) {

		printf("\nError: Invalid file \"%s\"\n", file_path);
		goto exit;
	}

	context = XCalculateSignatureBegin(XCALCSIG_FLAG_SAVE_GAME, (byte*)TitleSignatureKey);
	if (context)
		if (XCalculateSignatureUpdate(context, (file_buffer + 0x18), (file_size - 0x18)))
			if (XCalculateSignatureEnd(context, signature))
				success = true;

	if (!success) {

		printf("\nError: Failed to calculate signature\n");
		goto exit;
	}

	printf("\nCurrent   : ");
	PrintHex((file_buffer + 4), XCALCSIG_SIGNATURE_SIZE, true);
	printf("Calculated: ");
	PrintHex(signature, XCALCSIG_SIGNATURE_SIZE, true);

	if (WriteBytes(file_handle, 4, XCALCSIG_SIGNATURE_SIZE, signature) != XCALCSIG_SIGNATURE_SIZE) {

		printf("\nError: Failed to write file \"%s\"\n", file_path);
		goto exit;
	}

	CloseFile(file_handle);

	printf("\n\nFile signed successfully");


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
	printf("TitleID         : %s\n", INFO_TITLE_ID);
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