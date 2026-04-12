#include "lib.h"

#include <stdio.h>

FILE* FileOpen(const char *filename, const char *mode) {
	FILE* fp;
	fopen_s(&fp, filename, mode);
	return fp;
}
