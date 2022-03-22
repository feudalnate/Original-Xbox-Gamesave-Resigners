#pragma once
#include <stdlib.h>
#include <stdio.h>

#include "XCalcSigLib\XCalcSigLib.h"
#include "Data\FileIO.h"
#include "Data\Hexadecimal.h"
#include "Data\Functions.h"

/*
Game: Star Wars: Republic Commando
Region: NTSC-U / PAL
TitleID: 0x4C410013
Signature Key: 88C3BC25F5BB1DE11F1F6FCE21BF7F74
*/

/*
Game: Star Wars: Republic Commando
Region: NTSC-J
TitleID: 0x4C410019
Signature Key: 54731ABF22F0EA8687AAA6478F4BAAEA
*/

#define INFO_GAME_NAME "Star Wars: Republic Commando\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / NTSC-J / PAL\0"
#define INFO_TITLE_ID "4C410013 / 4C410019\0"

#define INFO_USAGE "swrpsign [jp] <XboxHDKey> <file>\n\nWARNING: Specify \"jp\" flag only if signing NTSC-J gamesaves\0"

#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
bool CheckXboxHDKey(utf8* input_XboxHDKey_string, byte* output_XboxHDKey_bytes);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);