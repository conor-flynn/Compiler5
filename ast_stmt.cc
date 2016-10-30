/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"

Type* fanOutStatement(Stmt* s, Scope* scope) {
#if 0
	StmtBlock* sb = 		dynamic_cast<StmtBlock*>(s);
	ConditionalStmt* cs = 	dynamic_cast<ConditionalStmt*>(s);
	LoopStmt* ls = 			dynamic_cast<LoopStmt*>(s);
	ForStmt* fs = 			dynamic_cast<ForStmt*>(s);
	WhileStmt* ws = 		dynamic_cast<WhileStmt*>(s);
	IfStmt* is = 			dynamic_cast<IfStmt*>(s);
	SwitchStmt* ss = 		dynamic_cast<SwitchStmt*>(s);
	BreakStmt* bs =			dynamic_cast<BreakStmt*>(s);
	ReturnStmt* rs =		dynamic_cast<ReturnStmt*>(s);
	PrintStmt* ps = 		dynamic_cast<PrintStmt*>(s);

	Expr* ex = dynamic_cast<Expr*>(s);

	if (sb) {
		sb->Check(scope);
	} else if (cs) {
		cs->Check(scope);
	} else if (ls) {
		ls->Check(scope);
	} else if (fs) {
		fs->Check(scope);
	} else if (ws) {
		ws->Check(scope);
	} else if (is) {
		is->Check(scope);
	} else if (ss) {
		ss->Check(scope);
	} else if (ex) {
		ex->Check(scope);
	} else if (bs) {
		bs->Check(scope);
	} else if (rs) {
		rs->Check(scope);
	} else if (ps) {
		ps->Check(scope);
	}
	return NULL;
#endif
	return NULL;
}

Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
}

Scope* globalScope = NULL;
void Program::Check() {
    /* pp3: here is where the semantic analyzer is kicked off.
     *      The general idea is perform a tree traversal of the
     *      entire program, examining all constructs for compliance
     *      with the semantic rules.  Each node can have its own way of
     *      checking itself, which makes for a great use of inheritance
     *      and polymorphism in the node classes.
     */
#if 0
     Scope* globalScope = new Scope(NULL);
     for (int i = 0; i < decls->NumElements(); i++) {
     	Decl* dec = decls->Nth(i);
     	dec->ShallowCheck(globalScope);
     }

     

     for (int i = 0; i < decls->NumElements(); i++) {
     	Decl* dec = decls->Nth(i);     
     	Scope* normalScope = new Scope(globalScope);
     	fanOutDeclaration(dec, normalScope);   
     }
#endif
     scope = new Scope();
     for (int i = 0; i < decls->NumElements(); i++) {
     	decls->Nth(i)->tsaPreCheck(scope);
     }
     globalScope = scope;
     for (int i = 0; i < decls->NumElements(); i++) {
     	decls->Nth(i)->Check(scope);
     }
}

void Program::Emit() {
	
}

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    (decls=d)->SetParentAll(this);
    (stmts=s)->SetParentAll(this);
}

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) { 
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this); 
    (body=b)->SetParent(this);
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) { 
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init=i)->SetParent(this);
    (step=s)->SetParent(this);
}

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) { 
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}


ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}
  
PrintStmt::PrintStmt(List<Expr*> *a) {    
    Assert(a != NULL);
    (args=a)->SetParentAll(this);
}


Case::Case(IntConstant *v, List<Stmt*> *s) {
    Assert(s != NULL);
    value = v;
    if (value) value->SetParent(this);
    (stmts=s)->SetParentAll(this);
}

SwitchStmt::SwitchStmt(Expr *e, List<Case*> *c) {
    Assert(e != NULL && c != NULL);
    (expr=e)->SetParent(this);
    (cases=c)->SetParentAll(this);
}












Type* Stmt::Check(Scope* scope) {
#if 0
	return fanOutStatement(this, scope);
#endif
	return NULL;
}

Type* StmtBlock::Check(Scope* scope) {
#if 0
	Scope* blockScope = new Scope(scope);

	for (int i = 0; i < decls->NumElements(); i++) {
		Decl* d = decls->Nth(i);
		fanOutDeclaration(d, blockScope);
	}

	for (int i = 0; i < stmts->NumElements(); i++) {
		Stmt* s = stmts->Nth(i);
		fanOutStatement(s, blockScope);
	}
	// Statement blocks cannot be used on RHS, so they need no return value.
	return Type::errorType;
#endif
	return NULL;
}

