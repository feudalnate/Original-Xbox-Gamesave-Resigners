#include "SHA1.h"

/*
	NOTE: Partial SHA-1 implementation. Functions are _mostly_ 1:1 with original SHA-1 source.

	"Hands-off mode" only
	Little endian only
*/

//Standard SHA-1 defines
#define rol(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits)))) //rotate left

#define blk0(i) (block->l[i] = (rol(block->l[i], 24) & 0xFF00FF00) | (rol(block->l[i], 8) & 0x00FF00FF)) //little endian only
#define blk(i) (block->l[i & 15] = rol(block->l[(i + 13) & 15] ^ block->l[(i + 8) & 15] ^ block->l[(i + 2) & 15] ^ block->l[i & 15], 1))

#define R0(v, w, x, y, z, i) z += ((w & (x ^ y)) ^ y) + blk0(i) + 0x5A827999 + rol(v, 5); w = rol(w, 30);
#define R1(v, w, x, y, z, i) z += ((w & (x ^ y)) ^ y) + blk(i) + 0x5A827999 + rol(v, 5); w = rol(w, 30);
#define R2(v, w, x, y, z, i) z += (w ^ x ^ y) + blk(i) + 0x6ED9EBA1 + rol(v, 5); w = rol(w, 30);
#define R3(v, w, x, y, z, i) z += (((w | x) & y) | (w & x)) + blk(i) + 0x8F1BBCDC + rol(v, 5); w = rol(w, 30);
#define R4(v, w, x, y, z, i) z += (w ^ x ^ y) + blk(i) + 0xCA62C1D6 + rol(v, 5); w = rol(w, 30);

void internal_sha1_core(sha1_context* context, byte* buffer)
{
	if (context && buffer) {
		u32 a, b, c, d, e;
		typedef union {
			byte c[64];
			u32 l[16];
		} CHAR64LONG16;
		CHAR64LONG16* block;

		//hands-off only
		static byte workspace[64];
		block = (CHAR64LONG16*)workspace;
		copy((byte*)block, buffer, 64);

		a = context->state[0];
		b = context->state[1];
		c = context->state[2];
		d = context->state[3];
		e = context->state[4];

		R0(a, b, c, d, e, 0);
		R0(e, a, b, c, d, 1);
		R0(d, e, a, b, c, 2);
		R0(c, d, e, a, b, 3);
		R0(b, c, d, e, a, 4);
		R0(a, b, c, d, e, 5);
		R0(e, a, b, c, d, 6);
		R0(d, e, a, b, c, 7);
		R0(c, d, e, a, b, 8);
		R0(b, c, d, e, a, 9);
		R0(a, b, c, d, e, 10);
		R0(e, a, b, c, d, 11);
		R0(d, e, a, b, c, 12);
		R0(c, d, e, a, b, 13);
		R0(b, c, d, e, a, 14);
		R0(a, b, c, d, e, 15);
		R1(e, a, b, c, d, 16);
		R1(d, e, a, b, c, 17);
		R1(c, d, e, a, b, 18);
		R1(b, c, d, e, a, 19);
		R2(a, b, c, d, e, 20);
		R2(e, a, b, c, d, 21);
		R2(d, e, a, b, c, 22);
		R2(c, d, e, a, b, 23);
		R2(b, c, d, e, a, 24);
		R2(a, b, c, d, e, 25);
		R2(e, a, b, c, d, 26);
		R2(d, e, a, b, c, 27);
		R2(c, d, e, a, b, 28);
		R2(b, c, d, e, a, 29);
		R2(a, b, c, d, e, 30);
		R2(e, a, b, c, d, 31);
		R2(d, e, a, b, c, 32);
		R2(c, d, e, a, b, 33);
		R2(b, c, d, e, a, 34);
		R2(a, b, c, d, e, 35);
		R2(e, a, b, c, d, 36);
		R2(d, e, a, b, c, 37);
		R2(c, d, e, a, b, 38);
		R2(b, c, d, e, a, 39);
		R3(a, b, c, d, e, 40);
		R3(e, a, b, c, d, 41);
		R3(d, e, a, b, c, 42);
		R3(c, d, e, a, b, 43);
		R3(b, c, d, e, a, 44);
		R3(a, b, c, d, e, 45);
		R3(e, a, b, c, d, 46);
		R3(d, e, a, b, c, 47);
		R3(c, d, e, a, b, 48);
		R3(b, c, d, e, a, 49);
		R3(a, b, c, d, e, 50);
		R3(e, a, b, c, d, 51);
		R3(d, e, a, b, c, 52);
		R3(c, d, e, a, b, 53);
		R3(b, c, d, e, a, 54);
		R3(a, b, c, d, e, 55);
		R3(e, a, b, c, d, 56);
		R3(d, e, a, b, c, 57);
		R3(c, d, e, a, b, 58);
		R3(b, c, d, e, a, 59);
		R4(a, b, c, d, e, 60);
		R4(e, a, b, c, d, 61);
		R4(d, e, a, b, c, 62);
		R4(c, d, e, a, b, 63);
		R4(b, c, d, e, a, 64);
		R4(a, b, c, d, e, 65);
		R4(e, a, b, c, d, 66);
		R4(d, e, a, b, c, 67);
		R4(c, d, e, a, b, 68);
		R4(b, c, d, e, a, 69);
		R4(a, b, c, d, e, 70);
		R4(e, a, b, c, d, 71);
		R4(d, e, a, b, c, 72);
		R4(c, d, e, a, b, 73);
		R4(b, c, d, e, a, 74);
		R4(a, b, c, d, e, 75);
		R4(e, a, b, c, d, 76);
		R4(d, e, a, b, c, 77);
		R4(c, d, e, a, b, 78);
		R4(b, c, d, e, a, 79);

		context->state[0] += a;
		context->state[1] += b;
		context->state[2] += c;
		context->state[3] += d;
		context->state[4] += e;

		//wipe
		a = 0;
		b = 0;
		c = 0;
		d = 0;
		e = 0;
	}
}

