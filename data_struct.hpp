#include<iostream>
#include<string>

struct atom_type {
	std::string terminal;
	std::string nonter;
};
// useless comment to test git config
struct node {
	std::string clas;
	plus *plus_t;
	conc *conc_t;
	fang *fang_t;
	atom *atom_t;
	ou *ou_t;
};

typedef struct plus {
	node *left;
	node *right;
};

typedef struct conc {
	node *left;
	node *right;
};

typedef struct fang {
	node *child;
};

typedef struct ou {
	node *left;
	node *right;
};

typedef struct atom {
	atom_type *type;
	int *cod;  // 0 ou 1
	char *action;
	node *child;
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

node *GenAtom(std::string *a, int *code, atom_type *t){
	node *val = new node;
	val->clas="atom";
	val->atom_t->action=a;
	val->atom_t->cod=code;
	val->atom_t->type=t;
	return val;
}

void GenForet(){
	int S = 0;
	int N = 1;
	int E = 2;
	int T = 3;
	int F = 4;

	A[S] = GenConc(GenFang(GenConc(GenConc(GenConc(GenAtom("N",0,"nonter"),GenAtom("->",0,"terminal")),GenAtom("E",0,"nonter")),GenAtom(",",1,"terminal"),GenAtom(";",0,"terminal"))));
