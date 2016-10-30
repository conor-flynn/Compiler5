/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>



IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
    value = val;
}
Type* IntConstant::Check(Scope* scope) { return Type::intType; }

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
    value = val;
}
Type* DoubleConstant::Check(Scope* scope) { return Type::doubleType; }

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    value = val;
}
Type* BoolConstant::Check(Scope* scope) { return Type::boolType; }

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
    Assert(val != NULL);
    value = strdup(val);
}
Type* StringConstant::Check(Scope* scope) { return Type::stringType; }
Type* NullConstant::Check(Scope* scope) { return Type::nullType; }

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
    Assert(tok != NULL);
    strncpy(tokenString, tok, sizeof(tokenString));
}
CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r) 
  : Expr(Join(l->GetLocation(), r->GetLocation())) {
    Assert(l != NULL && o != NULL && r != NULL);
    (op=o)->SetParent(this);
    (left=l)->SetParent(this); 
    (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r) 
  : Expr(Join(o->GetLocation(), r->GetLocation())) {
    Assert(o != NULL && r != NULL);
    left = NULL; 
    (op=o)->SetParent(this);
    (right=r)->SetParent(this);
}
   
  
ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this); 
    (subscript=s)->SetParent(this);
}
     
FieldAccess::FieldAccess(Expr *b, Identifier *f) 
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b; 
    if (base) base->SetParent(this); 
    (field=f)->SetParent(this);
}


Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}
 

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) { 
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}


NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this); 
    (elemType=et)->SetParent(this);
}

PostfixExpr::PostfixExpr(LValue *lv, Operator *o) : Expr(Join(lv->GetLocation(), o->GetLocation())) {
    Assert(lv != NULL && o != NULL);
    (lvalue=lv)->SetParent(this);
    (op=o)->SetParent(this);
}







































Type* fanOutExpression(Expr* e, Scope* scope) {
#if 0
	EmptyExpr* ee = dynamic_cast<EmptyExpr*>(e);

	CompoundExpr* ce = dynamic_cast<CompoundExpr*>(e);
	LValue* lv = dynamic_cast<LValue*>(e);
	Call* c = dynamic_cast<Call*>(e);
	NewArrayExpr* nae = dynamic_cast<NewArrayExpr*>(e);
	ReadIntegerExpr* rie = dynamic_cast<ReadIntegerExpr*>(e);
	ReadLineExpr* rle = dynamic_cast<ReadLineExpr*>(e);
	PostfixExpr* pfe = dynamic_cast<PostfixExpr*>(e);
	This* t = dynamic_cast<This*>(e);


	AssignExpr* ae = dynamic_cast<AssignExpr*>(e);
	NewExpr* ne = dynamic_cast<NewExpr*>(e);

	if (dynamic_cast<IntConstant*>(e)) {
		return Type::intType;
	} else if (dynamic_cast<DoubleConstant*>(e)) {
		return Type::doubleType;
	} else if (dynamic_cast<BoolConstant*>(e)) {
		return Type::boolType;
	} else if (dynamic_cast<StringConstant*>(e)) {
		return Type::stringType;
	} else if (dynamic_cast<NullConstant*>(e)) {
		return Type::nullType;
	} else if (ce) {
		return ce->Check(scope);
	} else if (lv) {
		ArrayAccess* aa = dynamic_cast<ArrayAccess*>(e);
		if (aa) {
			return aa->Check(scope);
		}
		FieldAccess* fa = dynamic_cast<FieldAccess*>(e);
		if (fa) {
			return fa->Check(scope);
		}
		return Type::errorType;
	} else if (c) {
		return c->Check(scope);
	} else if (nae) {
		return nae->Check(scope);
	} else if (t) {
		return t->Check(scope);
	} else if (ne) {
		return ne->Check(scope);
	}

#endif
	return Type::errorType;
}


























Type* Expr::Check(Scope* scope) {
#if 0
	Type* result = fanOutExpression(this, scope);
	return result;
#endif
	return NULL;
}

Type* EmptyExpr::Check(Scope* scope) {
	return Type::voidType;
}

bool acceptableMatch(Type* lhs, Type* rhs) {
#if 0
	return lhs->IsAcceptable(rhs);
#endif
	return false;
}

