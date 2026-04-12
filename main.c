// main.c

#include "his.h"
#include "lib.h"
#include "patient.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
	Patient* p1 = PatientAdd(NULL, "Bob");
	Patient* p2 = PatientAdd(NULL, "Alice");

	printf("Patient %s has id %u\n", p1->name, p1->id);
	printf("Patient %s has id %u\n", p2->name, p2->id);

	printf("find 1: %s\n", PatientFindById(1)->name);
	printf("find Alice: %d\n", PatientFindByName("Alice")->id);

	return 0;
}
