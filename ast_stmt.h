/* File: ast_stmt.h
 * ----------------
 * The Stmt class and its subclasses are used to represent
 * statements in the parse tree.  For each statment in the
 * language (for, if, return, etc.) there is a corresponding
 * node class for that construct. 
 *
 * pp5: You will need to extend the Stmt classes to implement
 * code generation for statements.
 */


#ifndef _H_ast_stmt
#define _H_ast_stmt

#include "list.h"
#include "ast.h"

class Decl;
class VarDecl;
class Expr;
class Stmt;

Type* fanOutStatement(Stmt* stmt, Scope* scope);
  
class Program : public Node
{
  protected:
     List<Decl*> *decls;
     
  public:
     Program(List<Decl*> *declList);
     void Check();
     void Emit();
};

class Stmt : public Node
{
  public:
     Stmt() : Node() {}
     Stmt(yyltype loc) : Node(loc) {}
     virtual ~Stmt(){}

     Type* Check(Scope* scope);
};

class StmtBlock : public Stmt 
{
  protected:
    List<VarDecl*> *decls;
    List<Stmt*> *stmts;
    
  public:
    StmtBlock(List<VarDecl*> *variableDeclarations, List<Stmt*> *statements);
    Type* Check(Scope* scope);
};

  
class ConditionalStmt : public Stmt
{
  protected:
    Expr *test;
    Stmt *body;
  
  public:
    ConditionalStmt(Expr *testExpr, Stmt *body);
    Type* Check(Scope* scope);
    Expr* getTest(){ return test; }
};

class LoopStmt : public ConditionalStmt 
{
  public:
    LoopStmt(Expr *testExpr, Stmt *body)
            : ConditionalStmt(testExpr, body) {}
    Type* Check(Scope* scope);
};

class ForStmt : public LoopStmt 
{
  protected:
    Expr *init, *step;
  
  public:
    ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
    Type* Check(Scope* scope);
};

class WhileStmt : public LoopStmt 
{
  public:
    WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}
    Type* Check(Scope* scope);
};

class IfStmt : public ConditionalStmt 
{
  protected:
    Stmt *elseBody;
  
  public:
    IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);
    Type* Check(Scope* scope);
};

class BreakStmt : public Stmt 
{
  public:
    BreakStmt(yyltype loc) : Stmt(loc) {}
    Type* Check(Scope* scope);
};

class ReturnStmt : public Stmt  
{
  protected:
    Expr *expr;
  
  public:
    ReturnStmt(yyltype loc, Expr *expr);
    Type* Check(Scope* scope);
};

class PrintStmt : public Stmt
{
  protected:
    List<Expr*> *args;
    
  public:
    PrintStmt(List<Expr*> *arguments);
    Type* Check(Scope* scope);
};


class IntConstant;

class Case : public Node
{
  protected:
    IntConstant *value;
    List<Stmt*> *stmts;
    
  public:
    Case(IntConstant *v, List<Stmt*> *stmts);
    const char *GetPrintNameForNode() { return value ? "Case" :"Default"; }
    Type* Check(Scope* scope);
};

class SwitchStmt : public Stmt
{
  protected:
    Expr *expr;
    List<Case*> *cases;
    
  public:
    SwitchStmt(Expr *e, List<Case*> *cases);
    const char *GetPrintNameForNode() { return "SwitchStmt"; }
    Type* Check(Scope* scope);
};

#endif
