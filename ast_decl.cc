/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
        
         
Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
    Assert(n != NULL);
    (id=n)->SetParent(this); 
    (checked=false);
}

void fanOutDeclaration(Decl* d, Scope* scope) {
#if 0
	VarDecl* vd = dynamic_cast<VarDecl*>(d);
	FnDecl* fd = dynamic_cast<FnDecl*>(d);
	ClassDecl* cd = dynamic_cast<ClassDecl*>(d);
	InterfaceDecl* id = dynamic_cast<InterfaceDecl*>(d);

	if (vd) {
		vd->Check(scope);
	} else if (fd) {
		fd->Check(scope);
	} else if (cd) {
		cd->Check(scope);
	} else if (id) {
		id->Check(scope);
	}
#endif
}

VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
    Assert(n != NULL && t != NULL);
    (type=t)->SetParent(this);
}
  

ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n) {
    // extends can be NULL, impl & mem may be empty lists but cannot be NULL
    Assert(n != NULL && imp != NULL && m != NULL);     
    extends = ex;
    if (extends) extends->SetParent(this);
    (implements=imp)->SetParentAll(this);
    (members=m)->SetParentAll(this);
}


InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
    Assert(n != NULL && m != NULL);
    (members=m)->SetParentAll(this);
}

	
FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
    Assert(n != NULL && r!= NULL && d != NULL);
    (returnType=r)->SetParent(this);
    (formals=d)->SetParentAll(this);
    body = NULL;
}

void FnDecl::SetFunctionBody(Stmt *b) { 
    (body=b)->SetParent(this);
}











void Decl::ShallowCheck(Scope* scope) {
#if 0
	if (scopeHasLocalDeclaration(this, scope)) {
		ReportError::DeclConflict(
						this, 
						scope->declarations.Lookup(this->id->getName()));
		return;
	}
	scope->declarations.Enter(this->id->getName(), this);
#endif
}

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


bool searchScopeForType(char* typeName, Scope* scope) {
#if 0
	Scope* currentScope = scope;
	while (currentScope != NULL) {
		if (currentScope->declarations.Lookup(typeName) != 0) {
			return true;
		}
		currentScope = currentScope->parent;
	}
	return false;
#endif
	return false;
}

ClassDecl* findClass(char* className, Scope* scope) {

#if 0
	ClassDecl* retval;
	Decl* temp;

	Scope* currentScope = scope;

	while (currentScope != NULL) {
		temp = currentScope->declarations.Lookup(className);
		if (temp) {
			retval = dynamic_cast<ClassDecl*>(temp);
			if (retval) {
				return retval;
			}
		}
		currentScope = currentScope->parent;
	}
	return NULL;
#endif
	return NULL;
}

InterfaceDecl* findInterface(char* interfaceName, Scope* scope) {

#if 0
	InterfaceDecl* interDecl;
	Decl* temp;

	Scope* currentScope = scope;

	while (currentScope != NULL) {
		temp = currentScope->declarations.Lookup(interfaceName);
		if (temp) {
			interDecl = dynamic_cast<InterfaceDecl*>(temp);
			if (interDecl) {
				return interDecl;
			}
		}
		currentScope = currentScope->parent;
	}
#endif
	return NULL;
}

void scopelooping(char* name, Scope* scope) {
#if 0
	Scope* currentScope = scope;


	while (currentScope != NULL) {



		currentScope = currentScope->parent;
	}
#endif
}

bool scopeHasLocalDeclaration(Decl* decl, Scope* scope) {
#if 0
	return scope->declarations.Lookup(decl->getId()->getName()) != NULL;
#endif
	return false;
}

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


void Decl::Check(Scope* scope) {

}

void searchType(Type* type, Scope* scope) {
#if 0
	NamedType* name = dynamic_cast<NamedType*>(type);
	ArrayType* array = dynamic_cast<ArrayType*>(type);
	bool foundType = false;

	if (name) {
		foundType = searchScopeForType(name->getId()->getName(), scope);
		if (!foundType) {
			ReportError::IdentifierNotDeclared(name->getId(), LookingForType);
		}
	}else if (array) {
		searchType(array->getType(), scope);
	}
#endif
}

