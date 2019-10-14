#include<iostream>
#include<string>

/* typedef struct atom_type {
	std::string terminal;
	std::string nonter;
}atom_type; */

typedef struct node {
	std::string clas;
	plus *plus_t;
	conc *conc_t;
	fang *fang_t;
	atom *atom_t;
	ou *ou_t;
}node;

typedef struct plus {
	node *left;
	node *right;
}plus;

typedef struct conc {
	node *left;
	node *right;
}conc;

typedef struct fang {
	node *child;
}fang;

typedef struct ou {
	node *left;
	node *right;
}ou;

typedef struct atom {
	bool *is_term;
	int *cod;  // 0 ou 1
	char *action;
	node *child;
}atom
;

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

node *GenAtom(std::string *a, int *code, bool *t){
	node *val = new node;
	val->clas="atom";
	val->atom_t->action=a;
	val->atom_t->cod=code;
	val->atom_t->is_term=t;
	return val;
}

/*  Ce test fonctionne, donc les valeurs qu'on passe à GenAtom dans GenForest ne sont pas du type attendu
std::string *test;
int *ttest;
bool *tttest;
node *Test = GenAtom(test, ttest, tttest);
*/
void GenForet(){
	int S = 0;
	int N = 1;
	int E = 2;
	int T = 3;
	int F = 4;

	node A[S] = GenConc(GenFang(GenConc(GenConc(GenConc(GenAtom("N",0,false),GenAtom("->",0,true)),GenAtom("E",0,false)),GenAtom(",",1,true),GenAtom(";",0,true))));
}
