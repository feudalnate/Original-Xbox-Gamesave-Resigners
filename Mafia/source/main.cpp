#include "main.h"

/*
Game: Mafia
Region: NTSC-U / PAL
TitleID: 0x54540009
Signature Key: 7F2BFB0822D125B958DAA8E9C640B83D
*/

//per-title key
const byte TitleSignatureKey[] = { 0x7F, 0x2B, 0xFB, 0x08, 0x22, 0xD1, 0x25, 0xB9, 0x58, 0xDA, 0xA8, 0xE9, 0xC6, 0x40, 0xB8, 0x3D };

const u32 known_filename_count = 110;
const char* const known_filenames[known_filename_count] =
{
	"mafia.000", "mafia.005", "mafia.010", "mafia.015",	"mafia.020", "mafia.025", "mafia.030", "mafia.040",	"mafia.045", "mafia.050",
	"mafia.055", "mafia.060", "mafia.065", "mafia.070",	"mafia.075", "mafia.080", "mafia.085", "mafia.090", "mafia.095", "mafia.100",
	"mafia.105", "mafia.110", "mafia.115", "mafia.130", "mafia.131", "mafia.135", "mafia.140", "mafia.145", "mafia.146", "mafia.150",
	"mafia.155", "mafia.160", "mafia.165", "mafia.170", "mafia.185", "mafia.190", "mafia.195", "mafia.197", "mafia.200", "mafia.205",
	"mafia.220", "mafia.223", "mafia.225", "mafia.230", "mafia.235", "mafia.240", "mafia.243", "mafia.245", "mafia.260", "mafia.263",
	"mafia.265", "mafia.270", "mafia.275", "mafia.277", "mafia.280", "mafia.290", "mafia.295", "mafia.310", "mafia.315", "mafia.320",
	"mafia.325", "mafia.330", "mafia.335", "mafia.340", "mafia.345", "mafia.350", "mafia.355", "mafia.360", "mafia.370", "mafia.372",
	"mafia.375", "mafia.380", "mafia.385", "mafia.390", "mafia.405", "mafia.407", "mafia.410", "mafia.415", "mafia.425", "mafia.430",
	"mafia.435", "mafia.440", "mafia.452", "mafia.455", "mafia.460", "mafia.465", "mafia.466", "mafia.470", "mafia.475", "mafia.487",
	"mafia.490", "mafia.495", "mafia.497", "mafia.500", "mafia.505", "mafia.520", "mafia.525", "mafia.530", "mafia.532", "mafia.535",
	"mafia.540", "mafia.550", "mafia.552", "mafia.555", "mafia.557", "mafia.560", "mafia.561", "mafia.570", "mafia.sav", "mr.sav"
};

int main(int argc, char* argv[]) {

	PrintInfo();

	//variables
	utf8* key = 0;
	u32 key_length = 32;
	u32 key_byte_count;
	byte* XboxHDKey = 0;

	utf8* path = 0;
	bool path_is_directory = false;

	u32 found_files_count;
	byte* found_files = 0;
	u32 working_buffer_size = ((2 * 1024) * 1024); //2MB
	byte* working_buffer = 0;

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

		printf("Error: File or directory not specified");
		PrintUsage();
		goto exit;
	}

	//pull out args
	key = (utf8*)argv[1];
	path = (utf8*)argv[2];

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

	if (GetFileAttributesA((LPCSTR)path) & FILE_ATTRIBUTE_DIRECTORY) {

		path_is_directory = true;

		found_files = new byte[MAX_PATH * known_filename_count];
		found_files_count = GetKnownFilesFromDirectory(path, found_files);

		if (found_files_count == 0) {

			printf("Error: No known files found in directory \"%s\"", path);
			goto free_and_exit;
		}

	}

	if (!path_is_directory) {

		if (GetFileSize(path) == 0) {

			printf("Error: Failed to access file \"%s\"", path);
			goto free_and_exit;
		}

	}

	//--- data manipulation begins ---

	working_buffer = new byte[working_buffer_size];

	//do hashing/checksuming/signing
	if (path_is_directory && found_files && found_files_count > 0) {

		u32 signed_files = 0;
		u32 failed_files = 0;
		for (u32 i = 0; i < found_files_count; i++) {

			printf("\nFile      : %s\n", (found_files + (i * MAX_PATH)));
			if (SignFile(XboxHDKey, (utf8*)(found_files + (i * MAX_PATH)), working_buffer, working_buffer_size))
				signed_files++;
			else
				failed_files++;

		}
		
		printf("\n%d/%d known files found\n%d/%d file(s) signed successfully, %d failed", 
			known_filename_count, found_files_count, signed_files, found_files_count, failed_files);

	}
	else if (!path_is_directory) {

		if (SignFile(XboxHDKey, path, working_buffer, working_buffer_size))
			printf("\nFile signed successfully");
	}


