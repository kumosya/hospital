#ifndef _PATIENT_H
#define _PATIENT_H

#include "his.h"

#include <stdint.h>

typedef uint32_t PatientIdType;

typedef struct _Doctor Doctor;

typedef struct _Patient {
    char name[NAME_LENGTH];
    PatientIdType id;
    Doctor* doctor;  // 就诊医生
	enum Gender gender;     // 性别
	uint8_t age;          // 年龄

    struct _Patient* prev;
    struct _Patient* next;
} Patient;

Patient* PatientAdd(Doctor* doctor, const char* name);

Patient* PatientFindById(PatientIdType id);
Patient* PatientFindByName(const char* name);
Patient

#endif /* _PATIENT_H */
