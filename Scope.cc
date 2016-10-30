#include "Scope.h"

Scope::Scope() {
	parent = NULL;
	table = new Hashtable<Symbol*>();
	classNode = NULL;
	loopNode = NULL;
	classScope = NULL;
}