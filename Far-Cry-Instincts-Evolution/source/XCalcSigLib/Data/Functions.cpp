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

bool32 strcmp(utf7* a, utf7* b, u32 len) {

	if (a && b && len > 0) {

		utf7 char_a, char_b;
		for (u32 i = 0; i < len; i++) {

			char_a = ((a[i] >= 'A' && a[i] <= 'Z') ? ('a' + (a[i] - 'A')) : a[i]);
			char_b = ((b[i] >= 'A' && b[i] <= 'Z') ? ('a' + (b[i] - 'A')) : b[i]);

			if (char_a != char_b)
				return false;
		}

		return true;
	}

	return false;
}

bool32 strcmp(utf8* a, utf8* b, u32 len) {

	if (a && b && len > 0) {

		utf8 char_a, char_b;
		for (u32 i = 0; i < len; i++) {

			char_a = ((a[i] >= 'A' && a[i] <= 'Z') ? ('a' + (a[i] - 'A')) : a[i]);
			char_b = ((b[i] >= 'A' && b[i] <= 'Z') ? ('a' + (b[i] - 'A')) : b[i]);

			if (char_a != char_b)
				return false;
		}

		return true;
	}

	return false;

}