
#include "his.h"
#include "doctor.h"
#include "lib.h"
#include "patient.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Patient* global_patients_queue = NULL;

PatientIdType current_id = 0;

static PatientIdType GenerateId() {
	return ++current_id;
}

Patient *PatientAdd(Doctor *doctor, const char *name) {
	if (!global_patients_queue) {
		global_patients_queue = ListInitPatient();
	}
	Patient* node = (Patient*)malloc(sizeof(Patient));
	node->doctor = doctor;
	node->id = GenerateId();
	strcpy_s(node->name, sizeof(node->name), name);
	ListInsertTailPatient(global_patients_queue, node);
	return node;
}

Patient *PatientFindById(PatientIdType id) {
	if (!global_patients_queue)
		return NULL;

	Patient* cur = global_patients_queue->next;
	while (cur != global_patients_queue) {
		if (cur->id == id) {
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

Patient *PatientFindByName(const char* name) {
	if (!global_patients_queue)
		return NULL;
	Patient* cur = global_patients_queue->next;
	while (cur != global_patients_queue) {
		if (strcmp(cur->name, name) == 0) {
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
