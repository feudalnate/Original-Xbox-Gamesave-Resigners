#include "Functions.h"

void memcpy(byte* dst, byte* src, u32 len) {
	for (u32 i = 0; i < len; i++)
		dst[i] = src[i];
}

void memset(byte* buffer, byte value, u32 len) {
	for (u32 i = 0; i < len; i++)
		buffer[i] = value;
}

bool32 memcmp(byte* a, byte* b, u32 len) {
	for (u32 i = 0; i < len; i++)
		if (a[i] != b[i])
			return false;
	return true;
}