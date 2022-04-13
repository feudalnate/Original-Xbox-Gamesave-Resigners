#pragma once
#ifndef HMACSHA1
#define HMACSHA1

#include "..\Data\Types.h"
#include "..\Data\Functions.h"
#include "..\SHA1\SHA1.h"

void hmac_sha1(byte* buffer, u32 buffer_length, byte* buffer2, u32 buffer_length2, byte* key, u32 key_length, byte* result);

void hmacsha1_init(sha1_context* context, byte* key, u32 key_length);
void hmacsha1_update(sha1_context* context, byte* buffer, u32 length);
void hmacsha1_final(sha1_context* context, byte* key, u32 key_length, byte* result);

#endif 
