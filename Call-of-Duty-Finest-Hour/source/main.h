#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "XCalcSigLib\XCalcSigLib.h"
#include "Data\FileIO.h"
#include "Data\Hexadecimal.h"

/*
Game: Call of Duty: Finest Hour
Region: NTSC-U / NTSC-J / PAL
TitleID: 0x4156002A
Signature Key: 50AFC9B126306875A53A9C4DB8E25A21
*/

#define INFO_GAME_NAME "Call of Duty: Finest Hour\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / NTSC-J / PAL\0"
#define INFO_TITLE_ID "4156002A\0"

#define INFO_USAGE "codsign <file>\0"

#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);