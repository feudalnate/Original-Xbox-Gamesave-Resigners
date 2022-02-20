#include "main.h"
#include <stdio.h>

/*
Game: Armed & Dangerous
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x4C41000D
Signature Key: 2B6E33422A6AEC5A41E4A77E6882201A
*/

/*
"options.opt" file format

-------------------------------------------------------------------------------------------------
| Offset  | Length | Data type | Description                                                    |
-------------------------------------------------------------------------------------------------
| 0x0     | 0x14   | byte      | Non-roamable signature (HMAC-SHA1) (covers 0x18-EOF)           |
| 0x14    | 0x4    | uint32    | Decompressed file size                                         |
| 0x18    | 0x2    | byte      | ZLIB magic/flag (0x78 0xDA) (BEST_COMPRESSION)                 |
| 0x1A    | ???    | byte      | Compressed data, end of compressed data marked with null byte  |
| EOF-0x4 | 0x4    | uint32    | Adler32 checksum of decompressed data                          |
-------------------------------------------------------------------------------------------------

Note: "Decompressed file size" isn't covered by the Non-roamable signature (for some reason)
*/

int main(int argc, char* argv[]) {

	PrintInfo();

	//per-title key
	const byte TitleSignatureKey[] = { 0x2B, 0x6E, 0x33, 0x42, 0x2A, 0x6A, 0xEC, 0x5A, 0x41, 0xE4, 0xA7, 0x7E, 0x68, 0x82, 0x20, 0x1A };

	//variables
	utf8* key = 0;
	u32 key_length = 32;
	u32 key_byte_count;
	byte* XboxHDKey = 0;

	utf8* file = 0;
	u32 file_size;
	byte* file_buffer = 0;
	FILE* file_handle = 0;

	XCALCSIG_CONTEXT* context = 0;
	u32 signature_size;
	byte* signature = 0;

	u32 signature_offset;
	u32 signature_area_start;
	u32 signature_area_size;


	//check args
	if (argc != 3) {

		printf("Error: Invalid number of arguments provided");
		PrintUsage();
		goto exit;
	}

	if (!(argv[1])) {

		printf("Error: XboxHDKey not specified");
		PrintUsage();
		goto exit;
	}

	if (!(argv[2])) {

		printf("Error: File not specified");
		PrintUsage();
		goto exit;
	}

	//pull out args
	key = (utf8*)argv[1];
	file = (utf8*)argv[2];

	//check XboxHDKey
	key_byte_count = ByteCountFromHexLen(key);

	if (key_byte_count != 0x10) {

		printf("Error: XboxHDKey specified is incorrect length. Expect 32 characters");
		goto exit;
	}

	if (!ValidHex(key, key_length)) {

		printf("Error: XboxHDKey specified contains invalid hexadecimal characters");
		goto exit;
	}

	//--- file input / allocation begins ---

	XboxHDKey = new byte[key_byte_count];

	if (!HexToBytes(key, key_length, XboxHDKey)) {

		printf("Error: Failed to convert XboxHDKey hexadecimal string to bytes");
		goto free_and_exit;
	}

	//check file
	file_size = GetFileSize(file);

	if (file_size == 0) {

		printf("Error: Failed to access file \"%s\"", file);
		goto free_and_exit;
	}

	//title specific file size check
	if (file_size <= 0x20) {

		printf("Error: Invalid file \"%s\"", file);
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

	//--- data manipulation begins ---

	//title specific data marker checking
	if ( ( *(u16*)(file_buffer+0x18) ) != 55928) { //check zlib header

		printf("Error: Invalid file \"%s\"", file);
		goto free_and_exit;
	}


	//do hashing/checksuming/signing
	signature_size = XCalculateSignatureGetSize(XCALCSIG_FLAG_NON_ROAMABLE);
	signature = new byte[signature_size];

	context = XCalculateSignatureBegin(XCALCSIG_FLAG_NON_ROAMABLE, (byte*)TitleSignatureKey, XboxHDKey);
	if (!(context)) {

		printf("Error: Failed to initialize XCALCSIG context");
		goto free_and_exit;
	}
	
	//do signature calculation

	//Armed and Dangerous specific
	signature_offset = 0;
	signature_area_start = 0x18;
	signature_area_size = (file_size - signature_area_start);

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