#ifndef SCOPE_H
#define SCOPE_H


#include "hashtable.h"
#include "ast.h"
#include "location.h"
#include "mips.h"

class Node;
class Scope;

class Symbol {
	public:	// who needs the safety of protected anyways ayy lmao
		int symbol_type;
		Scope* owner;
		Location* location;
		Symbol(int type, Node* origin);
		Symbol(int type, Node* origin, Location* place);
		Symbol(int type, Node* origin, Scope* info);
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
};
#endif