Type* CompoundExpr::Check(Scope* scope) {
#if 0
	if (!left) {
		LogicalExpr* le = dynamic_cast<LogicalExpr*>(this);
		if (le) {
			Type* righty = right->Check(scope);
			bool acceptable = righty->IsEquivalentTo(Type::boolType);
			if (acceptable) {
				return Type::boolType;
			} else {
				ReportError::IncompatibleOperand(op, righty);
				return Type::errorType;
			}
		}
	}

	Type* lhs = left ->Check(scope);
	Type* rhs = right->Check(scope);

	// If there was a problem evaluating an expression, we just assume everything works out fine and dandy, because the world is a magical place.
	if (lhs == Type::errorType) return Type::errorType;
	if (rhs == Type::errorType) return Type::errorType;

	Type* badReturn = getHighest(lhs, rhs);

	bool equal = lhs->IsEquivalentTo(rhs);
	bool i_or_d = 
			(lhs->IsEquivalentTo(Type::intType) || lhs->IsEquivalentTo(Type::doubleType));


	ArithmeticExpr* ar 	= dynamic_cast<ArithmeticExpr*>	(this);
	RelationalExpr* re 	= dynamic_cast<RelationalExpr*>	(this);
	EqualityExpr*   ee 	= dynamic_cast<EqualityExpr*>	(this);
	LogicalExpr*    le 	= dynamic_cast<LogicalExpr*>	(this);
	AssignExpr*     ae	= dynamic_cast<AssignExpr*>		(this);

	if (ar) {		
		if (equal && i_or_d) {
			return lhs;
		}
	} else if (re) {
		if (equal && i_or_d) {
			return Type::boolType;
		}
	} else if (ee) {
		NamedType* nt1 = dynamic_cast<NamedType*>(lhs);
		NamedType* nt2 = dynamic_cast<NamedType*>(rhs);

		bool oneIsObject = (nt1 || nt2);
		bool oneIsNull = 
				(lhs->IsEquivalentTo(Type::nullType)) ||
				(rhs->IsEquivalentTo(Type::nullType));
		bool acceptable = (oneIsObject && oneIsNull);


		if (equal || acceptable) {
			return Type::boolType;
		}
	} else if (le) {
		bool left = lhs->IsEquivalentTo(Type::boolType);
		bool right = rhs->IsEquivalentTo(Type::boolType);
		if (left || right) {	// TODO : This could be a huge problem?
								// object = (badExpression && goodExpression)
								// object = (error)			---> acceptable
								// object = (bool)			---> not acceptable
			return Type::boolType;
		}
			
	} else if (ae) {
		if (equal) {
			return lhs;
		}
	}

	ReportError::IncompatibleOperands(op, lhs, rhs);
	return Type::errorType;
#endif
	return NULL;
}

Type* ArrayAccess::Check(Scope* scope) {
#if 0
	Type* retval = Type::errorType;

	Type* baseType = base->Check(scope);
		ArrayType* at = dynamic_cast<ArrayType*>(baseType);
		if (at) {
			retval = at->getType();
		} else {
			ReportError::BracketsOnNonArray(base);
		}

	Type* subscriptType = subscript->Check(scope);
		if (subscriptType != Type::intType) {
			ReportError::SubscriptNotInteger(subscript);
		}
	return retval;
#endif
	return NULL;
}

Type* FieldAccess::Check(Scope* scope) {
#if 0
	if (base) {
		Type* baseType = base->Check(scope);

		if (baseType == Type::errorType) {
			return Type::errorType;
		}

		NamedType* nt = dynamic_cast<NamedType*>(baseType);
		if (nt) {
			char* classReference = nt->getId()->getName();


			Scope* current = scope;
			while (current != NULL) {

				Decl* d = current->declarations.Lookup(classReference);
				if (d) {
					ClassDecl* cd = dynamic_cast<ClassDecl*>(d);
					if (cd) {
						Type* fieldType = cd->findField(field);
						if (fieldType == NULL || fieldType == Type::errorType) {
							ReportError::FieldNotFoundInBase(field, baseType);
							return Type::errorType;
						} else {
							if (scope->classScope == NULL) {
								ReportError::InaccessibleField(field, baseType);
								return Type::errorType;
							} else {
								return fieldType;
							}
						}
					}
				}
				current = current->parent;
			}
			ReportError::FieldNotFoundInBase(field, baseType);
			return Type::errorType;
		} else {
			ReportError::FieldNotFoundInBase(field, baseType);
			return Type::errorType;
		}
	} else {
		Scope* current = scope;
		while (current != NULL) {
			Decl* d = current->declarations.Lookup(field->getName());
			if (d) {
				VarDecl* vd = dynamic_cast<VarDecl*>(d);
				if (vd) {
					return vd->getReturnType();
				}
			}
			current = current->parent;
		}

		if (scope->classScope) {
			// We are within a class, so we should also look for inherited variables
			Type* memberType = scope->classScope->findField(field);
			if (!(memberType == Type::errorType)) {
				return memberType;
			}
		}

		ReportError::IdentifierNotDeclared(field, LookingForVariable);
		return Type::errorType;
	}
#endif
	return NULL;
}

