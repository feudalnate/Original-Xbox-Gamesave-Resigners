#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <windows.h>
#include "SHA1/hmac.h"

const unsigned char xbe_certificate_key[0x10] = { 0x5C, 0x07, 0x33, 0xAE, 0x04, 0x01, 0xF7, 0xE8, 0xBA, 0x79, 0x93, 0xFD, 0xCD, 0x2F, 0x1F, 0xE0 };
const unsigned char pal_signature_key[0x10] = { 0x07, 0x4B, 0xD1, 0x97, 0x2F, 0x7B, 0xE0, 0x74, 0x53, 0x9F, 0x82, 0x14, 0x3A, 0x72, 0x2E, 0x4F };
const unsigned char ntsc_signature_key[0x10] = { 0xE1, 0xD4, 0x11, 0x8A, 0x91, 0xD2, 0x0D, 0x24, 0xC0, 0xE3, 0xBB, 0xB1, 0x62, 0x32, 0x96, 0x4D };

int main(int argc, char* argv[])
{
	system("cls||clear"); //clear console window
	SetConsoleTitle(TEXT("Jet Set Radio Future (XBOX) - Hash Fix"));

	char* filename;
	FILE* filehandle;
	long filesize;
	int PAL = -1;

	printf("Jet Set Radio Future (XBOX)\nHash Fix by feudalnate (June 10th, 2019)\n");

	//check args
	if (argc != 3)
	{
		printf("Usage: jsrffix <pal|ntsc> <input file>");
		goto exit;
	}

	//check specified region
	char* region = argv[1];
	for (int i = 0; region[i]; i++)
	{
		region[i] = tolower((unsigned char)region[i]); //force lower-case 
	}
	if (strcmp(region, "pal") == 0) PAL = 1;
	else if (strcmp(region, "ntsc") == 0) PAL = 0;
	else
	{
		printf("Error: Invalid region type \"%s\"", region);
		goto exit;
	}

	//check input file
	filename = argv[2];
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

	//check file size
	fseek(filehandle, 0, SEEK_END);
	filesize = ftell(filehandle);
	if (filesize != 0xA080)
	{
		printf("Error: Invalid file size (not a JSRF save?)");
		fclose(filehandle);
		goto exit;
	}

	//read file into memory
	unsigned char* buffer = (unsigned char*)malloc(filesize);
	rewind(filehandle);
	fread(buffer, 1, filesize, filehandle);

	//compute "auth_key"
	unsigned char* auth_key = (unsigned char*)malloc(0x14);
	hmac_sha1(&xbe_certificate_key, 0x10, (PAL ? &pal_signature_key : &ntsc_signature_key), 0x10, auth_key);

	int hash_start = 0x14; //start offset to begin hashing
	int hash_length = filesize - hash_start; //hashing area
	int hash_offset = 0; //hash write location

	//do hashing
	printf("\nCurrent hash:    0x");
	for (int i = 0; i < 0x14; i++) printf("%02X", buffer[i]);

	unsigned char* hash = (unsigned char*)malloc(0x14);
	hmac_sha1(auth_key, 0x10, buffer + hash_start, hash_length, hash); //only use first 0x10 bytes of auth_key
	
	printf("\nCalculated hash: 0x");
	for (int i = 0; i < 0x14; i++) printf("%02X", hash[i]);

	//write the hash
	rewind(filehandle);
	fwrite(hash, 1, 0x14, filehandle);

	//clean up
	fflush(filehandle);
	fclose(filehandle);
	free(buffer);
	free(auth_key);
	free(hash);

	printf("\n\n%s signature successfully written to file.", (PAL ? "PAL" : "NTSC"));

exit:
	getchar();
	return 0;
}