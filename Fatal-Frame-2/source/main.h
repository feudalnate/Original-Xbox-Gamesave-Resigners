#pragma once
#include "XCalcSigLib\XCalcSigLib.h"
#include "Data\FileIO.h"
#include "Data\Hexadecimal.h"

/*
Game: Fatal Frame 2 / Project ZERO 2
Region: NTSC-U / PAL
TitleID: 0x5443000A
Signature Key: FEE1A3D52ABAD9171B19E91F7B771535
*/

#define INFO_GAME_NAME "Fatal Frame 2 / Project ZERO 2\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / PAL\0"
#define INFO_TITLE_ID "5443000A\0"

#define INFO_USAGE "ff2sign <XboxHDKey> <file>\0"

#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);
bool CheckXboxHDKey(utf8* input_XboxHDKey_string, byte* output_XboxHDKey_bytes);
bool SignBlock(byte* block, u32 block_size, byte* TitleSignatureKey, byte* XboxHDKey);