void VarDecl::Check(Scope* scope) {
#if 0
	if (this->checked) return;
	this->checked = true;

	// Variables should still check local declaration. When the global scan goes through, the variable declaration conflict will not happen cause it only looks at current scope.
	if (scopeHasLocalDeclaration (this, scope)) {
		ReportError::DeclConflict(this, scope->declarations.Lookup(this->id->getName()));
		return;
	}
	scope->declarations.Enter(this->id->getName(), this);
	searchType(getReturnType(), scope);
#endif
}

void FnDecl::Check(Scope* scope) {
#if 0
	if (this->checked) return;
	this->checked = true;

	if (scopeHasLocalDeclaration(this, scope)) {
		ReportError::DeclConflict(
						this, 
						scope->declarations.Lookup(this->id->getName()));
		return;						
	}
	scope->declarations.Enter(this->id->getName(), this);

	searchType(getReturnType(), scope);

	Scope* paramScope = new Scope(scope);
	for (int i = 0; i < this->formals->NumElements(); i++) {
		VarDecl* vd = this->formals->Nth(i);
		vd->Check(paramScope);
	}

	Scope* bodyScope = new Scope(paramScope);
	bodyScope->functionScope = this;
	this->body->Check(bodyScope);
#endif
}

Type* ClassDecl::findField(Identifier* field) {
#if 0
	for (int i = 0; i < members->NumElements(); i++) {
		Decl* d = members->Nth(i);
		VarDecl* vd = dynamic_cast<VarDecl*>(d);
		if (vd) {
			if (strcmp(vd->getId()->getName(), field->getName()) == 0) {
				return vd->getReturnType();
			}
		}
	}
	Decl* d = parentMembers->Lookup(field->getName());
	if (d) {
		VarDecl* vd = dynamic_cast<VarDecl*>(d);
		if (vd) {
			return vd->getReturnType();
		}
	}
	return Type::errorType;
#endif
	return NULL;
}

void ClassDecl::CheckParent(Scope* scope) {
#if 0
	if (this->extends != NULL) {
		// Find the class associated with 'extends' and retrieve the variables and functions.

		ClassDecl* retval;
		if ( (retval=findClass(this->extends->getId()->getName(), scope)) != NULL) {

			Hashtable<Decl*>* parent = new Hashtable<Decl*>();
			Hashtable<Decl*>* interface = new Hashtable<Decl*>();

			retval->passToSubclass(scope, parent, interface);

			this->parentMembers = parent;
			this->interfaceMembers = interface;

		} else {
			// If we cannot find the extension, give error;
			ReportError::IdentifierNotDeclared(this->extends->getId(), LookingForClass);
		}
	}
#endif
}
void ClassDecl::CheckInterfaces(Scope* scope) {
#if 0
	if (this->implements->NumElements() != 0) {
		this->interfaceMembers = new Hashtable<Decl*>();
		// Find all of the interface function headers associated with each interface listed.
		for (int j = 0; j < this->implements->NumElements(); j++) {

			NamedType* currentInterface = this->implements->Nth(j);
			InterfaceDecl* retval;
			bool foundInterface = false;

			if ((retval = findInterface(currentInterface->getId()->getName(), scope)) != NULL) {
				foundInterface = true;

				Scope* childScope = new Scope(scope->parent);
				retval->Check(childScope);
				retval->addInterface(this->interfaceMembers);
			}

			if (!foundInterface) {
				ReportError::IdentifierNotDeclared(currentInterface->getId(), LookingForInterface);
			}

		}
	}
#endif
}
void ClassDecl::passToSubclass(
			Scope* useThisScope, 
			Hashtable<Decl*>* parent, 
			Hashtable<Decl*>* interface) 
{
#if 0
	this->Check(useThisScope);
	Decl* d;
	for (int i = 0; i < members->NumElements(); i++) {
		d = members->Nth(i);
		parent->Enter(d->getId()->getName(), d);
	}

	if (parentMembers) {
		Iterator<Decl*> inherit = parentMembers->GetIterator();
		while ((d=inherit.GetNextValue())!=NULL) {
			parentMembers->Enter(d->getId()->getName(), d);
		}
	}
#endif
}

void ClassDecl::Check(Scope* scope) {
#if 0
	if (this->checked) return;
	this->checked = true;

	scope->classScope = this;

	this->CheckParent(scope);
	this->CheckInterfaces(scope);

	Scope* bodyScope = new Scope(scope);
	for (int i = 0; i < this->members->NumElements(); i++) {
		Decl* d = this->members->Nth(i);
		fanOutDeclaration(d, bodyScope);
		checkDeclarationAgainstParent(d);
		checkDeclarationAgainstInterface(d);
	}
#endif
}


