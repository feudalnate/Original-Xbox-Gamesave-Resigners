#include "main.h"

/*
Game: Half-Life 2
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x45410091
Signature Key: CCB0F5720B1478A0B2C518AB429E7DEA
*/

#define XBOXHDKEY_TEXT_SIZE 32
#define XBOXHDKEY_BYTE_SIZE 16

//title specific file checks/markers
#define JSAV_MAGIC 0x5641534A

int main(int argc, char* argv[]) {

	utf8* file = 0;
	u32 file_size;
	byte* file_buffer = 0;
	FILE* file_handle = 0;
	utf8* XboxHDKey_string;
	byte* XboxHDKey;

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

	if (*(u32*)file_buffer == JSAV_MAGIC) {

		SignJSAV(file_buffer, file_size, XboxHDKey);
	}
	else {

		SignGeneric(file_buffer, file_size, XboxHDKey);
	}

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

exit:
	return 0;
}

void SignJSAV(byte* buffer, u32 buffer_size, byte* XboxHDKey) {

	const byte TitleSignatureKey[] = {
		0xCC, 0xB0, 0xF5, 0x72, 0x0B, 0x14, 0x78, 0xA0, 0xB2, 0xC5, 0x18, 0xAB, 0x42, 0x9E, 0x7D, 0xEA
	};

	u32 block_num = 0;
	u32 block_offset = 0;
	u32 block_size = 0x108F + *(u32*)(buffer + 8); //header size + u32 storing block size

	u32 total_size = block_size; //keep track of total bytes processed, number of additional blocks could be unknown so move through until EOF

	XCALCSIG_CONTEXT* context;
	u32 signature_area = (block_offset + (block_size - 0x14));
	byte* signature = new byte[0x14];

	context = XCalculateSignatureBegin(XCALCSIG_FLAG_NON_ROAMABLE, (byte*)TitleSignatureKey, XboxHDKey);
	if (context) {
		XCalculateSignatureUpdate(context, (buffer + block_offset), signature_area);
		XCalculateSignatureEnd(context, signature);
	}

	printf("Current   : ");
	PrintHex((buffer + block_offset + signature_area), 0x14, true);
	printf("Calculated: ");
	PrintHex(signature, 0x14, true);
	printf("\n");

	memcpy((buffer + block_offset + signature_area), signature, 0x14);

	if (buffer_size == total_size) //it's possible for a save to not contain any additional blocks
		goto exit;
		

	//additional blocks

	while (total_size != buffer_size) {

		//NOTE: The 0x108 bytes of header data is NOT included in any signature calculation

		block_offset += (block_size + 0x108); //0x108 = generic block header size
		block_size = *(u32*)(buffer + (block_offset - 4)); //u32 storing block size
		
		total_size += (0x108 + block_size);

		signature_area = (block_size - 0x14);

		context = XCalculateSignatureBegin(XCALCSIG_FLAG_NON_ROAMABLE, (byte*)TitleSignatureKey, XboxHDKey);
		if (context) {
			XCalculateSignatureUpdate(context, (buffer + block_offset), signature_area);
			XCalculateSignatureEnd(context, signature);
		}

		block_num++;

		printf("Current   : ");
		PrintHex((buffer + block_offset + signature_area), 0x14, true);
		printf("Calculated: ");
		PrintHex(signature, 0x14, true);
		printf("\n");
		
		memcpy((buffer + block_offset + signature_area), signature, 0x14);

	}

exit:
	delete[] signature;
	printf("\nSigned %d block(s). ", (block_num + 1));

}

void SignGeneric(byte* buffer, u32 buffer_size, byte* XboxHDKey) {

	const byte TitleSignatureKey[] = {
		0xCC, 0xB0, 0xF5, 0x72, 0x0B, 0x14, 0x78, 0xA0, 0xB2, 0xC5, 0x18, 0xAB, 0x42, 0x9E, 0x7D, 0xEA
	};

	//standard entire file signing, store signature at EOF-0x14

	byte* signature = new byte[0x14];

	XCALCSIG_CONTEXT* context = XCalculateSignatureBegin(XCALCSIG_FLAG_NON_ROAMABLE, (byte*)TitleSignatureKey, XboxHDKey);
	if (context) {
		XCalculateSignatureUpdate(context, buffer, (buffer_size - 0x14));
		XCalculateSignatureEnd(context, signature);
	}

	printf("Current   : ");
	PrintHex(((buffer + buffer_size) - 0x14), 0x14, true);
	printf("Calculated: ");
	PrintHex(signature, 0x14, true);
	printf("\n");

	memcpy(((buffer + buffer_size) - 0x14), signature, 0x14);

	delete[] signature;
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