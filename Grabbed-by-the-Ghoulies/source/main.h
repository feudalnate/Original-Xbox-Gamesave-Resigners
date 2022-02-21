#pragma once
#include <stdlib.h>

#include "XCalcSigLib\XCalcSigLib.h"
#include "Data\FileIO.h"
#include "Data\Hexadecimal.h"

/*
Game: Grabbed by the Ghoulies
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x4D530053
Signature Key: 4426DB89185652A1945C8820DC5A0A43
*/

#define INFO_GAME_NAME "Grabbed by the Ghoulies\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / NTSC-J / PAL\0"
#define INFO_TITLE_ID "4D530053\0"

#define INFO_USAGE "gbtgsign <file>\0"

#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);