void InterfaceDecl::addInterface(Hashtable<Decl*>* source) {
#if 0
	for (int i = 0; i < members->NumElements(); i++) {
		Decl* d = members->Nth(i);
		source->Enter(d->getId()->getName(), d);
	}
#endif
}

bool compareTypes(Type* lhs, Type* rhs) {
#if 0
	NamedType* named = dynamic_cast<NamedType*>(lhs);
	ArrayType* array = dynamic_cast<ArrayType*>(lhs);

	if (named) {
		return named->IsEquivalentTo(rhs);
	} else if (array) {
		return array->IsEquivalentTo(rhs);
	} else {
		return lhs->IsEquivalentTo(rhs);
	}
#endif
	return false;
}

void compareFunctions(FnDecl* source, FnDecl* other) {
#if 0
	// Return type mismatch
	if (!compareTypes(source->getReturnType(), other->getReturnType())){
		ReportError::OverrideMismatch(source);
		return;
	}

	int currentNumbers = source->getFormals()->NumElements();
	int targetNumbers = other->getFormals()->NumElements();
	if (currentNumbers == targetNumbers) {
		for (int i = 0; i < currentNumbers; i++) {

			VarDecl* currentFormal = source->getFormals()->Nth(i);
			VarDecl* targetFormal = other->getFormals()->Nth(i);

			Type* cur = currentFormal->getReturnType();
			Type* tar = targetFormal->getReturnType();

			bool match = compareTypes(cur, tar);
			if (!match) {
				ReportError::OverrideMismatch(source);
				return;
			}
		}
	} else {
		ReportError::OverrideMismatch(source);
		return;
	}
#endif
}

void ClassDecl::checkDeclarationAgainstInterface(Decl* source) {
#if 0
	if (interfaceMembers == NULL) return;

	Decl* other = interfaceMembers->Lookup(source->getId()->getName());
	if (!other) return;

	int localType = decodeDeclaration(source);

	if (localType != FnD) {
		ReportError::DeclConflict(source, other);
		return;
	}

	FnDecl* localFunction = dynamic_cast<FnDecl*>(source);
	FnDecl* otherFunction = dynamic_cast<FnDecl*>(other);
	compareFunctions(localFunction, otherFunction);
#endif
}

// We are trying to check 'local' against all inherited members to see if we are breaking a rule.
void ClassDecl::checkDeclarationAgainstParent(Decl* local) {
#if 0
	if (parentMembers == NULL || parentMembers == 0) return;

	// If there is no parent function, return;
	Decl* loaded = parentMembers->Lookup(local->getId()->getName());
	if (!loaded) return;

	char* loadName = loaded->getId()->getName();
	char* current = local->getId()->getName();

	int loadType = decodeDeclaration(loaded);
	int currType = decodeDeclaration(local);

	// If the declaration types don't agree, it is a situation such that VarDecl != ClassDecl
	if (loadType != currType) {
		ReportError::DeclConflict(local, loaded);
		return;
	}

	switch (loadType) {

		// Both are functions.
		case FnD:
		{
			FnDecl* source = dynamic_cast<FnDecl*>(local);
			FnDecl* other  = dynamic_cast<FnDecl*>(loaded);
			compareFunctions(source, other);	
			return;		
		}
		break;
		case VarD:
		{
			ReportError::DeclConflict(local, loaded);
			return;
		}
		break;
		default:
		{

		}
		break;
	}
#endif	
}
void InterfaceDecl::Check(Scope* scope) {
#if 0
	Scope* bodyScope = new Scope(scope);
	for (int i = 0; i < members->NumElements(); i++) {
		Decl* d = members->Nth(i);
		fanOutDeclaration(d, bodyScope);
	}
	scope->declarations.Enter(this->getId()->getName(), this);
#endif
}
int decodeDeclaration(Decl* d) {
#if 0
	VarDecl* vd = dynamic_cast<VarDecl*>(d);
	FnDecl* fd = dynamic_cast<FnDecl*>(d);
	ClassDecl* cd = dynamic_cast<ClassDecl*>(d);
	InterfaceDecl* id = dynamic_cast<InterfaceDecl*>(d);

	if (vd) {
		return VarD;
	} else if (fd) {
		return FnD;
	} else if (cd) {
		return ClassD;
	} else if (id) {
		return InterfaceD;
	}
#endif
	return -1;
}