Decl* getDeclaration(Identifier* id, Scope* scope) {
#if 0
	Assert(id);
	Assert(scope);

	Scope* current = scope;

	while (current != NULL) {

		Decl* d = current->declarations.Lookup(id->getName());

		if (d) {
			return d;
		}
		current = current->parent;
	}
#endif
	return NULL;
}

void compareFunctions(Identifier* fnId, List<Type*>* provided, List<Expr*>* supplied, List<VarDecl*>* declarations, Scope* scope) {
#if 0
	int trueCount = declarations->NumElements();
	int useCount = provided->NumElements();

	if (trueCount != useCount) {
		ReportError::NumArgsMismatch(fnId, trueCount, useCount);
	} else {
		for (int i = 0; i < trueCount; i++) {
			VarDecl* var 	= declarations->Nth(i);

			Type* dtype = var->getReturnType();
			Type* utype = provided->Nth(i);

			if (acceptableMatch(dtype, utype)) {

			} else {
				ReportError::ArgMismatch(supplied->Nth(i), i, utype, dtype);
			}
		}
	}
#endif
}

Type* Call::Check(Scope* scope) {
#if 0
	List<Type*>* eval = new List<Type*>();
	for (int i = 0; i < actuals->NumElements(); i++) {
		eval->Append(actuals->Nth(i)->Check(scope));
	}

	// Do we even have a base?
	if (base) {
		Type* baseType = base->Check(scope);

		if (baseType == Type::errorType) {
			return Type::errorType;
		}

		NamedType* baseClass = dynamic_cast<NamedType*>(baseType);
		ArrayType* baseArray = dynamic_cast<ArrayType*>(baseType);

		// Is our base a non-default and non-array type?
		if (baseClass) {

			Decl* daddy = getDeclaration(baseClass->getId(), scope);
			ClassDecl* cd;

			// Can we find the declaration?
			if (daddy) {
				cd = dynamic_cast<ClassDecl*>(daddy);

				// Is our declaration a class?
				if (cd) {

					// For each member declaration in the class, we are looking for a particular function
					for (int i = 0; i < cd->getMembers()->NumElements(); i++) {
						Decl* d = cd->getMembers()->Nth(i);
						FnDecl* fd = dynamic_cast<FnDecl*>(d);

						// Is this class member a function?
						if (fd) {

							// Does the function have the same name as the function we are calling?
							if (strcmp(field->getName(), fd->getId()->getName()) == 0) {

								// We have found the function!
								compareFunctions(field, eval, actuals, fd->getFormals(), scope);
								return fd->getReturnType();
							} else {
								// We found a function, but it's name doesn't match.
								// Continue.
							}
						} else {
							// We found a declaration, but it isn't a function.
							// Continue.
						}
					}

					// We found the class, but found no matching function.
					ReportError::FieldNotFoundInBase(field, baseType);
					return Type::errorType;

				} else {
					// The declaration provided by our base is NOT a class.
					ReportError::FieldNotFoundInBase(field, baseType);
					return Type::errorType;
				}
			} else {
				// We could not find the declaration when supplied a NamedType. So we should NOT report errors on the field.

				//ReportError::FieldNotFoundInBase(field, baseType);
				//return Type::errorType;
			}
		} else if (baseArray) {
			if (strcmp(field->getName(), "length") != 0) {
				ReportError::FieldNotFoundInBase(field, baseType);
				return Type::errorType;	
			}
		} else {
			// We are trying to access a field off of an object that is NOT a class...!
			ReportError::FieldNotFoundInBase(field, baseType);
			return Type::errorType;
		}
	} else {

		char* functionName = field->getName();

		Scope* current = scope;
		while (current != NULL) {

			Decl* d = current->declarations.Lookup(functionName);
			if (d) {
				FnDecl* fd = dynamic_cast<FnDecl*>(d);
				if (fd) {
					compareFunctions(field, eval, actuals, fd->getFormals(), scope);
					return fd->getReturnType();
				}
			}
			current = current->parent;
		}
		ReportError::IdentifierNotDeclared(field, LookingForFunction);
		return Type::errorType;
	}
#endif
	return Type::errorType;
}

