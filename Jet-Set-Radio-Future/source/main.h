#include "Helpers\Types.h"
#include "Helpers\Functions.h"
#include "Helpers\Hexadecimal.h"
#include "Helpers\FileIO.h"
#include "XCalcSigLib\XCalcSigLib.h"

/*
Game: Jet Set Radio Future
Region: NTSC-U / NTSC-J
TitleID: 0x5345000A
Signature Key: E1D4118A91D20D24C0E3BBB16232964D
*/

/*
Game: Jet Set Radio Future
Region: PAL
TitleID: 0x49470018
Signature Key: 074BD1972F7BE074539F82143A722E4F
*/

const byte TitleSignatureKey[XCALCSIG_KEY_SIZE] = { 0xE1, 0xD4, 0x11, 0x8A, 0x91, 0xD2, 0x0D, 0x24, 0xC0, 0xE3, 0xBB, 0xB1, 0x62, 0x32, 0x96, 0x4D }; //NTSC-U/J
const byte AlternateTitleSignatureKey[XCALCSIG_KEY_SIZE] = { 0x07, 0x4B, 0xD1, 0x97, 0x2F, 0x7B, 0xE0, 0x74, 0x53, 0x9F, 0x82, 0x14, 0x3A, 0x72, 0x2E, 0x4F }; //PAL

#define INFO_GAME_NAME "Jet Set Radio Future\0"
#define INFO_SUPPORTED_REGIONS "NTSC-U / NTSC-J / PAL\0"
#define INFO_TITLE_ID "5345000A / 49470018\0"
#define INFO_USAGE "jsrfsign <ntsc|pal> <file>\0"
#define INFO_URL "https://github.com/feudalnate\0"
#define INFO_BUILD_DATE __DATE__

int main(int argc, char* argv[]);
void PrintInfo();
void PrintUsage();
void PrintHex(byte* buffer, u32 length, bool newLine);
u32 CheckRegionString(char* string);