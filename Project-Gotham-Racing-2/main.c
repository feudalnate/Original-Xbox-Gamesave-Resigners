/*
Game: Project Gotham Racing 2
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x4D53004B
Signature Key: E24F381F76FA6084DD4E25607184EF81
*/

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <windows.h>
#include "SHA1/hmac.h"

unsigned char* CalculateRoamable(unsigned char* TitleSignatureKey, unsigned char* data, int length);

//pgr2 signature key (all regions)
const unsigned char signature_key[0x10] = { 0xE2, 0x4F, 0x38, 0x1F, 0x76, 0xFA, 0x60, 0x84, 0xDD, 0x4E, 0x25, 0x60, 0x71, 0x84, 0xEF, 0x81 };

int main(int argc, char* argv[])
{
	SetConsoleTitle(TEXT("Project Gotham Racing 2 (XBOX) Resigner"));

	char* filename;
	long filesize;
	FILE* filehandle;

	printf("Project Gotham Racing 2 (XBOX)\nResigner by feudalnate (July 15th, 2020)\
	\n----------------------------------------\n\n");

	//check args
	if (argc != 2)
	{
		printf("Usage: pgr2resigner <input file>");
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
#pragma warning(disable: 4996)
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

	//sign data
	unsigned char* hash = CalculateRoamable(&signature_key, (buffer + 0x14), (filesize - 0x14));
	memcpy(buffer, hash, 0x14);

	//write data back to file
	rewind(filehandle);
	fwrite(buffer, 1, filesize, filehandle);
	fflush(filehandle);

	//clean up
	fclose(filehandle);
	free(buffer);
	free(hash);

	printf("Gamesave signed successfully!");

exit:
	getchar();
	return 0;
}

unsigned char* CalculateRoamable(unsigned char* TitleSignatureKey, unsigned char* data, int length)
{
	//key hard-coded in kernel. used for mixing the title signature into an 'auth' key which is used to the sign save data 
	unsigned char XboxCertificateKey[0x10] = { 0x5C, 0x07, 0x33, 0xAE, 0x04, 0x01, 0xF7, 0xE8, 0xBA, 0x79, 0x93, 0xFD, 0xCD, 0x2F, 0x1F, 0xE0 };

	unsigned char* cert_key = (unsigned char*)malloc(0x10);
	unsigned char* auth_key = (unsigned char*)malloc(0x14);
	unsigned char* title_signature_key = (unsigned char*)malloc(0x10);
	unsigned char* roamable_signature = (unsigned char*)malloc(0x14);

	//copy keys (not necessary in C but for claritys sake)
	memcpy(cert_key, &XboxCertificateKey, 0x10); //copy 0x10 bytes
	memcpy(title_signature_key, TitleSignatureKey, 0x10); //copy 0x10 bytes

	//calc auth key
	hmac_sha1(cert_key, 0x10, title_signature_key, 0x10, auth_key);

	//calc roamable signature
	hmac_sha1(auth_key, 0x10, data, length, roamable_signature); //use first 0x10 bytes of auth_key

	//clean up
	free(cert_key);
	free(auth_key);
	free(title_signature_key);

	return roamable_signature; //must be freed by caller
}