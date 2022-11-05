#pragma once
#ifndef DATAFUNCTIONS
#define DATAFUNCTIONS

#include "Types.h"

void copy(byte* dst, byte* src, u32 len);
void set(byte* buffer, byte value, u32 len);
void zero(byte* buffer, u32 len);
bool compare(byte* a, byte* b, u32 len);
bool strcmp7(utf7* a, utf7* b, u32 len);
bool strcmp8(utf8* a, utf8* b, u32 len);
u32 strlen7(utf7* string);
u32 strlen7(utf7* string, u32 max);
u32 strlen8(utf8* string);
u32 strlen8(utf8* string, u32 max);

#endif