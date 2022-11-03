#include "main.h"

/*
Game: Gladius
Region: NTSC-U / PAL
TitleID: 0x4C410008
Signature Key: 48A73E2F85CF76F105EE68AC96231B2B
*/

/*

  Internal data block format
  (saves contain one or more data blocks, aligned one after the other until EOF)

 |-----------------------------------------------------------------------------------|
 | Offset | Length | Data Type | Description                                         |
 |-----------------------------------------------------------------------------------|
 | 0x0    | 0x4    | int32     | Size of entire block (including size and hash)      |
 | 0x4    | 0x14   | byte[]    | Block data hash (XAPI roamable signature)           |
 | 0x18   | ???    | byte[]    | Block data start. Length = (block size - 0x18)      |
 |-----------------------------------------------------------------------------------|

*/

int main(int argc, char* argv[]) {

	PrintInfo();

	XCALCSIG_CONTEXT* context = 0;
	byte signature[XCALCSIG_SIGNATURE_SIZE] = { 0 };
	bool signature_result = false;

	utf7* file_path = 0;
	u32 file_size = 0;
	FILE* file_handle = 0;
	byte* file_buffer = 0;
	u32 file_buffer_position = 0;

	s32 block_size = 0;
	byte* block_signature = 0;
	byte* block_data = 0;
	u32 block_data_size = 0;

	u32 total_blocks = 0;
	u32 total_block_size = 0;
	

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

	//check/process blocks
	while (total_block_size != file_size) {

		block_size = *(s32*)(file_buffer + file_buffer_position);

		if (block_size <= 0 || block_size > (s32)file_size || (total_block_size + block_size) > file_size) {

			printf("\nError: Bad file data\n");
			goto exit;
		}

		block_signature = ((file_buffer + file_buffer_position) + 4);
		block_data = ((file_buffer + file_buffer_position) + 0x18);
		block_data_size = (block_size - 0x18);

		signature_result = false;
		context = XCalculateSignatureBegin(XCALCSIG_FLAG_SAVE_GAME, (byte*)TitleSignatureKey);
		if (context)
			if (XCalculateSignatureUpdate(context, block_data, block_data_size))
				if (XCalculateSignatureEnd(context, signature))
					signature_result = true;

		if (!signature_result) {

			printf("\nError: Failed to calculate signature\n");
			goto exit;
		}

		printf("\nBlock #%d", total_blocks);
		printf("\nCurrent   : ");
		PrintHex(block_signature, XCALCSIG_SIGNATURE_SIZE, true);
		printf("Calculated: ");
		PrintHex(signature, XCALCSIG_SIGNATURE_SIZE, true);

		copy(block_signature, signature, XCALCSIG_SIGNATURE_SIZE);

		total_blocks++;
		total_block_size += block_size;
		file_buffer_position += block_size;
	}
	
	if (WriteBytes(file_handle, 0, file_size, file_buffer) != file_size) {

		printf("\nError: Failed to write file \"%s\"\n", file_path);
		goto exit;
	}

	CloseFile(file_handle);

	printf("\n\nSigned %d blocks. File signed successfully", total_blocks);


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