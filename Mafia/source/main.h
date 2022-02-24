#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <Windows.h> //for filesystem stuff

#include "XCalcSigLib\XCalcSigLib.h"
#include "Data\FileIO.h"
#include "Data\Hexadecimal.h"

/*
Game: Mafia
Region: NTSC-U / PAL
TitleID: 0x54540009
Signature Key: 7F2BFB0822D125B958DAA8E9C640B83D
*/

#define INFO_GAME_NAME "Mafia\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / PAL\0"
#define INFO_TITLE_ID "54540009\0"

#define INFO_USAGE "mafiasign <XboxHDKey> <file/directory>\0"

#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
u32 GetKnownFilesFromDirectory(utf8* directory, byte* memory_block);
bool SignFile(byte* XboxHDKey, utf8* file, byte* working_buffer, u32 working_buffer_length);

void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);