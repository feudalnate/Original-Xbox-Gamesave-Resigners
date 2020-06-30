/*
Game: Black
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x45410083
Signature Key: 87D30D70E361DD1C517B588E0118C3E0
*/

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <windows.h>
#include "SHA1/hmac.h"


int IsHex(char* string);
unsigned char* hex2bin(char* string);
unsigned char* CalculateRoamable(unsigned char* TitleSignatureKey, unsigned char* data, int length);
unsigned char* CalculateNonRoamable(unsigned char* TitleSignatureKey, unsigned char* XboxHDKey, unsigned char* data, int length);

//black signature key (all regions)
const unsigned char signature_key[0x10] = { 0x87, 0xD3, 0x0D, 0x70, 0xE3, 0x61, 0xDD, 0x1C, 0x51, 0x7B, 0x58, 0x8E, 0x01, 0x18, 0xC3, 0xE0 };

int main(int argc, char* argv[])
{
	SetConsoleTitle(TEXT("Black (XBOX) Resigner"));

	char* filename;
	char* xboxhdkey_str;
	unsigned char* xboxhdkey;
	FILE* filehandle;
	long filesize;

	printf("Black (XBOX)\nResigner by feudalnate (June 29th, 2020)\
	\n----------------------------------------\n\n");

	//check args
	if (argc != 3)
	{
		printf("Usage: blackresigner <XboxHDKey> <input file>");
		goto exit;
	}
	xboxhdkey_str = argv[1];
	filename = argv[2];

	//check xboxhdkey is hex and is correct size (32 chars (16 bytes (0x10)))
	if (strlen(xboxhdkey_str) != 32 || !IsHex(xboxhdkey_str))
	{
		printf("Error: Invalid XboxHDKey. Expected 32 character hexadecimal string");
		goto exit;
	}

	//convert xboxhdkey hex string to byte
	xboxhdkey = hex2bin(xboxhdkey_str);
	if (xboxhdkey == NULL)
	{
		//shouldnt happen if the IsHex fails, prepare for it anyway :)
		printf("Error: Invalid XboxHDKey. Failed to convert from hexadecimal");
		goto exit;
	}

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

	//check file size
	if (filesize != 0x1800)
	{
		fclose(filehandle);
		printf("Error: File \"%s\" is invalid size", filename);
		goto exit;
	}

	//read file into memory
	unsigned char* buffer = (unsigned char*)malloc(filesize);
	rewind(filehandle);
	fread(buffer, 1, filesize, filehandle);

	//sign data
	unsigned char* hash = CalculateNonRoamable(&signature_key, xboxhdkey, buffer, (filesize - 0x14));
	memcpy(buffer + (filesize - 0x14), hash, 0x14);

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

int IsHex(char* string)
{
	const char hexdigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	if (string == NULL) return -1;
	int length = strlen(string);
	if (length == 0 || length % 2 != 0) return -1;
	char* lower = (char*)calloc(1, length);
	for (int i = 0; string[i]; i++)
	{
		lower[i] = tolower(string[i]); //force lower-case 
	}
	for (int i = 0; lower[i]; i++)
	{
		int match = -1;
		for (int x = 0; hexdigits[x]; x++)
		{
			if (lower[i] == hexdigits[x])
			{
				match = 0;
				break;
			}
		}
		if (!match)
		{
			free(lower);
			return -1;
		}
	}
	free(lower);
	return 0;
}

unsigned char* hex2bin(char* string)
{
	int length = (strlen(string) / 2);
	unsigned char* result = (unsigned char*)calloc(length, 1);
	int index = 0;
	while (index < length * 2) {
		char c = string[index];
		int value = 0;
		if (c >= '0' && c <= '9') value = (c - '0');
		else if (c >= 'A' && c <= 'F') value = (10 + (c - 'A'));
		else if (c >= 'a' && c <= 'f') value = (10 + (c - 'a'));
		else
		{
			free(result);
			return NULL;
		}
		result[(index / 2)] += value << (((index + 1) % 2) * 4);
		index++;
	}
	return result;
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

unsigned char* CalculateNonRoamable(unsigned char* TitleSignatureKey, unsigned char* XboxHDKey, unsigned char* data, int length)
{
	unsigned char* xbox_hd_key = (unsigned char*)malloc(0x10);
	unsigned char* roamable_signature;
	unsigned char* nonroamable_signature = (unsigned char*)malloc(0x14);

	//copy keys (not necessary in C but for claritys sake)
	memcpy(xbox_hd_key, XboxHDKey, 0x10);

	//calc roamable signature
	roamable_signature = CalculateRoamable(TitleSignatureKey, data, length);

	//convert roamable signature to nonroamable signature
	hmac_sha1(xbox_hd_key, 0x10, roamable_signature, 0x14, nonroamable_signature);

	//clean up
	free(xbox_hd_key);
	free(roamable_signature);

	return nonroamable_signature; //must be freed by caller
}