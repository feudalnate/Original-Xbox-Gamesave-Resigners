#pragma once
#ifndef DATAFUNCTIONS
#define DATAFUNCTIONS

#include "Types.h"

void memcpy(byte* dst, byte* src, u32 len);
void memset(byte* buffer, byte value, u32 len);
bool32 memcmp(byte* a, byte* b, u32 len);
bool32 strcmp(utf7* a, utf7* b, u32 len);
bool32 strcmp(utf8* a, utf8* b, u32 len);

#endif