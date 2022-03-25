#include "main.h"

/*
Game: Richard Burns Rally
Region: PAL
TitleID: 0x53430005
Signature Key: BFD9EF83979291CEE2FBB44E03EAD982
*/

#define XBOXHDKEY_TEXT_SIZE 32
#define XBOXHDKEY_BYTE_SIZE 16

//checks and markers
#define RBR_FILE_SIZE 0x26000 //profile file
#define RST_FILE_SIZE 0x4000 //race result file
#define RPL_FILE_SIZE 0xF000 //race replay file
#define TUR_FILE_SIZE 0x14 //signature file

int main(int argc, char* argv[]) {

	PrintInfo();

	//per-title key
	const byte TitleSignatureKey[] = {
		0xBF, 0xD9, 0xEF, 0x83, 0x97, 0x92, 0x91, 0xCE, 0xE2, 0xFB, 0xB4, 0x4E, 0x03, 0xEA, 0xD9, 0x82
	};

	utf8* file = 0;
	u32 file_size;
	byte* file_buffer = 0;
	FILE* file_handle = 0;
	utf8* XboxHDKey_string;
	byte* XboxHDKey = 0;

	XCALCSIG_CONTEXT* context = 0;
	u32 signature_size;
	byte* signature = 0;

	//title specific variables
	u32 signature_offset;
	u32 signature_area_start;
	u32 signature_area_size;
	u32 signature_type = XCALCSIG_FLAG_NON_ROAMABLE;

	//signa.tur file
	utf8* file2 = 0;
	u32 file2_size;
	byte* file2_buffer = 0;
	FILE* file2_handle = 0;

	utf8* directory_path = 0;
	u32 directory_path_length;


	//check args
	if (argc != 3 && argc != 4) {

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

	if (argc == 4) {

		file2 = (utf8*)argv[3];
	}
	else {

		directory_path = new utf8[255];
		memset((byte*)directory_path, 0, 255);

		if (!GetContainingDirectory((utf8*)file, directory_path, directory_path_length, false)) {

			printf("\nError: Failed to retrieve directory path of file\n");
			PrintUsage();
			goto free_and_exit;

		}

		memcpy((byte*)(directory_path + directory_path_length), (byte*)"signa.tur", 9);
		file2 = directory_path;
	}

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

		printf("\nError: Failed to access file \"%s\"", file);
		goto free_and_exit;
	}

	//title specific file check
	if (file_size != RBR_FILE_SIZE &&
		file_size != RPL_FILE_SIZE &&
		file_size != RST_FILE_SIZE)
	{

		printf("\nError: Unknown or invalid file \"%s\"\n", file);
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

	file2_size = GetFileSize(file2);

	if (file2_size != TUR_FILE_SIZE) {

		if ((file2_handle = CreateFile(file2)) == NULL) {

			printf("\nError: Failed to create signature file \"%s\"\n", file2);
			goto free_and_exit;
		}

		file2_buffer = new byte[TUR_FILE_SIZE];
		file2_size = TUR_FILE_SIZE;
		memset(file2_buffer, 0, TUR_FILE_SIZE);
	}
	else {

		if ((file2_handle = OpenFile(file2, FILEMODE_READWRITE)) == NULL) {

			printf("\nError: Failed to open signature file \"%s\"\n", file2);
			goto free_and_exit;
		}

		file2_buffer = new byte[file2_size];

		if (ReadBytes(file2_handle, 0, file2_size, file2_buffer) != file2_size) {

			printf("\nError: Failed to read signature file \"%s\"\n", file2);
			goto free_and_exit;
		}

	}

	//title specific signature offset/data area
	signature_offset = 0;
	signature_area_start = 0;
	signature_area_size = file_size;

	//--- data manipulation begins ---

	//do hashing/checksuming/signing

	signature_size = XCalculateSignatureGetSize(signature_type);
	signature = new byte[signature_size];

	context = XCalculateSignatureBegin(signature_type, (byte*)TitleSignatureKey, XboxHDKey);
	if (!(context)) {

		printf("\nError: Failed to initialize XCALCSIG context\n");
		goto free_and_exit;
	}

	//do signature calculation

	if (XCalculateSignatureUpdate(context, (file_buffer + signature_area_start), signature_area_size) != XCALCSIG_SUCCESS) {

		printf("\nError: Failed to update hash\n");
		goto free_and_exit;
	}

	if (XCalculateSignatureEnd(context, signature) != XCALCSIG_SUCCESS) {

		printf("\nError: Failed to finalize hash\n");
		goto free_and_exit;
	}

	printf("Current   : ");
	PrintHex(file2_buffer, signature_size, true);
	printf("Calculated: ");
	PrintHex(signature, signature_size, true);

	memcpy(file2_buffer, signature, signature_size);

	//--- file output ---

	if (WriteBytes(file2_handle, 0, file2_size, file2_buffer) != file2_size) {

		printf("\nError: Failed to write signature file \"%s\"\n", file2);
		goto free_and_exit;
	}

	CloseFile(file_handle);
	CloseFile(file2_handle);

	printf("\nSignature written to file:\n%s\n\nFile signed successfully", file2);


free_and_exit:

	if (XboxHDKey)
		delete[] XboxHDKey;

	if (file_buffer)
		delete[] file_buffer;

	if (file_handle)
		CloseFile(file_handle);

	if (file2_buffer)
		delete[] file2_buffer;

	if (file2_handle)
		CloseFile(file2_handle);

	if (directory_path)
		delete[] directory_path;

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

bool32 GetContainingDirectory(utf8* in_file_path, utf8* out_directory_path, u32& out_directory_path_length, bool32 trim_trailing_seperator) {

	//walk input until null marker to get string length
	s32 length = 0;
	while (*(u8*)(in_file_path + length) != 0)
		length++;

	//bad input
	if (length == 0)
		return false;

	//walk input backwards until seperator character is reached
	while ((length > -1)) {

		if (*(utf8*)(in_file_path + length) == '\\' ||
			*(utf8*)(in_file_path + length) == '/') { //does the forward slash make sense for Windows?

			if (!trim_trailing_seperator)
				length++;

			break;
		}

		length--;
	}

	if (length <= 0)
		return false;

	memcpy((byte*)out_directory_path, (byte*)in_file_path, length);
	out_directory_path_length = length;

	return true;
}