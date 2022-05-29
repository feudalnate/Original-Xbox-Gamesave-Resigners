#pragma once
#include "XCalcSigLib\XCalcSigLib.h"
#include "Data\FileIO.h"
#include "Data\Hexadecimal.h"

/*
Game: Fatal Frame / Project ZERO
Region: NTSC-U / PAL
TitleID: 0x54430004 / 0x4D530059
Signature Key: BD1E1C7B4DB4BA8D49E37EA24F80F14E / 0D07E43488A315BF1BDC3B47E0B46B24
*/

#define INFO_GAME_NAME "Fatal Frame / Project ZERO\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / PAL\0"
#define INFO_TITLE_ID "54430004 / 4D530059\0"

#define INFO_USAGE "ffsign <na|pal> <XboxHDKey> <file>\0"

#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);
bool CheckXboxHDKey(utf8* input_XboxHDKey_string, byte* output_XboxHDKey_bytes);
bool SignBlock(byte* block, u32 block_size, byte* TitleSignatureKey, byte* XboxHDKey);