void sha1_init(sha1_context* context) {
	if (context) {
		context->state[0] = 0x67452301;
		context->state[1] = 0xEFCDAB89;
		context->state[2] = 0x98BADCFE;
		context->state[3] = 0x10325476;
		context->state[4] = 0xC3D2E1F0;
		context->count[0] = 0;
		context->count[1] = 0;
		set(context->buffer, 0, 64);
	}
};

void sha1_update(sha1_context* context, byte* buffer, u32 length) {
	if (context && buffer && length > 0) {
		u32 i, j;

		j = (context->count[0] >> 3) & 63;
		if ((context->count[0] += length << 3) < (length << 3)) {
			context->count[1]++;
		}
		context->count[1] += (length >> 29);

		if ((j + length) > 63) {
			i = (64 - j);
			copy(&context->buffer[j], buffer, i);
			internal_sha1_core(context, context->buffer);

			while ((i + 63) < length) {
				internal_sha1_core(context, &buffer[i]);
				i += 64;
			}

			j = 0;
		}
		else {
			i = 0;
		}

		copy(&context->buffer[j], &buffer[i], (length - i));
	}
}

void sha1_final(sha1_context* context, byte* result) {
	if (context && result) {
		byte f[8];
		byte b = 128;

		for (u32 i = 0; i < 8; i++) {
			f[i] = (byte)(context->count[(i >= 4 ? 0 : 1)] >> ((3 - (i & 3)) * 8) & 255);
		}

		sha1_update(context, &b, 1);

		b = 0;
		while ((context->count[0] & 504) != 448) {
			sha1_update(context, &b, 1);
		}

		sha1_update(context, f, 8);

		for (u32 i = 0; i < 20; i++) {
			result[i] = (byte)((context->state[i >> 2] >> ((3 - (i & 3)) * 8)) & 255);
		}

		//wipe
		set(context->buffer, 0, 64);
		set((byte*)context->state, 0, 20);
		set((byte*)context->count, 0, 8);
		set(f, 0, 8);

		//hands-off only
		internal_sha1_core(context, context->buffer);
	}
}