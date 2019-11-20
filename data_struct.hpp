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
	Node *child;
}ou;

typedef struct atom {
	bool is_term;
	int cod;  // 0 ou 1
	const char *action;
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
plus *ptest;
conc *ctest;
fang *ftest;
atom *atest;
ou *otest;

node *GenConc(node *r, node *l) {
	node *val = new node;
	conc *c= new conc;
	c->left=l;
	c->right=r;
	val->conc_t=c;
	val->clas="conc";
	val->plus_t=ptest;
	val->fang_t=ftest;
	val->atom_t=atest;
	val->ou_t=otest;
	return val;
	delete c;
}

node *GenFang(node *c){
	node *val = new node;
	fang *f = new fang;
	f->child=c;
	val->clas="fang";
	val->fang_t=f;
	val->conc_t=ctest;
	val->plus_t=ptest;
	val->atom_t=atest;
	val->ou_t=otest;
	return val;
	delete f;
}

node *GenPlus(node *r, node *l) {
	node *val = new node;
	plus *p = new plus;
	p->left=l;
	p->right=r;
	val->plus_t=p;
	val->clas="plus";
	val->fang_t=ftest;
	val->conc_t=ctest;
	val->atom_t=atest;
	val->ou_t=otest;
	return val;
	delete p;
}

node *GenOu(node *c){
	node *val = new node;
	ou *o = new ou;
	val->clas="ou";
	o->child=c;
	val->ou_t=o;
	val->plus_t=ptest;
	val->fang_t=ftest;
	val->conc_t=ctest;
	val->atom_t=atest;
	return val;
	delete o;
}

node *GenAtom(const char *a, int code, bool t){
	node *val = new node;
	atom *at = new atom;
	val->clas="atom";
	at->action=a;
	at->cod=code;
	at->is_term=t;
	val->atom_t=at;
	val->plus_t=ptest;
	val->fang_t=ftest;
	val->conc_t=ctest;
	val->ou_t=otest;
	return val;
	delete at;
}

void GenForet()
{
	node *A[5];

	int S = 0;
	int N = 1;
	int E = 2;
	int T = 3;
	int F = 4;
	
	node *test = GenConc(
				GenFang(
					GenConc(
						GenConc(
							GenConc(
								GenAtom("N",0,false),
							GenAtom("->",0,true)),
						GenAtom("E",0,false)),
					GenAtom(",",1,true))),
			GenAtom(";",0,true));

	
	std::cout << "Before assign" << std::endl;
	A[S] = { test } ;
	std::cout << "Assign passed" << std::endl;
}
