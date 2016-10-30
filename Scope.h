#ifndef SCOPE_H
#define SCOPE_H


#include "hashtable.h"
#include "location.h"
#include "mips.h"
#include "ast.h"

class Node;
class Scope;

enum {VARIABLE, FUNCTION, CLASS};

class Symbol {
	public:	//  ayy lmao
		int symbolType;
		Node* attachment;
		Scope* owner;
		Location* location;
		Symbol(int type, Node* origin);
		//Symbol(int type, Node* origin, Location* place);
		//Symbol(int type, Node* origin, Scope* info);

		Node* getAttachment() { return attachment; }
};

class Scope {
	public:

		Scope* parent;
		//Hashtable<Decl*> declarations;	// Decl* isn't good enough
		//Hashtable<Item*> table;
		Hashtable<Symbol*>* table;
		//Hashtable<Decl*> inheritance;

		//Node* scopeOwner;			// Class/Function: Who owns this scope;
		Node* classNode;	// More detailed than 'scopeOwner'
		Node* loopNode;

		Scope* classScope;		//
		//Scope* extendsScope;	// Scope from 'extends'
		//ClassDecl* classScope;	// If classScope != NULL, then this scope is within a class.
		//FnDecl* functionScope;	// If functionScope != NULL< then this scope is within a function (for return statements);

		Scope();

		Symbol* findLocalSymbol(char* name);
		bool addVariableSymbol(char* name, Node* node);
};
#endif