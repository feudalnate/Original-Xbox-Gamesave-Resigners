#include "HMACSHA1.h"

void hmac_sha1(byte* buffer, u32 buffer_length, byte* buffer2, u32 buffer_length2, byte* key, u32 key_length, byte* result) {

	/*
		NOTE: Xbox/Windows 2000 kernel does this slightly different.

		Support 2 input buffers specifically for the Xbox EEPROM

		Implementation below is as-per specification
		https://datatracker.ietf.org/doc/html/rfc2104
	*/

	if (buffer && buffer_length > 0 && key && key_length > 0) {

		const u32 HASHSIZE = 20;
		const u32 BLOCKSIZE = 64;

		sha1_context* context = new sha1_context();
		byte kipad[BLOCKSIZE]; //key, inner padding
		byte kopad[BLOCKSIZE]; //key, outer padding
		byte hash[HASHSIZE]; //working digest buffer

		//zero pad buffers
		memset(kipad, 0, BLOCKSIZE);
		memset(kopad, 0, BLOCKSIZE);

		if (key_length > BLOCKSIZE) {
			//hash key if can't fit into pad buffers
			sha1_init(context);
			sha1_update(context, key, key_length);
			sha1_final(context, hash);
			memcpy(kipad, hash, HASHSIZE);
			memcpy(kopad, hash, HASHSIZE);
		}
		else {
			//if the key fits just copy it
			memcpy(kipad, key, key_length);
			memcpy(kopad, key, key_length);
		}

		//HMAC xor
		for (u32 i = 0; i < BLOCKSIZE; i++) {
			kipad[i] ^= 0x36;
			kopad[i] ^= 0x5C;
		}

		//inner
		sha1_init(context);
		sha1_update(context, kipad, BLOCKSIZE);
		sha1_update(context, buffer, buffer_length);
		if (buffer2 && (buffer_length2 > 0)) {
			sha1_update(context, buffer2, buffer_length2);
		}
		sha1_final(context, hash);

		//outer
		sha1_init(context);
		sha1_update(context, kopad, BLOCKSIZE);
		sha1_update(context, hash, HASHSIZE);
		sha1_final(context, hash);

		//copy result
		memcpy(result, hash, HASHSIZE);

		//wipe
		delete context;
		memset(kipad, 0, BLOCKSIZE);
		memset(kopad, 0, BLOCKSIZE);
		memset(hash, 0, HASHSIZE);
	}
}


/*
	NOTE: The functions below aren't _technically_ standard.

	These are here to conform (more-or-less) to how the XCrypt library in the Xbox kernel does block by block hashing
*/

void hmacsha1_init(sha1_context* context, byte* key, u32 key_length) {
	if (context && key && key_length > 0) {

		/*
			NOTE: We push the KiPad block through mixed with the key on initialization and leave out the KoPad block until hash finalization

			SELF-NOTE(feudalnate): Should this implementation pull the SHA1 context, KiPad/KoPad blocks, and the key/key length out into it's own HMAC context struct instead?
		*/

		const u32 HASHSIZE = 20;
		const u32 BLOCKSIZE = 64;

		byte kipad[BLOCKSIZE]; //key, inner padding
		byte hash[HASHSIZE]; //working digest buffer

		//zero out pad buffer
		memset(kipad, 0, BLOCKSIZE);

		/*
			NOTE: The XCrypt library only seems to trim the key if it's larger than BLOCKSIZE instead of hashing it...

			This implementation will follow the specification properly, future issues withstanding...
		*/
		if (key_length > BLOCKSIZE) {
			//hash key if can't fit into pad buffers
			sha1_init(context);
			sha1_update(context, key, key_length);
			sha1_final(context, hash);
			memcpy(kipad, hash, HASHSIZE);
		}
		else {
			//if the key fits just copy it
			memcpy(kipad, key, key_length);
		}

		//HMAC xor (inner only)
		for (u32 i = 0; i < BLOCKSIZE; i++) {
			kipad[i] ^= 0x36;
		}

		//push inner block through SHA1, do not finalize the hash
		sha1_init(context);
		sha1_update(context, kipad, BLOCKSIZE);

		//wipe
		memset(kipad, 0, BLOCKSIZE);
		memset(hash, 0, HASHSIZE);
	}
}

void hmacsha1_update(sha1_context* context, byte* buffer, u32 length) {
	if (context && buffer && length > 0) {

		//nothing special here just push the data block through SHA1
		sha1_update(context, buffer, length);
	}
}

void hmacsha1_final(sha1_context* context, byte* key, u32 key_length, byte* result) {
	if (context && key && key_length > 0 && result) {

		const u32 HASHSIZE = 20;
		const u32 BLOCKSIZE = 64;

		byte kopad[BLOCKSIZE]; //key, outer padding
		byte hash[HASHSIZE]; //working digest buffer

		//zero out pad buffer
		memset(kopad, 0, BLOCKSIZE);

		/*
			NOTE: The XCrypt library only seems to trim the key if it's larger than BLOCKSIZE instead of hashing it...

			This implementation will follow the specification properly, future issues withstanding...
		*/
		if (key_length > BLOCKSIZE) {
			//need another SHA1 context here, can't use input context for temp. purposes
			sha1_context* temp = new sha1_context();

			//hash key if can't fit into pad buffers
			sha1_init(temp);
			sha1_update(temp, key, key_length);
			sha1_final(temp, hash);
			memcpy(kopad, hash, HASHSIZE);

			delete temp;
		}
		else {
			//if the key fits just copy it
			memcpy(kopad, key, key_length);
		}

		//HMAC xor (outer only)
		for (u32 i = 0; i < BLOCKSIZE; i++) {
			kopad[i] ^= 0x5C;
		}

		//finialize the hash of inner block (KiPad) and input data
		sha1_final(context, hash);

		//push outer block (KoPad) and hash of inner block/input data through final hash round
		sha1_init(context);
		sha1_update(context, kopad, BLOCKSIZE);
		sha1_update(context, hash, HASHSIZE);
		sha1_final(context, hash);

		//copy result
		memcpy(result, hash, HASHSIZE);

		//wipe
		memset(kopad, 0, BLOCKSIZE);
		memset(hash, 0, HASHSIZE);
	}
}