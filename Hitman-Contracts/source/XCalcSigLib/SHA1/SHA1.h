#pragma once
#ifndef SHA1
#define SHA1

#include "..\Data\Types.h"
#include "..\Data\Functions.h"

struct sha1_context {
	u32 state[5];
	u32 count[2];
	byte buffer[64];
};

void sha1_init(sha1_context* context);
void sha1_update(sha1_context* context, byte* buffer, u32 length);
void sha1_final(sha1_context* context, byte* result);

#endif