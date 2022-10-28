#include "Data\Types.h"
#include "Data\Functions.h"
#include "Data\Hexadecimal.h"
#include "Data\FileIO.h"
#include "XCalcSigLib\XCalcSigLib.h"

/*
Game: Steel Battalion: Line of Contact
Region: NTSC-U / PAL / NTSC-J
TitleID: 0x43430009
Signature Key: B91003CEC57E68A99AA961D10DC34C98
*/

const byte TitleSignatureKey[XCALCSIG_KEY_SIZE] = { 0xB9, 0x10, 0x03, 0xCE, 0xC5, 0x7E, 0x68, 0xA9, 0x9A, 0xA9, 0x61, 0xD1, 0x0D, 0xC3, 0x4C, 0x98 };

#define INFO_GAME_NAME "Steel Battalion: Line of Contact\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / PAL / NTSC-J\0"
#define INFO_TITLE_ID "43430009\0"
#define INFO_USAGE "sblocsign <file>\0"
#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);