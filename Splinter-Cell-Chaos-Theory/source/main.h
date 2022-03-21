#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "XCalcSigLib\XCalcSigLib.h"
#include "Data\FileIO.h"
#include "Data\Hexadecimal.h"
#include "Data\Functions.h"

/*
Game: Splinter Cell: Chaos Theory (Single Player/Co-op)
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x55530038
Signature Key: EC3283DB375155B3929ED6F1E1C9546F
*/

/*
Game: Splinter Cell: Chaos Theory (Multiplayer)
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x55530041
Signature Key: 6342DD40F83B4728EA822BFD8CB13AC4
*/

#define INFO_GAME_NAME "Splinter Cell: Chaos Theory\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / NTSC-J / PAL\0"
#define INFO_TITLE_ID "55530038 / 55530041\0"

#define INFO_USAGE "scctsign <file>\0"

#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);