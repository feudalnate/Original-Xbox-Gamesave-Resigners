#include "Hexadecimal.h"

bool ValidHex(utf8* string, u32 string_length) {

	const char hex_digits[22] = 
	{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'A', 'B', 'C', 'D', 'E', 'F' };

	if (string && string_length > 0 && string_length % 2 == 0) {

		bool match;
		for (u32 i = 0; i < string_length; i++) {

			match = false;
			for (u32 x = 0; x < 22; x++)
			{

				if (string[i] == hex_digits[x]) {

					match = true;
					break;
				}

			}

			if (!match)
				return false;

		}

		return true;
	}

	return false;
}

bool ValidHex(utf7* string, u32 string_length) {
	return ValidHex((utf8*)string, string_length);
}

u32 HexLenFromByteCount(u32 number_of_bytes, bool include_null_terminator) {

	if (number_of_bytes > 0)
		return ((number_of_bytes * 2) + (include_null_terminator ? 1 : 0));

	return 0;
}

u32 ByteCountFromHexLen(utf8* null_terminated_string) {

	if (null_terminated_string) {

		u32 count = 0;
		while (null_terminated_string[count] != '\0')
			count++;

		if (count % 2 == 0)
			return (count / 2);

	}

	return 0;
}

u32 ByteCountFromHexLen(utf7* null_terminated_string) {
	return ByteCountFromHexLen((utf8*)null_terminated_string);
}

u32 ByteCountFromHexLen(u32 hex_string_length) {
	
	if (hex_string_length > 0 && hex_string_length % 2 == 0)
			return (hex_string_length / 2);

	return 0;
}

bool BytesToHex(byte* buffer, u32 buffer_length, utf8* result) {

	if (buffer && result && buffer_length > 0) {

		byte value;
		for (u32 i = 0; i < buffer_length; i++) {

			value = buffer[i];

			if ((value / 16) < 10)
				result[(i * 2)] = (char)((value / 16) + 48);
			else
				result[(i * 2)] = (char)(((value / 16) - 10) + 65);

			if ((value % 16) < 10)
				result[(i * 2) + 1] = (char)((value % 16) + 48);
			else
				result[(i * 2) + 1] = (char)(((value % 16) - 10) + 65);

		}

		return true;
	}

	return false;
}

bool BytesToHex(byte* buffer, u32 buffer_length, utf7* result) {
	return BytesToHex(buffer, buffer_length, (utf8*)result);
}

bool HexToBytes(utf8* string, u32 string_length, byte* result) {

	if (string && string_length > 0 && string_length % 2 == 0 && result) {

		u32 byte_index = 0;
		byte value, nibble;
		for (u32 string_index = 0; string_index < string_length; string_index += 2) {

			value = 0;
			for (u32 nibble_index = 0; nibble_index < 2; nibble_index++) {

				nibble = string[string_index + nibble_index];

				if (nibble >= '0' && nibble <= '9')
					nibble = (nibble - '0');
				else if (nibble >= 'A' && nibble <= 'F')
					nibble = (10 + (nibble - 'A'));
				else if (nibble >= 'a' && nibble <= 'f')
					nibble = (10 + (nibble - 'a'));
				else
					return false;

				if (nibble_index == 0)
					value = (nibble << 4);
				else
					value |= nibble;

			}

			result[byte_index] = value;
			byte_index++;
		}

		return true;
	}
	
	return false;
}

bool HexToBytes(utf7* string, u32 string_length, byte* result) {
	return HexToBytes((utf8*)string, string_length, result);
}
