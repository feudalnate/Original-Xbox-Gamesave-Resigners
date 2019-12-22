#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <windows.h>
#include "main.h"
#include "MD5/md5.h"
#include "SHA1/hmac.h"

int main(int argc, char *argv[]) 
{
	SetConsoleTitle(TEXT("Need for Speed: Most Wanted (XBOX) Hash Fix"));

	char* filename;
	FILE* filehandle;
	long filesize;

	printf("Need for Speed: Most Wanted (XBOX)\nHash Fix by feudalnate (March 7th, 2019)\
	\n\nAdditional hash fixes added (May 28th, 2019)\
	\nThanks to github.com/focanmess\
	\n----------------------------------------\n\n");

	//check args
	if (argc != 2)
	{
		printf("Usage: nfsmwfix <input file>");
		goto exit;
	}
	filename = argv[1];

	//check input file exists
	if (_access(filename, 0) == -1)
	{
		printf("Error: File \"%s\" not found", filename);
		goto exit;
	}

	//open file
	filehandle = fopen(filename, "rb+");
	if (filehandle == NULL)
	{
		printf("Error: Could not access the file \"%s\"", filename);
		goto exit;
	}

	//get file size
	fseek(filehandle, 0, SEEK_END);
	filesize = ftell(filehandle);

	//read file into memory
	unsigned char* buffer = (unsigned char*)malloc(filesize);
	rewind(filehandle);
	fread(buffer, 1, filesize, filehandle);

	//load MC02 header info, check magic
	struct MC02Header* header = (struct MC02Header*)buffer;
	if (memcmp(&header->Magic, &Magic, 4) != 0)
	{
		printf("Error: Invalid MC02 file \"%s\"", filename);
		goto exit;
	}

	printf("File: %s\n\nWriting hashes...\n\nOffset: Hash\n----------------------------------------", filename);
	
	//start offsets to begin hashing
	int md5_start_1 = 0x74; //game data first hash
	int md5_start_2 = 0x64; //game data second hash
	int sha_start_1 = sizeof(MC02Header); //descriptor offset
	int sha_start_2 = sizeof(MC02Header) + (int)header->DescriptorSize; //savedata offset
	int sha_start_3 = 0x0; //header offset

	//hash areas
	int md5_length_1 = 0x3FF0;
	int md5_length_2 = 0xF494;
	int sha_length_1 = (int)header->DescriptorSize;
	int sha_length_2 = (int)header->SavedataSize;
	int sha_length_3 = sizeof(MC02Header) - 0x14;

	//hash write locations
	int md5_offset_1 = 0x64;
	int md5_offset_2 = 0xF4F8;
	int sha_offset_1 = 0x10;
	int sha_offset_2 = 0x24;
	int sha_offset_3 = 0x38;

	//do hashing
	unsigned char* hash = (unsigned char*)malloc(0x14);

	//first hash
	md5(buffer + md5_start_1, md5_length_1, hash);
	fseek(filehandle, md5_offset_1, 0);
	fwrite(hash, 1, 0x10, filehandle);
	printf("\n0x%-4X: 0x", md5_offset_1);
	for (int i = 0; i < 0x10; i++) printf("%02X", hash[i]);

	//second hash
	md5(buffer + md5_start_2, md5_length_2, hash);
	fseek(filehandle, md5_offset_2, 0);
	fwrite(hash, 1, 0x10, filehandle);
	printf("\n0x%-4X: 0x", md5_offset_2);
	for (int i = 0; i < 0x10; i++) printf("%02X", hash[i]);

	//third hash
	hmac_sha1(auth_key, 0x10, buffer + sha_start_1, sha_length_1, hash);
	fseek(filehandle, sha_offset_1, 0);
	fwrite(hash, 1, 0x14, filehandle);
	printf("\n0x%-4X: 0x", sha_offset_1);
	for (int i = 0; i < 0x14; i++) printf("%02X", hash[i]);

	//fourth hash
	hmac_sha1(auth_key, 0x10, buffer + sha_start_2, sha_length_2, hash);
	fseek(filehandle, sha_offset_2, 0);
	fwrite(hash, 1, 0x14, filehandle);
	printf("\n0x%-4X: 0x", sha_offset_2);
	for (int i = 0; i < 0x14; i++) printf("%02X", hash[i]);

	//fifth hash
	hmac_sha1(auth_key, 0x10, buffer + sha_start_3, sha_length_3, hash);
	fseek(filehandle, sha_offset_3, 0);
	fwrite(hash, 1, 0x14, filehandle);
	printf("\n0x%-4X: 0x", sha_offset_3);
	for (int i = 0; i < 0x14; i++) printf("%02X", hash[i]);

	//clean up
	fflush(filehandle);
	fclose(filehandle);
	free(buffer);
	free(hash);

	printf("\n\nDone.");

exit:
	getchar();
	return 0;
}