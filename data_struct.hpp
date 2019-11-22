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
	int clas;
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
	val->clas=1;
	return val;
	delete c;
}

node *GenFang(node *c){
	node *val = new node;
	fang *f = new fang;
	f->child=c;
	val->clas=4;
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
	val->clas=2;
	return val;
	delete p;
}

node *GenOu(node *c){
	node *val = new node;
	ou *o = new ou;
	val->clas=3;
	o->child=c;
	val->ou_t=o;
	return val;
	delete o;
}

node *GenAtom(const char *a, int code, bool t){
	node *val = new node;
	atom *at = new atom;
	val->clas=5;
	at->action=a;
	at->cod=code;
	at->is_term=t;
	val->atom_t=at;
	return val;
	delete at;
}

void printArbre(node *ptr){
    int prof=0;
    prof+=1;
	std::string write;

    for(int k=1;k<=prof;k++){
		write += "...";
        std::cout << write ;

        switch(ptr->clas){
            case 1 :
            std::cout << "> Conc" << std::endl;
            printArbre(ptr->conc_t->left);
            printArbre(ptr->conc_t->right);
			break;
            case 2 :
            std::cout << "> Plus" << std::endl;
            printArbre(ptr->plus_t->left);
            printArbre(ptr->plus_t->right);
			break;
            case 3 :
            std::cout << "> Ou" << std::endl;
            printArbre(ptr->ou_t->child);
			break;
            case 4 :
            std::cout << "> Star" << std::endl;
            printArbre(ptr->fang_t->child);
			break;
            case 5 :
            std::cout << "> Atom" << std::endl;
            if(ptr->atom_t->is_term){
                std::cout << "Code = " << ptr->atom_t->cod << " Action = " << ptr->atom_t->action << " est Terminal" << std::endl;
            } else {
                std::cout << "Code = " << ptr->atom_t->cod << " Action = " << ptr->atom_t->action << " est Non-Terminal" << std::endl;
            }
            break;
			default:
			std::cout << "Problème de type inconnu" << std::endl;
			break;
        }
        prof-=1;
    }
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

	printArbre(A[S]);
	std::cout << "=============================================================" << std::endl;
	printArbre(A[N]);
	std::cout << "=============================================================" << std::endl;
	printArbre(A[E]);
	std::cout << "=============================================================" << std::endl;
	printArbre(A[T]);
	std::cout << "=============================================================" << std::endl;
	printArbre(A[F]);
	std::cout << "=============================================================" << std::endl;
}
