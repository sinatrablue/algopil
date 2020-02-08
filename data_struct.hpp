#include<iostream>
#include<string>

typedef struct node Node;

typedef struct union_p {
	Node *left;
	Node *right;
}union_p;

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
}atom;

struct node {
	int clas;
	union_p *plus_t;
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
};

node *GenFang(node *c){
	node *val = new node;
	fang *f = new fang;
	f->child=c;
	val->clas=4;
	val->fang_t=f;
	return val;
	delete f;
};

node *GenPlus(node *r, node *l) {
	node *val = new node;
	union_p *p = new union_p;
	p->left=l;
	p->right=r;
	val->plus_t=p;
	val->clas=2;
	return val;
	delete p;
};

node *GenOu(node *c){
	node *val = new node;
	ou *o = new ou;
	val->clas=3;
	o->child=c;
	val->ou_t=o;
	return val;
	delete o;
};

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
};

int printArbre(node *ptr, int prof){
	prof+=1;
	int k;

    for(k=prof-1;  k<=prof; k++){
		std::string write="";
		for(int i=1; i<=prof; i++){
			write += "......";
		}
        std::cout << write ;
		std::cout << prof;
        switch(ptr->clas){
            case 1 :
            std::cout << "> Conc" << std::endl;
            printArbre(ptr->conc_t->left, prof);
            printArbre(ptr->conc_t->right, prof);
			prof-=1;
			break;
            case 2 :
            std::cout << "> Plus" << std::endl;
            printArbre(ptr->plus_t->left, prof);
            printArbre(ptr->plus_t->right, prof);
			prof-=1;
			break;
            case 3 :
            std::cout << "> Ou" << std::endl;
            printArbre(ptr->ou_t->child, prof);
			prof-=1;
			break;
            case 4 :
            std::cout << "> Star" << std::endl;
            printArbre(ptr->fang_t->child, prof);
			prof-=1;
			break;
            case 5 :
            std::cout << "> Atom             ";
            if(ptr->atom_t->is_term){
                std::cout << "Code = " << ptr->atom_t->cod << " Action = " << ptr->atom_t->action << " est Terminal" << std::endl;
				prof-=1;
            } else {
                std::cout << "Code = " << ptr->atom_t->cod << " Action = " << ptr->atom_t->action << " est Non-Terminal" << std::endl;
				prof-=1;
            }
            break;
			default:
			std::cout << "Problème de type inconnu" << std::endl;
			break;
        }
        prof-=1;
    }
	return prof;
};

int GenForet(int prof, int S, int N, int E, int T, int F, node* A[])
{
	printArbre(A[S], prof);
	std::cout << "============================================================================================================================================" << std::endl;
	printArbre(A[N], prof);
	std::cout << "============================================================================================================================================" << std::endl;
	printArbre(A[E], prof);
	std::cout << "============================================================================================================================================" << std::endl;
	printArbre(A[T], prof);
	std::cout << "============================================================================================================================================" << std::endl;
	printArbre(A[F], prof);
	std::cout << "============================================================================================================================================" << std::endl;

	return prof;
};

 /*  Antisèche : READ CHARACTERS IN A STRING ONE BY ONE
std::string str = ???;
for(char& c : str) {
    do_things_with(c);
}

std::string str = ???;
for(std::string::iterator it = str.begin(); it != str.end(); ++it) {
    do_things_with(*it);
}

std::string str = ???;
for(std::string::size_type i = 0; i < str.size(); ++i) {
    do_things_with(str[i]);
}
*/

// Procédure scan
// fonctionne mais doit être appelée un nombre de fois équivalent à la taille de la phrase, si on l'appelle plus elle va faire plein de fois le dernier atome. 
void scan(std::string phrase, std::string::size_type &it_phrase, int &code, std::string &action){  // Doit reconnaitre les éléments terminaux car ils sont entre quotes
	if(isalpha(phrase[it_phrase]) && phrase[it_phrase-1]=='\'' && phrase[it_phrase+1]=='\''){  // Si le caractère trouvé est une lettre et entourée de quotes
		action = phrase[it_phrase]; // c'est terminal
		code = 1;
		it_phrase +=1;
	}
	else if(phrase[it_phrase]!='\''){   // Sinon si c'est un vrai caractère et pas un quote, et qu'il n'a donc pas de quote
		action = phrase[it_phrase]; // pas terminal
		code = 0;
		it_phrase +=1;
	} else {
		it_phrase +=1;	// Sinon, c'est qu'on est en train de lire un quote, donc on passe direct au suivant parce que ce n'est pas intéressant à lire
		scan(phrase, it_phrase, code, action);
	}
};


bool Analyse(node *ptr, int &i){
	bool res_analys;
	switch(ptr->clas){
		case 1: 
		if (Analyse(ptr->conc_t->left, i)){
			Analyse(ptr->conc_t->right, i);
		} else {
			return false;
		}
		break;

		case 2:
		if (Analyse(ptr->plus_t->left, i)){
			return true;
		} else {
			Analyse(ptr->plus_t->left, i);
		}
		break;

		case 3:
		while (Analyse(ptr->fang_t->child, i)){
			return true;
		}
		break;

		case 4:
		while (Analyse(ptr->fang_t->child, i)){
			return true;
		}
		break;

		case 5:
		if(ptr->atom_t->is_term){
			if(ptr->atom_t->cod) {
				return true;
				i=0;
			  	//scan();
			} else {
				return false;
			}
		} else {
			if(ptr->atom_t->cod) {
				return true;
				i=0;
			} else {
				return false;
			}
			
		}
		break;
	}
};