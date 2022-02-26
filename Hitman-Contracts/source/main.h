#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "XCalcSigLib\XCalcSigLib.h"
#include "Data\FileIO.h"
#include "Data\Hexadecimal.h"

/*
Game: Hitman: Contracts
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x45530012
Signature Key: 2AE2713DD4A34AE3F20C29CD851DD327
*/

#define INFO_GAME_NAME "Hitman: Contracts\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / NTSC-J / PAL\0"
#define INFO_TITLE_ID "45530012\0"

#define INFO_USAGE "hcsign <file>\0"

#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);