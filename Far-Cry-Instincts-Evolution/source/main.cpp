#include "main.h"

/*
Game: Far Cry Instincts: Evolution
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x55530060
Signature Key: 79A31342BE08D67E139F395DD4CDFAD6
*/


//checks and markers
const byte MAP_FAT_FILE_MAGIC[] = { 0x44, 0x41, 0x54 }; //'DAT'
const byte MAP_DAT_FILE_MAGIC[] = { 0x43, 0x52, 0x59 }; //'CRY'


int main(int argc, char* argv[]) {

	PrintInfo();

	//per-title key
	const byte TitleSignatureKey[] = {
		0x79, 0xA3, 0x13, 0x42, 0xBE, 0x08, 0xD6, 0x7E, 0x13, 0x9F, 0x39, 0x5D, 0xD4, 0xCD, 0xFA, 0xD6
	};

	bool is_map_data = false;
	bool free_file2_name = false;

	utf8* file = 0;
	u32 file_size;
	byte* file_buffer = 0;
	FILE* file_handle = 0;

	//*.sig file
	utf8* file2 = 0;
	u32 file2_size;
	byte* file2_buffer = 0;
	FILE* file2_handle = 0;


	//check args
	if (argc != 2 && argc != 3) {

		printf("\nError: Invalid number of arguments provided\n");
		PrintUsage();
		goto exit;
	}

	if (!(argv[1])) {

		printf("\nError: File not specified\n");
		PrintUsage();
		goto exit;
	}

	//*.sig file if dealing with map files - not required
	if (argc == 3)
		file2 = (utf8*)argv[2];


	//pull out args
	file = (utf8*)argv[1];

	//--- file input / allocation begins ---

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

	//check if we're dealing with map data
	if (memcmp(file_buffer, (byte*)MAP_DAT_FILE_MAGIC, 3) ||
		memcmp(file_buffer, (byte*)MAP_FAT_FILE_MAGIC, 3))
		is_map_data = true;


	if (is_map_data && file2 != NULL) {

		file2_size = GetFileSize(file2);

		if (file2_size != (XCalculateSignatureGetSize(XCALCSIG_FLAG_SAVE_GAME) * 2)) {

			printf("\nError: Failed to access signature file or incorrect file size\n");
			goto free_and_exit;
		}
	}

	if (is_map_data && file2 == NULL) {

		u32 out_directory_path_len;
		utf8* out_directory_path = new utf8[255];
		memset(out_directory_path, 0, 255);

		u32 out_file_name_len;
		utf8* out_file_name = new utf8[255];
		memset(out_file_name, 0, 255);

		u32 file2_name_buffer_len;
		utf8* file2_name_buffer = new utf8[255];
		memset(file2_name_buffer, 0, 255);

		if (SplitFilePath(file, out_file_name, out_file_name_len, out_directory_path, out_directory_path_len, true)) {

			memcpy((out_file_name + out_file_name_len), (utf8*)".sig", 4);

			if (CombineFilePath(out_directory_path, out_file_name, file2_name_buffer, file2_name_buffer_len)) {

				file2 = file2_name_buffer;
				free_file2_name = true;
			}
			else {

				delete[] file2_name_buffer;
				delete[] out_directory_path;
				delete[] out_file_name;

				printf("\nError: Failed to build signature file filepath. Please specify a signature file\n");
				goto free_and_exit;
			}
		}
		else {

			delete[] file2_name_buffer;
			delete[] out_directory_path;
			delete[] out_file_name;

			printf("\nError: Failed to build signature file filepath. Please specify a signature file\n");
			goto free_and_exit;
		}

		delete[] out_directory_path;
		delete[] out_file_name;
	}

	//--- data manipulation begins ---

	if (is_map_data) { //map signing

		file2_size = GetFileSize(file2);

		if (file2_size != (XCalculateSignatureGetSize(XCALCSIG_FLAG_SAVE_GAME) * 2)) {

			file2_handle = CreateFile(file2);
			file2_size = (XCalculateSignatureGetSize(XCALCSIG_FLAG_SAVE_GAME) * 2);
		}
		else file2_handle = OpenFile(file2, FILEMODE_READWRITE);

		if (!file2_handle) {

			printf("\nError: Failed to open or create signature file \"%s\"\n", file2);
			goto free_and_exit;
		}

		file2_buffer = new byte[(XCalculateSignatureGetSize(XCALCSIG_FLAG_SAVE_GAME) * 2)];
		memset(file2_buffer, 0, (XCalculateSignatureGetSize(XCALCSIG_FLAG_SAVE_GAME) * 2));

		if (!GenerateMapSignature(file_buffer, file_size, (byte*)TitleSignatureKey, file2_buffer)) {

			printf("\nError: Failed to generate map signatures\n");
			goto free_and_exit;
		}

		if (WriteBytes(file2_handle, 0, file2_size, file2_buffer) != file2_size) {

			printf("\nError: Failed to write signature file \"%s\"\n", file2);
			goto free_and_exit;
		}

	}
	else { //generic signing

		printf("Current   : ");
		PrintHex((file_buffer + (file_size - XCalculateSignatureGetSize(XCALCSIG_FLAG_SAVE_GAME))), XCalculateSignatureGetSize(XCALCSIG_FLAG_SAVE_GAME), true);

		if (!GenerateRoamableSignature(
			file_buffer,
			(file_size - XCalculateSignatureGetSize(XCALCSIG_FLAG_SAVE_GAME)),
			(byte*)TitleSignatureKey,
			(file_buffer + (file_size - XCalculateSignatureGetSize(XCALCSIG_FLAG_SAVE_GAME)))
		)) {

			printf("\nError: Failed to generate signature\n");
			goto free_and_exit;
		}

		printf("Calculated: ");
		PrintHex((file_buffer + (file_size - XCalculateSignatureGetSize(XCALCSIG_FLAG_SAVE_GAME))), XCalculateSignatureGetSize(XCALCSIG_FLAG_SAVE_GAME), true);

		if (WriteBytes(file_handle, 0, file_size, file_buffer) != file_size) {

			printf("\nError: Failed to write file \"%s\"\n", file);
			goto free_and_exit;
		}

	}

	printf("\n\nFile signed successfully");

free_and_exit:

	if (file_buffer)
		delete[] file_buffer;

	if (file_handle)
		CloseFile(file_handle);

	if (free_file2_name)
		delete[] file2;

	if (file2_buffer)
		delete[] file2_buffer;

	if (file2_handle)
		CloseFile(file2_handle);

exit:
	return 0;
}

