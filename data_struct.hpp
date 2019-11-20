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

node *GenConc(node *r, node *l) {
	node *val = new node;
	conc *c= new conc;
	c->left=l;
	c->right=r;
	val->conc_t=c;
	val->clas="conc";
	return val;
	delete c;
}

node *GenFang(node *c){
	node *val = new node;
	fang *f = new fang;
	f->child=c;
	val->clas="fang";
	val->fang_t=f;
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
	return val;
	delete p;
}

node *GenOu(node *c){
	node *val = new node;
	ou *o = new ou;
	val->clas="ou";
	o->child=c;
	val->ou_t=o;
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
	
	node *AS = GenConc(	GenFang( GenConc( GenConc( GenConc( GenAtom("N",0,false),GenAtom("->",0,true)),	GenAtom("E",0,false)),GenAtom(",",1,true))),GenAtom(";",0,true));
	node *AN = GenAtom("IDNTER", 0, false);
	node *AE = GenConc(	GenFang( GenConc( GenAtom("T", 0, false), GenAtom("+", 0, false))), GenAtom("+", 0, false))	;
	node *AT = GenConc(	GenFang( GenConc( GenAtom("F", 0, false), GenAtom(".", 0, false))), GenAtom("F", 0, false))	;
	node *AF = GenConc(GenConc(GenPlus(GenConc(GenConc(GenPlus(GenConc(GenConc(GenPlus(GenPlus(GenAtom("IDNTER",0,false) , GenAtom("ELTER",0,true)) , GenAtom("(",0,false)) , GenAtom("E",0,false)) , GenAtom(")",0,false)) , GenAtom("[",0,false)) , GenAtom("E",0,false)) , GenAtom("]",0,false)) , GenAtom("(/",0,false)) , GenAtom("E", 0, false)) , GenAtom("/)",0,false)) ;

	A[S] = { AS } ;
	std::cout << "S generated" << std::endl;
	A[N] = { AN } ;
	std::cout << "N generated" << std::endl;
	A[E] = { AE } ;
	std::cout << "E generated" << std::endl;
	A[T] = { AT } ;
	std::cout << "T generated" << std::endl;
	A[F] = { AF } ;
	std::cout << "F generated" << std::endl;


}
