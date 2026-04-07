#pragma once

#include "framework.h"

#define PATIENT_NAME_LEN 63
#define PATIENT_AGE_MAX  120

typedef struct Patient {
	char name[PATIENT_NAME_LEN];
	int age;
	struct Patient *next;
	struct Patient* prev;
} Patient;
