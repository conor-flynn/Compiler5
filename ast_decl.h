/* File: ast_decl.h
 * ----------------
 * In our parse tree, Decl nodes are used to represent and
 * manage declarations. There are 4 subclasses of the base class,
 * specialized for declarations of variables, functions, classes,
 * and interfaces.
 *
 * pp5: You will need to extend the Decl classes to implement 
 * code generation for declarations.
 */

#ifndef _H_ast_decl
#define _H_ast_decl

#include "ast.h"
#include "list.h"

class Type;
class NamedType;
class Identifier;
class Stmt;

class Decl : public Node 
{
  protected:
    Identifier *id;
    //DeclType declType;
  
  public:
  	bool checked;
    Decl(Identifier *name);
    virtual ~Decl(){}
    friend std::ostream& operator<<(std::ostream& out, Decl *d) { return out << d->id; }

    void Check(Scope* scope);
    void ShallowCheck(Scope* scope);
    Identifier* getId() { return id; }
};

class VarDecl : public Decl 
{
  protected:
    Type *type;
    
  public:
    VarDecl(Identifier *name, Type *type);

    void Check(Scope* scope);
    bool searchScope(char* name, Scope* scope);
    Type* getReturnType(){ return type; }
};

class ClassDecl : public Decl 
{
  protected:
    List<Decl*> *members;
    NamedType *extends;
    List<NamedType*> *implements;

  public:
  	Hashtable<Decl*>* parentMembers;
  	Hashtable<Decl*>* interfaceMembers;

    ClassDecl(Identifier *name, NamedType *extends, 
              List<NamedType*> *implements, List<Decl*> *members);

    void Check(Scope* scope);
    void CheckParent(Scope* scope);
    void CheckInterfaces(Scope* scope);
    
    void passToSubclass(
    		Scope* useThisScope, 
    		Hashtable<Decl*>* parent,
    		Hashtable<Decl*>* interface);
    void checkDeclarationAgainstParent(Decl* d);
    void checkDeclarationAgainstInterface(Decl* d);
    List<Decl*>* getMembers(){ return members; }
    Type* findField(Identifier* field);
};

class InterfaceDecl : public Decl 
{
  protected:
    List<Decl*> *members;
    
  public:
    InterfaceDecl(Identifier *name, List<Decl*> *members);

    void addInterface(Hashtable<Decl*>* source);
    void Check(Scope* scope);
};

class FnDecl : public Decl 
{
  protected:
    List<VarDecl*> *formals;
    Type *returnType;
    Stmt *body;
    
  public:
    FnDecl(Identifier *name, Type *returnType, List<VarDecl*> *formals);
    void SetFunctionBody(Stmt *b);

    void Check(Scope* scope);
    Type* getReturnType(){ return returnType; }
    List<VarDecl*>* getFormals(){ return formals; }
};



















enum DeclType { VarD, ClassD, InterfaceD, FnD };
void fanOutDeclaration(Decl* d, Scope* scope);
int decodeDeclaration(Decl* d);

bool searchScopeForType(char* typeName, Scope* scope);
void searchType(Type* type, Scope* scope);

ClassDecl* findClass(char* className, Scope* scope);
InterfaceDecl* findInterface(char* interfaceName, Scope* scope);

void compareFunctions(FnDecl* source, FnDecl* other);
bool compareTypes(Type* lhs, Type* rhs);

void scopelooping(char* name, Scope* scope);
bool scopeHasLocalDeclaration(Decl* decl, Scope* scope);





















#endif
