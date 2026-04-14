#ifndef _RECORD_H
#define _RECORD_H

#include <stdint.h>

typedef uint32_t RecordIdType;

typedef struct _Record {
	RecordIdType id;
	Patient* patient; // 就诊患者
	Doctor* doctor;   // 就诊医生

	struct _Record* prev;
	struct _Record* next;
} Record;

#endif /* _RECORD_H */