#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "XCalcSigLib\XCalcSigLib.h"
#include "Data\FileIO.h"
#include "Data\Hexadecimal.h"
#include "Data\Functions.h"

/*
Game: Half-Life 2
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x45410091
Signature Key: CCB0F5720B1478A0B2C518AB429E7DEA
*/

#define INFO_GAME_NAME "Half-Life 2\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / NTSC-J / PAL\0"
#define INFO_TITLE_ID "45410091\0"

#define INFO_USAGE "hl2sign <XboxHDKey> <file>\0"

#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
void SignJSAV(byte* buffer, u32 buffer_size, byte* XboxHDKey);
void SignGeneric(byte* buffer, u32 buffer_size, byte* XboxHDKey);
bool CheckXboxHDKey(utf8* input_XboxHDKey_string, byte* output_XboxHDKey_bytes);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);