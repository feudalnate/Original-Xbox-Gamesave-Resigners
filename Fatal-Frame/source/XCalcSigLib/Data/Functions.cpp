#include "Functions.h"

void copy(byte* dst, byte* src, u32 len) {
	for (u32 i = 0; i < len; i++)
		dst[i] = src[i];
}

void set(byte* buffer, byte value, u32 len) {
	for (u32 i = 0; i < len; i++)
		buffer[i] = value;
}

void zero(byte* buffer, u32 len) {
	set(buffer, 0, len);
}

bool compare(byte* a, byte* b, u32 len) {
	for (u32 i = 0; i < len; i++)
		if (a[i] != b[i])
			return false;
	return true;
}

bool strcmp7(utf7* a, utf7* b, u32 len) {

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

bool strcmp8(utf8* a, utf8* b, u32 len) {

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