#pragma once

const unsigned int Magic = 0x4D433032; // '20CM' (little endian) / 0x3230434D 'MC02' (big endian) 

//pre-mixed key of certificate key + title signature (XCalcSig 'roamable' signature key)
const unsigned char auth_key[0x10] = { 0x4F, 0x30, 0x5E, 0x65, 0xF9, 0x60, 0xBF, 0xFB, 0x92, 0xCF, 0xF5, 0x9A, 0xD0, 0x99, 0xBE, 0x67 };

struct MC02Header {
	char Magic[4]; //MC02 (big endian) | 20CM (little endian)
	unsigned int PackageSize; //total size of the container
	unsigned int DescriptorSize; //size of the first block of data (generally holds data related to the second block, hence 'descriptor')
	unsigned int SavedataSize; //size of the second block of data

	/*
	//standard EAChecksum hashes
	unsigned int DescriptorHash; //EAChecksum hash of the first block
	unsigned int SavedataHash; //EAChecksum hash of the second block
	unsigned int HeaderHash; //EAChecksum hash of the header (from 0x0 over the next 0x18 bytes)
	*/

	//non-standard XCalcSig hashes
	unsigned char DescriptorHash[0x14]; //HMAC-SHA1 hash of the first block
	unsigned char SavedataHash[0x14]; //HMAC-SHA1 hash of the second block
	unsigned char HeaderHash[0x14]; //HMAC-SHA1 hash of the header area (0x0 - 0x38)
} MC02Header;