bool GenerateRoamableSignature(byte* buffer, u32 length, byte* TitleSignatureKey, byte* signature) {

	if (buffer && length > 0 && TitleSignatureKey && signature) {

		XCALCSIG_CONTEXT* context = XCalculateSignatureBegin(XCALCSIG_FLAG_SAVE_GAME, TitleSignatureKey);
		if (context) {

			if (XCalculateSignatureUpdate(context, buffer, length)) {

				return XCalculateSignatureEnd(context, signature);
			}
			
			XCalculateSignatureEnd(context, NULL);
		}
	}

	return false;
}

bool GenerateMapSignature(byte* map_data, u32 map_data_len, byte* TitleSignatureKey, byte* signature) {

	//sig file
	//0x0-0x14 - sig file signature
	//0x14-0x28 - dat/fat file signature

	if (map_data && map_data_len > 0 && TitleSignatureKey && signature) {

		u32 signature_size = XCalculateSignatureGetSize(XCALCSIG_FLAG_SAVE_GAME);
		if (GenerateRoamableSignature(map_data, map_data_len, TitleSignatureKey, (signature + signature_size))) {

			return GenerateRoamableSignature((signature + signature_size), signature_size, TitleSignatureKey, signature);
		}
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

bool SplitFilePath(utf8* in_file_path, utf8* out_file_name, u32& out_file_name_length, utf8* out_directory_path, u32& out_directory_path_length, bool trim_trailing_seperator) {

	u32 file_name_start;
	u32 file_name_end;

	//walk input until null marker to get string length
	s32 length = 0;
	while (*(u8*)(in_file_path + length) != 0)
		length++;

	//bad input
	if (length == 0)
		return false;

	file_name_end = length;

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

	if (!trim_trailing_seperator) file_name_start = length;
	else file_name_start = (length + 1);


	memcpy((byte*)out_directory_path, (byte*)in_file_path, length);
	out_directory_path_length = length;

	memcpy((byte*)out_file_name, (byte*)(in_file_path + file_name_start), (file_name_end - file_name_start));
	out_file_name_length = (file_name_end - file_name_start);

	return true;
}

bool CombineFilePath(utf8* in_directory_path, utf8* in_file_name, utf8* out_file_path, u32& out_file_path_length) {

	u32 dir_path_len = 0;
	u32 file_name_len = 0;
	bool dir_path_ends_with_seperator;
	bool file_name_starts_with_seperator;

	while (*(u8*)(in_directory_path + dir_path_len) != 0)
		dir_path_len++;

	if (dir_path_len == 0)
		return false;

	while (*(u8*)(in_file_name + file_name_len) != 0)
		file_name_len++;

	if (file_name_len == 0)
		return false;

	dir_path_ends_with_seperator = (*(u8*)((in_directory_path + dir_path_len) - 1) == '\\');
	file_name_starts_with_seperator = (*(u8*)in_file_name == '\\');

	memcpy(out_file_path, in_directory_path, dir_path_len);

	if (dir_path_ends_with_seperator && file_name_starts_with_seperator) {

		memcpy(((out_file_path + dir_path_len) - 1), in_file_name, file_name_len);
	}
	else if (!dir_path_ends_with_seperator && !file_name_starts_with_seperator) {

		*(u8*)(out_file_path + dir_path_len) = '\\';
		memcpy(((out_file_path + dir_path_len) + 1), in_file_name, file_name_len);
	}
	else {
		
		memcpy((out_file_path + dir_path_len), in_file_name, file_name_len);
	}

	out_file_path_length = 0;

	while (*(u8*)(out_file_path + out_file_path_length) != 0)
		out_file_path_length++;

	return (out_file_path_length > 0);
}