#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "XCalcSigLib\XCalcSigLib.h"
#include "Data\FileIO.h"
#include "Data\Hexadecimal.h"
#include "Data\Functions.h"

/*
Game: Splinter Cell: Pandora Tomorrow
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x55530019
Signature Key: 0D5B5C7E20F73FF9C24EC23B9A66B341
*/

#define INFO_GAME_NAME "Splinter Cell: Pandora Tomorrow\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / NTSC-J / PAL\0"
#define INFO_TITLE_ID "55530019\0"

#define INFO_USAGE "scptsign <file>\0"

#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);