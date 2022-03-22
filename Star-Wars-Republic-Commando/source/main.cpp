#include "main.h"

/*
Game: Star Wars: Republic Commando
Region: NTSC-U / PAL
TitleID: 0x4C410013
Signature Key: 88C3BC25F5BB1DE11F1F6FCE21BF7F74
*/

/*
Game: Star Wars: Republic Commando
Region: NTSC-J
TitleID: 0x4C410019
Signature Key: 54731ABF22F0EA8687AAA6478F4BAAEA
*/

#define XBOXHDKEY_TEXT_SIZE 32
#define XBOXHDKEY_BYTE_SIZE 16

//checks and markers
#define CTS_FILE_SIZE 0xEFFF0
#define CTS_MAGIC_VALUE 0xC1832A9E //NOTE: Unsure if this is a constant. Only examined 2 files. Don't use for now.
#define ZERO 0

/*
	NOTE: For System.ini and User.ini files there is no obvious file markers and file size checks can't be used for these dynamically sized files.

	Layout of these files is as follows:

	0x0 - ?                : Ini content
	(EOF-0x18) - (EOF-0x14): u32 with 0 value (NOT covered by the signature calculation)
	(EOF-0x14) - EOF       : Non-roamable signature

	Best check that can be done is for the null u32 value near the EOF
	...
	will do this check for now but may cause problems for future modders(?) - this isn't great.

	There's the ini sections that can be checked but could affect modding, should avoid a check like this.
*/

int main(int argc, char* argv[]) {

	PrintInfo();

	//per-title key
	const byte TitleSignatureKey[] = { 
		0x88, 0xC3, 0xBC, 0x25, 0xF5, 0xBB, 0x1D, 0xE1, 0x1F, 0x1F, 0x6F, 0xCE, 0x21, 0xBF, 0x7F, 0x74
	};

	const byte JP_TitleSignatureKey[] = {
		0x54, 0x73, 0x1A, 0xBF, 0x22, 0xF0, 0xEA, 0x86, 0x87, 0xAA, 0xA6, 0x47, 0x8F, 0x4B, 0xAA, 0xEA
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

	bool32 Japan = false;

	//check args
	if (argc != 3 && argc != 4) {

		printf("\nError: Invalid number of arguments provided\n");
		PrintUsage();
		goto exit;
	}

	if (argc == 4) {

		if (strcmp((utf7*)argv[1], (utf7*)"jp", 2))
			Japan = true;
		else {
			printf("\nError: Invalid arguments provided\n");
			PrintUsage();
			goto exit;
		}
	}

	if (!(argv[(Japan ? 2 : 1)])) {

		printf("\nError: XboxHDKey not specified\n");
		PrintUsage();
		goto exit;
	}

	if (!(argv[(Japan ? 3 : 2)])) {

		printf("\nError: File not specified\n");
		PrintUsage();
		goto exit;
	}

	//pull out args
	XboxHDKey_string = (utf8*)argv[(Japan ? 2 : 1)];
	file = (utf8*)argv[(Japan ? 3 : 2)];

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

	file_buffer = new byte[file_size];
	
	if ((file_handle = OpenFile(file, FILEMODE_READWRITE)) == NULL) {

		printf("\nError: Failed to open file \"%s\"\n", file);
		goto free_and_exit;
	}

	if (ReadBytes(file_handle, 0, file_size, file_buffer) != file_size) {

		printf("\nError: Failed to read file \"%s\"\n", file);
		goto free_and_exit;
	}

	//title specific file check

	if (file_size != CTS_FILE_SIZE) {

		//.ini files
		if (*(u32*)(file_buffer + (file_size - XCalculateSignatureGetSize(signature_type) - 4)) != ZERO &&
			*(byte*)file_buffer != (byte)'[') { //check for start of ini section denotation

			printf("\nError: Invalid or unknown file \"%s\"\n", file);
			goto free_and_exit;
		}
	}
	/*
	else {
	
		Don't use magic check for now.

		//.cts files
		if (*(u32*)file_buffer != CTS_MAGIC_VALUE) {

			printf("Error: Invalid file \"%s\"", file);
			goto free_and_exit;
		}
		
	}
	*/

	//title specific signature offset/data area
	signature_offset = (file_size - XCalculateSignatureGetSize(signature_type));
	signature_area_start = 0;
	signature_area_size = (file_size - XCalculateSignatureGetSize(signature_type) - 4);

	//--- data manipulation begins ---

	//do hashing/checksuming/signing

	signature_size = XCalculateSignatureGetSize(signature_type);
	signature = new byte[signature_size];

	context = XCalculateSignatureBegin(signature_type, (Japan ? (byte*)JP_TitleSignatureKey : (byte*)TitleSignatureKey), XboxHDKey);
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
	PrintHex((file_buffer + signature_offset), signature_size, true);
	printf("Calculated: ");
	PrintHex(signature, signature_size, true);

	//copy signature into file buffer (could directly copy result into file buffer with XCalculateSignatureEnd instead. leaving it pulled out for now)
	memcpy((file_buffer + signature_offset), signature, signature_size);

	//--- file output ---

	if (WriteBytes(file_handle, 0, file_size, file_buffer) != file_size) {

		printf("\nError: Failed to write file \"%s\"\n", file);
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