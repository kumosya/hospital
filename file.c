#include "framework.h"
#include "lib.h"

FILE* FileOpen(const char *filename, const char *mode) {
	FILE* fp;
	fopen_s(&fp, filename, mode);
	return fp;
}
