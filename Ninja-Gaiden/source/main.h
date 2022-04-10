#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "XCalcSigLib\XCalcSigLib.h"
#include "Data\FileIO.h"
#include "Data\Hexadecimal.h"
#include "Data\Functions.h"

/*
Game: Ninja Gaiden
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x54430003
Signature Key: A50114CA2B7C8198E829E7C937D6FC40

Save file location: \UDATA\5443003\<SaveID>\saveXXX.dat (replace XXX with 000-999)
Save file size: 0x17488 (95,368) bytes (static)

Settings file location: \TDATA\5443003\system.dat
Settings file size: 0x1B8 (440) bytes (static)

*/

#define INFO_GAME_NAME "Ninja Gaiden\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / NTSC-J / PAL\0"
#define INFO_TITLE_ID "54430003\0"

#define INFO_USAGE "ngsign <XboxHDKey> <file>\0"

#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
bool CheckXboxHDKey(utf8* input_XboxHDKey_string, byte* output_XboxHDKey_bytes);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);