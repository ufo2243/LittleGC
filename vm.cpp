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
		object->isMarked = 0;

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
			objectStack[i]
		}
	}
}