free_and_exit:
	if (XboxHDKey)
		delete[] XboxHDKey;

	if (found_files)
		delete[] found_files;

	if (working_buffer)
		delete[] working_buffer;

exit:
	return 0;
}

u32 GetKnownFilesFromDirectory(utf8* directory, byte* memory_block) {

	if (directory && memory_block) {

		//self-note: all this casting.. what are you doing?

		utf8 filepath[MAX_PATH];
		HANDLE search_handle = 0;
		WIN32_FIND_DATAA find_result;

		u32 folder_path_length;
		utf8 folder_path[MAX_PATH];

		folder_path_length = strlen((char*)directory);
		memset((byte*)folder_path, (byte)0, MAX_PATH);

		//trim trailing backslash if any
		if (directory[folder_path_length - 1] == '\\')
			folder_path_length -= 1;
		strncpy((char*)folder_path, (char*)directory, folder_path_length);

		u32 result = 0;
		for (u32 i = 0; i < known_filename_count; i++) {

			memset((byte*)filepath, (byte)0, MAX_PATH);
			sprintf((char*)filepath, "%s\\%s", folder_path, known_filenames[i]);

			if ((search_handle = FindFirstFileA((LPSTR)filepath, &find_result)) != INVALID_HANDLE_VALUE) {

				FindClose(search_handle);
				memcpy((byte*)(memory_block + (result * MAX_PATH)), filepath, MAX_PATH);
				result++;
			}

		}

		return result;
	}

	return 0;
}

bool SignFile(byte* XboxHDKey, utf8* file, byte* working_buffer, u32 working_buffer_length) {

	if (file && working_buffer && working_buffer_length > 0) {

		bool result = false;

		u32 file_size;
		FILE* file_handle;

		XCALCSIG_CONTEXT* context = 0;
		u32 signature_size;
		byte* signature = 0;

		u32 signature_offset;
		u32 signature_area_start;
		u32 signature_area_size;


		if ((file_handle = OpenFile(file, FILEMODE_READWRITE)) == NULL) {

			printf("Error: Failed to open file \"%s\"", file);
			goto free_and_return;
		}

		file_size = GetFileSize(file_handle);

		if (file_size > working_buffer_length) {

			printf("Error: File too large to fit into buffer \"%s\"", file);
			goto free_and_return;
		}

		if (ReadBytes(file_handle, 0, file_size, working_buffer) != file_size) {

			printf("Error: Failed to read file \"%s\"", file);
			goto free_and_return;
		}

		signature_size = XCalculateSignatureGetSize(XCALCSIG_FLAG_NON_ROAMABLE);
		signature = new byte[signature_size];

		context = XCalculateSignatureBegin(XCALCSIG_FLAG_NON_ROAMABLE, (byte*)TitleSignatureKey, XboxHDKey);
		if (!(context)) {

			printf("Error: Failed to initialize XCALCSIG context");
			goto free_and_return;
		}

		//do signature calculation

		//Mafia specific
		signature_offset = (file_size - signature_size) ;
		signature_area_start = 0;
		signature_area_size = (file_size - signature_size);

		if (XCalculateSignatureUpdate(context, (working_buffer + signature_area_start), signature_area_size) != XCALCSIG_SUCCESS) {

			printf("Error: Failed to update hash");
			goto free_and_return;
		}

		if (XCalculateSignatureEnd(context, signature) != XCALCSIG_SUCCESS) {

			printf("Error: Failed to finalize hash");
			goto free_and_return;
		}

		printf("Current   : ");
		PrintHex((working_buffer + signature_offset), signature_size, true);
		printf("Calculated: ");
		PrintHex(signature, signature_size, true);

		//copy signature into file buffer (could directly copy result into file buffer with XCalculateSignatureEnd instead. leaving it pulled out for now)
		memcpy((working_buffer + signature_offset), signature, signature_size);

		//--- file output ---

		if (WriteBytes(file_handle, 0, file_size, working_buffer) != file_size) {

			printf("Error: Failed to write file \"%s\"", file);
		}
		
		result = true;
	
free_and_return:

		if (file_handle) 
			CloseFile(file_handle);

		if (context)
			XCalculateSignatureEnd(context, NULL);

		if (signature)
			delete[] signature;

		return result;
	}

	return false;
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