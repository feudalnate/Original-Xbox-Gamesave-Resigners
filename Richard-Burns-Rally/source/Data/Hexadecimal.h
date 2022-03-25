#pragma once
#ifndef HEXADECIMAL
#define HEXADECIMAL

#include "Types.h"

bool ValidHex(utf8* string, u32 length);
u32 HexLenFromByteCount(u32 number_of_bytes, bool include_null_terminator = false);
u32 ByteCountFromHexLen(utf8* null_terminated_string);
u32 ByteCountFromHexLen(u32 hex_string_length);
bool BytesToHex(byte* buffer, u32 buffer_length, utf8* result);
bool HexToBytes(utf8* string, u32 string_length, byte* result);

#endif