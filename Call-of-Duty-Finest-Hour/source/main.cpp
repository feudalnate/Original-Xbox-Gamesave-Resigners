#include "main.h"

/*
Game: Call of Duty: Finest Hour
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x4156002A
Signature Key: 50AFC9B126306875A53A9C4DB8E25A21
*/

int main(int argc, char* argv[]) {

	PrintInfo();

	//per-title key
	const byte TitleSignatureKey[] = { 0x50, 0xAF, 0xC9, 0xB1, 0x26, 0x30, 0x68, 0x75, 0xA5, 0x3A, 0x9C, 0x4D, 0xB8, 0xE2, 0x5A, 0x21 };

	utf8* file = 0;
	u32 file_size;
	byte* file_buffer = 0;
	FILE* file_handle = 0;

	XCALCSIG_CONTEXT* context = 0;
	u32 signature_size;
	byte* signature = 0;

	//title specific variables
	u32 signature_offset;
	u32 signature_area_start;
	u32 signature_area_size;
	u32 signature_type = XCALCSIG_FLAG_SAVE_GAME;

	//check args
	if (argc != 2) {

		printf("Error: Invalid number of arguments provided");
		PrintUsage();
		goto exit;
	}

	if (!(argv[1])) {

		printf("Error: File not specified");
		PrintUsage();
		goto exit;
	}

	//pull out args
	file = (utf8*)argv[1];

	//--- file input / allocation begins ---

	//check file
	file_size = GetFileSize(file);

	if (file_size == 0) {

		printf("Error: Failed to access file \"%s\"", file);
		goto free_and_exit;
	}

	//title specific file size check
	if (file_size <= 0x18) { //must be at least signature size + u32 holding file size to even consider reading

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

	//title specific file size check
	signature_offset = 0x4;
	signature_area_start = 0x18;
	signature_area_size = *(u32*)(file_buffer); //internal file size

	if (file_size != (signature_area_size + 0x18)) { //+ signature size + u32

		printf("Error: Invalid file size \"%s\"", file);
		goto free_and_exit;
	}

	//--- data manipulation begins ---

	//do hashing/checksuming/signing

	signature_size = XCalculateSignatureGetSize(signature_type);
	signature = new byte[signature_size];

	context = XCalculateSignatureBegin(signature_type, (byte*)TitleSignatureKey);
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

void PrintInfo() {
	printf("\nXbox Gamesave Signing Tool (%s)\n\n", INFO_BUILD_DATE);
	printf("---------------------------------------\n");
	printf("Game         : %s\n", INFO_GAME_NAME);
	printf("TitleID      : %s\n", INFO_TITLE_ID);
	printf("Region(s)    : %s\n\n", INFO_SUPPORTED_REGIONS);
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