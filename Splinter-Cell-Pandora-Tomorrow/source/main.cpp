#include "main.h"

/*
Game: Splinter Cell: Pandora Tomorrow
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x55530019
Signature Key: 0D5B5C7E20F73FF9C24EC23B9A66B341
*/

//checks and markers
#define SG_FILE_SIZE 0x2625A0
#define OFFLINE_PRF_MIN_FILE_SIZE 0x16
#define ONLINE_PRF_MIN_FILE_SIZE 0x18

#define OFFLINE_PRF_MAGIC "UBIShanghai" //unicode (LE)
#define OFFLINE_PRF_MAGIC_LEN 11

#define FILETYPE_UNSET 0
#define FILETYPE_SG 1
#define FILETYPE_OFFLINE_PRF 2
#define FILETYPE_ONLINE_PRF 3

int main(int argc, char* argv[]) {

	PrintInfo();

	//per-title key
	const byte TitleSignatureKey[] = { 
		0x0D, 0x5B, 0x5C, 0x7E, 0x20, 0xF7, 0x3F, 0xF9, 0xC2, 0x4E, 0xC2, 0x3B, 0x9A, 0x66, 0xB3, 0x41 
	};

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

	u32 file_type = FILETYPE_UNSET;

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

	//check file
	file_size = GetFileSize(file);

	if (file_size == 0) {

		printf("Error: Failed to access file \"%s\"", file);
		goto exit;
	}

	//title specific file size check
	if (file_size != SG_FILE_SIZE && file_size <= OFFLINE_PRF_MIN_FILE_SIZE && file_size <= ONLINE_PRF_MIN_FILE_SIZE) {
		printf("Error: Invalid file size \"%s\"", file);
		goto exit;
	}

	if (file_size == SG_FILE_SIZE)
		file_type = FILETYPE_SG;

	//--- file input / allocation begins ---

	file_buffer = new byte[file_size];
	
	if ((file_handle = OpenFile(file, FILEMODE_READWRITE)) == NULL) {

		printf("Error: Failed to open file \"%s\"", file);
		goto free_and_exit;
	}

	if (ReadBytes(file_handle, 0, file_size, file_buffer) != file_size) {

		printf("Error: Failed to read file \"%s\"", file);
		goto free_and_exit;
	}

	//title specific file check
	if (file_type == FILETYPE_UNSET) {

		bool32 valid_magic = true;
		for (u32 i = 0; i < OFFLINE_PRF_MAGIC_LEN; i++) {

			if (file_buffer[i * 2] != OFFLINE_PRF_MAGIC[i]) {

				valid_magic = false;
				break;
			}

		}

		if (valid_magic) {

			file_type = FILETYPE_OFFLINE_PRF;
		}
		else {

			u32 internal_file_size = *(u32*)(file_buffer + XCalculateSignatureGetSize(signature_type));

			if ((internal_file_size + XCalculateSignatureGetSize(signature_type) + 4) == file_size) // + signature size + u32
				file_type = FILETYPE_ONLINE_PRF;

		}

	}

	if (file_type == FILETYPE_UNSET) {

		printf("Error: Cannot determine file type \"%s\"", file);
		goto free_and_exit;
	}

	//title specific signature offset/data area

	if (file_type == FILETYPE_SG || file_type == FILETYPE_OFFLINE_PRF) {

		signature_offset = (file_size - XCalculateSignatureGetSize(signature_type));
		signature_area_start = 0;
		signature_area_size = (file_size - XCalculateSignatureGetSize(signature_type));

	}
	else {

		signature_offset = 0;
		signature_area_start = XCalculateSignatureGetSize(signature_type);
		signature_area_size = (file_size - XCalculateSignatureGetSize(signature_type));

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