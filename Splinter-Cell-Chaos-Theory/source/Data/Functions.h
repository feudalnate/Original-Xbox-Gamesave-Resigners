#pragma once
#ifndef DATAFUNCTIONS
#define DATAFUNCTIONS

#include "Types.h"

void memcpy(byte* dst, byte* src, u32 len);
void memset(byte* buffer, byte value, u32 len);
bool32 memcmp(byte* a, byte* b, u32 len);

#endif