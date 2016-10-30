#include "Scope.h"

Symbol::Symbol(int type, Node* origin) {
	// For variables
	this->symbolType = type;
	this->attachment = origin;
}

Scope::Scope() {
	parent = NULL;
	table = new Hashtable<Symbol*>();
	classNode = NULL;
	loopNode = NULL;
	classScope = NULL;
}

Symbol* Scope::findLocalSymbol(char* name) {
	Symbol* result = NULL;

	if ( (result = table->Lookup(name)) != NULL) {
		return result;
	} else {
		return NULL;
	}
}
bool Scope::addVariableSymbol(char* name, Node* node) {
	Symbol* addition = new Symbol(VARIABLE, node);
	table->Enter(name, addition, false);
	return true;
}