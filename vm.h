#ifndef _VM_H
#define _VM_H
#define MAX_STACK_SIZE 30000
#include <stdlib.h>
#include <assert.h>

namespace GC {

typedef enum {
    INT = 0,
    PAIR = 1 
} ObjectType;


typedef struct sObject{
    ObjectType objectType;
    union {
        int value;
        struct {
            sObject *first;
            sObject *second;
        };
    };
	int isMarked;				// 0 for not marked,not 0 for marked
	sObject* next;
}VMObject;

class VM {
public:
    VM();
    ~VM();
    void PushObject(VMObject* myObject);
    VMObject PopObject();
	VMObject* NewObject(ObjectType objectType);
	void gc();

private:
    int stackSize;
	void markAll();
	void cleanAll();
	void markObject(VMObject* myObject);
    VMObject objectStack[MAX_STACK_SIZE];
	VMObject* firstObject;
};

} // end namespace GC
#endif