Type* NewExpr::Check(Scope* scope) {
#if 0
	Scope* current = scope;
	while (current != NULL) {
		Decl* d = current->declarations.Lookup(cType->getId()->getName());
		if (d) {
			ClassDecl* cd = dynamic_cast<ClassDecl*>(d);
			if (cd) {
				return cType;
			}
		}
		current = current->parent;
	}
	ReportError::IdentifierNotDeclared(cType->getId(), LookingForClass);
	return Type::errorType;
#endif
	return NULL;
}

Type* NewArrayExpr::Check(Scope* scope) {
#if 0
	Type* sizeType = size->Check(scope);
	Assert(sizeType);

	if (sizeType != Type::intType) {
		ReportError::NewArraySizeNotInteger(size);
		return Type::errorType;
	}

	NamedType* nt = dynamic_cast<NamedType*>(elemType);

	if (nt) {
		Scope* current = scope;
		bool found = false;
		while (current != NULL) {

			Decl* d = current->declarations.Lookup(nt->getId()->getName());
			if (d) {
				ClassDecl* cd = dynamic_cast<ClassDecl*>(d);
				if (cd) {
					found = true;
				}
			}
			current = current->parent;
		}
		if (!found) {
			ReportError::IdentifierNotDeclared(nt->getId(), LookingForClass);
			return Type::errorType;
		}
	}

	

	// on bad3.decaf, line 14 makes no sense:
	// 		NewArray("hello", string);
	// The second parameter is supposed to be a type, but when the first parameter is incorrect, we are just supposed to exit out of the checking process?
	Assert(elemType);
	ArrayType* at = new ArrayType(yyltype(), elemType);
	Assert(at);
	return at;
#endif
	return NULL;
}

Type* This::Check(Scope* scope) {
#if 0
	if (!scope->classScope) {
		ReportError::ThisOutsideClassScope(this);
	}
	return Type::errorType;
#endif
	return NULL;
}



















// If either type is an error, return errorType;
// If types are equal, return that type;
// Else, return errorTyp;
Type* getLowest(Type* first, Type* second) {
#if 0
	if (first->IsEquivalentTo(Type::errorType) || second->IsEquivalentTo(Type::errorType)) {
		return Type::errorType;
	}
	if (first->IsEquivalentTo(second)) {
		return first;
	}
#endif
	return Type::errorType;
}

// If there is a 'non-error' type within the two given, return that 'valid' type.
// Otherwise, just return errorType;
Type* getHighest(Type* first, Type* second) {
#if 0
	if (!first->IsEquivalentTo(Type::errorType)) return first;
	if (!second->IsEquivalentTo(Type::errorType)) return second;
	return Type::errorType;
#endif
	return NULL;
}

Type* searchScopeById(char* id, Scope* scope) {
#if 0
	Scope* temp = scope;

	while (temp != NULL) {
		Decl* d = scope->declarations.Lookup(id);
		VarDecl* vd = dynamic_cast<VarDecl*>(d);
		ClassDecl* cd = dynamic_cast<ClassDecl*>(d);
		InterfaceDecl* id = dynamic_cast<InterfaceDecl*>(d);

		if (vd) {
			return vd->getReturnType();
		} else if (cd) {
			return new Type(cd->getId()->getName());
		} else if (id) {
			return new Type(id->getId()->getName());
		} else {
			return Type::errorType;
		}

		temp = temp->parent;
	}
#endif
	return Type::errorType;
}