#include<iostream>
#include<string>

typedef struct node Node;

typedef struct plus {
	Node *left;
	Node *right;
}plus;

typedef struct conc {
	Node *left;
	Node *right;
}conc;

typedef struct fang {
	Node *child;
}fang;

typedef struct ou {
	Node *left;
	Node *right;
}ou;

typedef struct atom {
	bool *is_term;
	int *cod;  // 0 ou 1
	char *action;
	Node *child;
}atom
;

struct node {
	std::string clas;
	plus *plus_t;
	conc *conc_t;
	fang *fang_t;
	atom *atom_t;
	ou *ou_t;
};

// Gen functions :

node *GenConc(node *r, node *l) {
	node *val = new node;
	val->conc_t->left=l;
	val->conc_t->right=r;
	val->clas="conc";
	return val;
}

node *GenFang(node *c){
	node *val = new node;
	val->clas="fang";
	val->fang_t->child=c;
	return val;
}

node *GenPlus(node *r, node *l) {
	node *val = new node;
	val->plus_t->left=l;
	val->plus_t->right=r;
	val->clas="plus";
	return val;
}

node *GenOu(node *c){
	node *val = new node;
	val->clas="ou";
	val->ou_t->child=c;
	return val;
}

node *GenAtom(const char *a, int code, bool t){
	node *val = new node;
	val->clas="atom";
	val->atom_t->action=a;
	val->atom_t->cod=code;
	val->atom_t->is_term=t;
	return val;
}

void GenForet(){
	int S = 0;
	int N = 1;
	int E = 2;
	int T = 3;
	int F = 4;

	node *A[S] = GenConc(GenFang(GenConc(GenConc(GenConc(GenAtom("N",0,false),GenAtom("->",0,true)),GenAtom("E",0,false)),GenAtom(",",1,true))),GenAtom(";",0,true));
}
