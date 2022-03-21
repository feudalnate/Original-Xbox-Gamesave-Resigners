#include "main.h"

/*
Game: Splinter Cell: Chaos Theory (Single Player/Co-op)
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x55530038
Signature Key: EC3283DB375155B3929ED6F1E1C9546F
*/

/*
Game: Splinter Cell: Chaos Theory (Multiplayer)
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x55530041
Signature Key: 6342DD40F83B4728EA822BFD8CB13AC4
*/

//checks and markers
#define SINGLE_MULTI_SAV_FILE_SIZE 0x2625A0
#define SINGLE_MULTI_IMAGE_MAGIC "DDS "
#define SINGLE_MULTI_IMAGE_MAGIC_SIZE 4
#define SINGLE_MULTI_IMAGE_FILE_SIZE 0x8094
#define SINGLE_MULTI_IMAGE_NO_SIG_FILE_SIZE 0x8080
#define PROFILE_FILE_SIZE 0x1934
#define ONLINE_PRF_MIN_FILE_SIZE 0x18


#define FILETYPE_UNSET 0
#define FILETYPE_SP 1
#define FILETYPE_MP 2

int main(int argc, char* argv[]) {

	PrintInfo();

	//per-title key
	const byte SP_TitleSignatureKey[] = { 
		0xEC, 0x32, 0x83, 0xDB, 0x37, 0x51, 0x55, 0xB3, 0x92, 0x9E, 0xD6, 0xF1, 0xE1, 0xC9, 0x54, 0x6F
	};

	const byte MP_TitleSignatureKey[] = {
		0x63, 0x42, 0xDD, 0x40, 0xF8, 0x3B, 0x47, 0x28, 0xEA, 0x82, 0x2B, 0xFD, 0x8C, 0xB1, 0x3A, 0xC4
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
	if (file_size != SINGLE_MULTI_SAV_FILE_SIZE && file_size != SINGLE_MULTI_IMAGE_FILE_SIZE && 
		file_size <= ONLINE_PRF_MIN_FILE_SIZE && file_size != PROFILE_FILE_SIZE) {

		if (file_size == SINGLE_MULTI_IMAGE_NO_SIG_FILE_SIZE) {

			printf("Error: Image file not initialized by the game yet. Signing not needed. \"%s\"", file);
			goto exit;
		}

		printf("Error: Invalid file size \"%s\"", file);
		goto exit;
	}

	if (file_size == SINGLE_MULTI_SAV_FILE_SIZE || file_size == SINGLE_MULTI_IMAGE_FILE_SIZE || file_size == PROFILE_FILE_SIZE) file_type = FILETYPE_SP;
	else file_type = FILETYPE_MP;

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
	if (file_type == FILETYPE_MP) {

		u32 internal_file_size = *(u32*)(file_buffer + XCalculateSignatureGetSize(signature_type));

		if ((internal_file_size + XCalculateSignatureGetSize(signature_type) + 4) != file_size) // + signature size + u32
			file_type = FILETYPE_UNSET;
	}

	if (file_type == FILETYPE_UNSET) {

		printf("Error: Cannot determine file type \"%s\"", file);
		goto free_and_exit;
	}

	//title specific signature offset/data area

	if (file_type == FILETYPE_SP) {

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

	context = XCalculateSignatureBegin(signature_type, (file_type == FILETYPE_SP ? (byte*)SP_TitleSignatureKey : (byte*)MP_TitleSignatureKey));
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