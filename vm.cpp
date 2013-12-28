#include "vm.h"

namespace GC {
	VM::VM():stackSize(0) {
	}

	VM::~VM() {
	}

	void VM::PushObject(VMObject* myObject) {
		assert(stackSize < MAX_STACK_SIZE);
		objectStack[stackSize++] = myObject;
	}

	VMObject* VM::PopObject() {
		assert(stackSize != 0);
		return objectStack[stackSize--];
	}

	VMObject* VM::NewObject(ObjectType objectType) {
		VMObject* object = (VMObject *)malloc(sizeof(VMObject));
		assert(object != NULL);
		object->objectType = objectType;		
		switch (objectType) {
			case INT:
				object->value = 0;
				break;
			case PAIR:
				object->first = NULL;
				object->second = NULL;
				break;
		}
		object->isMark = 0;

		object->next = firstObject;
		firstObject = object;

		return object;
	}

	void VM::gc() {
		markAll();
		cleanAll();
	}

	void VM::markAll() {
		for (int i = 0; i < stackSize ; ++i) {
			markObject(objectStack[i]);
		}
	}

	void VM::markObject(VMObject* myObject) {
		if (myObject == NULL || myObject->isMark != 0) {
			return;
		}
		myObject->isMark = 1;
		switch (myObject->objectType) {
			case PAIR:
				markObject(myObject->first);
				markObject(myObject->second);
				break;
			case INT:
				break;
		}
	}

	void VM::cleanAll() {
		//find the first object which next is not NULL
		while (firstObject != NULL) {
			if (firstObject->isMark == 0) {
				VMObject* tempObject = firstObject;
				firstObject = firstObject->next;
				free(tempObject);
			}
			else {
				firstObject->isMark = 0;
				break;
			}
		}
		if (firstObject == NULL) {
			return;
		}

		VMObject* myObject = firstObject;
		while (myObject->next != NULL) {
			if (myObject->next->isMark == 1) {
				myObject->next->isMark = 0;
				myObject = myObject->next;
			}
			else {
				VMObject* tempObject = myObject->next;
				myObject->next = myObject->next->next;
				myObject = myObject->next;
				free(tempObject);
			}	
		}
	}
}