Type* ConditionalStmt::Check(Scope* scope) {
#if 0
	LoopStmt* ls = dynamic_cast<LoopStmt*>(this);
	IfStmt* is = dynamic_cast<IfStmt*>(this);

	if (ls) {
		ls->Check(scope);
	} else if (is) {
		is->Check(scope);
	}
	// Conditional statements cannot be used on RHS, so they need no return value.
	return Type::errorType;
#endif
	return NULL;
}

Type* LoopStmt::Check(Scope* scope) {
#if 0
	ForStmt* fs = dynamic_cast<ForStmt*>(this);
	WhileStmt* ws = dynamic_cast<WhileStmt*>(this);

	if (fs) {
		fs->Check(scope);
	} else if (ws) {
		ws->Check(scope);
	}
	// Loop statements cannot be used on RHS, so they need no return value.
#endif
	return Type::errorType;
}

Type* IfStmt::Check(Scope* scope) {
#if 0
	Scope* testScope = new Scope(scope);
	Type* testing = getTest()->Check(testScope);
	if (testing != Type::errorType && !testing->IsEquivalentTo(Type::boolType)) {
		ReportError::TestNotBoolean(getTest());
	}

	Scope* ifBodyScope = new Scope(testScope);
	this->body->Check(ifBodyScope);

	Scope* elseBodyScope = new Scope(scope);
	this->elseBody->Check(elseBodyScope);
	// If statements cannot be used on RHS, so they need no return value.
#endif
	return Type::errorType;
}

Type* ForStmt::Check(Scope* scope) {
#if 0
	Scope* initScope = new Scope(scope);
	init->Check(initScope);

	Scope* testScope = new Scope(initScope);
	Type* testing = getTest()->Check(testScope);
	if (testing != Type::errorType && !testing->IsEquivalentTo(Type::boolType)) {
		ReportError::TestNotBoolean(getTest());
	}

	Scope* stepScope = new Scope(testScope);
	step->Check(stepScope);

	Scope* bodyScope = new Scope(stepScope);
	bodyScope->inLoop = true;
	this->body->Check(bodyScope);

	// For statements cannot be used on RHS, so they need no return value.
#endif
	return Type::errorType;
}

Type* WhileStmt::Check(Scope* scope) {
#if 0
	Scope* testScope = new Scope(scope);
	Type* testing = getTest()->Check(testScope);
	if (testing != Type::errorType && !testing->IsEquivalentTo(Type::boolType)) {
		ReportError::TestNotBoolean(getTest());
	}

	Scope* bodyScope = new Scope(testScope);	
	bodyScope->inLoop = true;
	this->body->Check(bodyScope);
	// While statements cannot be used on RHS, so they need no return value.
#endif
	return Type::errorType;
}

Type* Case::Check(Scope* scope) {
	// Case statements cannot be used on RHS, so they need no return value.
	return Type::errorType;
}

Type* SwitchStmt::Check(Scope* scope) {
	return Type::errorType;
}

Type* ReturnStmt::Check(Scope* scope) {
#if 0
	if (!scope->functionScope) {
		// Not within a function!?!?!?!?!?!?!
	} else {
		Type* expressionType = expr->Check(scope);
		Type* trueType = scope->functionScope->getReturnType();

		if (expressionType->IsEquivalentTo(trueType) || expressionType == Type::errorType) {
			// no op
		} else {
			ReportError::ReturnMismatch(this, expressionType, trueType);
		}
	}
#endif
	return Type::errorType;
}

Type* PrintStmt::Check(Scope* scope) {
#if 0
	for (int i = 0; i < args->NumElements(); i++) {
		Type* result = args->Nth(i)->Check(scope);

		bool isInt 		= result->IsEquivalentTo(Type::intType);
		bool isString 	= result->IsEquivalentTo(Type::stringType);
		bool isBool 	= result->IsEquivalentTo(Type::boolType);
		bool isError    = result == Type::errorType;

		if (isInt || isString || isBool || isError) {
			// All good
		} else {
			ReportError::PrintArgMismatch(args->Nth(i), i, result);
		}
	}
#endif
	return Type::errorType;
}

Type* BreakStmt::Check(Scope* scope) {
#if 0
	if (!scope->inLoop) {
		ReportError::BreakOutsideLoop(this);
	}
#endif
	return Type::errorType;
}