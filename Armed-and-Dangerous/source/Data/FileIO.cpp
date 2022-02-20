#include "FileIO.h"

u32 GetFileSize(char* File) {

	u32 result = 0;

	if (File) {

		FILE* pFile = fopen(File, "rb");
		if (pFile != NULL) {

			if (fseek(pFile, 0, SEEK_END) == 0) {

				s32 size = ftell(pFile);
				if (size != -1)
					result = (u32)size;

			}

			fclose(pFile);
		}

	}

	return result;
}

u32 GetFileSize(utf8* File) {

	return GetFileSize((char*)File);
}

u32 GetFileSize(FILE* pFile) {

	u32 result = 0;

	if (pFile != NULL) {

		s32 last = ftell(pFile);
		if (last != -1) {

			if (fseek(pFile, 0, SEEK_END) == 0) {

				result = ftell(pFile);
				fseek(pFile, last, SEEK_SET);
			}

		}

	}

	return result;
}

FILE* OpenFile(char* File, u32 FileMode) {

	if (FileMode == FILEMODE_READ || FileMode == FILEMODE_READWRITE) {

		if (File != NULL) {

			return fopen(File, (FileMode == FILEMODE_READ ? "rb" : "rb+"));
		}

	}

	return NULL;
}

FILE* OpenFile(utf8* File, u32 FileMode) {

	return OpenFile((char*)File, FileMode);
}

void CloseFile(FILE* &pFile) {

	if (pFile) {

		fclose(pFile);
		pFile = 0;
	}

}

u32 ReadBytes(FILE* pFile, s32 Offset, u32 Count, byte* pOutputBuffer) {

	u32 result = 0;

	if (pFile && pOutputBuffer && Count > 0) {

		if (fseek(pFile, Offset, SEEK_SET) == 0) {

			result = fread(pOutputBuffer, 1, Count, pFile);
		}

	}

	return result;
}

u32 WriteBytes(FILE* pFile, s32 Offset, u32 Count, byte* pInputBuffer) {

	u32 result = 0;

	if (pFile && pInputBuffer && Count > 0) {

		if (fseek(pFile, Offset, SEEK_SET) == 0) {

			result = fwrite(pInputBuffer, 1, Count, pFile);
			if (result > 0)
				fflush(pFile);
		}
	}

	return result;
}