#pragma once

#include "XCalcSigLib\XCalcSigLib.h"
#include "Data\FileIO.h"
#include "Data\Hexadecimal.h"
#include "Data\Functions.h"

/*
Game: FlatOut 2
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x454D0020
Signature Key: EC1981167F15ACB9FEAD8AB67A02C1A5
*/

#define INFO_GAME_NAME "FlatOut 2\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / NTSC-J / PAL\0"
#define INFO_TITLE_ID "454D0020\0"

#define INFO_USAGE "fo2sign <XboxHDKey> <file>\0"

#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
bool CheckXboxHDKey(utf8* input_XboxHDKey_string, byte* output_XboxHDKey_bytes);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);