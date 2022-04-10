#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "XCalcSigLib\XCalcSigLib.h"
#include "Data\FileIO.h"
#include "Data\Hexadecimal.h"
#include "Data\Functions.h"

/*
Game: Ninja Gaiden Black
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x5443000D
Signature Key: FC3376488B3E5F00F65A6BDA9209CFE8

Alternate TitleID: 0x5443003 (for importing Ninja Gaiden saves/settings?)
Alternate Signature Key: A50114CA2B7C8198E829E7C937D6FC40 (for importing Ninja Gaiden saves/settings?)

Save file location: \UDATA\5443000D\<SaveID>\saveXXX.dat (replace XXX with 000-999)
Save file size: 0x174A8 (95,400) bytes (static)

Settings file location: \TDATA\5443000D\system.dat
Settings file size: 0x550 (1,360) bytes (static)

*/

#define INFO_GAME_NAME "Ninja Gaiden Black\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / NTSC-J / PAL\0"
#define INFO_TITLE_ID "5443000D\0"

#define INFO_USAGE "ngbsign <XboxHDKey> <file>\0"

#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
bool CheckXboxHDKey(utf8* input_XboxHDKey_string, byte* output_XboxHDKey_bytes);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);