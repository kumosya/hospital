#ifndef _LIB_H
#define _LIB_H

#include "list.h"
#include "patient.h"
#include "doctor.h"

#include <stdio.h>

// List
ListMkInc(Patient);
ListMkInc(Doctor);

// File
FILE* FileOpen(const char* filename, const char* mode);

#endif /* _LIB_H */
