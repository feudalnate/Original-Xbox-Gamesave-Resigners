#pragma once
#ifndef FILEIO
#define FILEIO

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdio.h>
#include "Types.h"

#define FILEMODE_READ 0
#define FILEMODE_READWRITE 1

u32 GetFileSize(char* File);
u32 GetFileSize(utf8* File);
u32 GetFileSize(FILE* pFile);

FILE* OpenFile(char* File, u32 FileMode);
FILE* OpenFile(utf8* File, u32 FileMode);
void CloseFile(FILE* &pFile);

u32 ReadBytes(FILE* pFile, s32 Offset, u32 Count, byte* pOutputBuffer);
u32 WriteBytes(FILE* pFile, s32 Offset, u32 Count, byte* pInputBuffer);

#endif