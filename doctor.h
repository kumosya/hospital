#ifndef _DOCTOR_H
#define _DOCTOR_H

#include "lib.h"
#include "his.h"

typedef unsigned int DoctorIdType;

typedef struct _Doctor {
	char name[NAME_LENGTH];
	DoctorIdType id;
	Patient *patients_queue; // 就诊患者队列

	struct _Doctor* prev;
	struct _Doctor* next;
} Doctor;

#endif /* _DOCTOR_H */
