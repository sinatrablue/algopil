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

node *GenConc(node *l, node *r) {
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

node *GenPlus(node *l, node *r) {
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

// Fonction pour vérifier que ça contient au moins une lettre, étant donné que la méthode std::any_of puis std::isalpha ne fonctionne pas
bool atLeastOneLetter(std::string word){
	bool hasLetter=false;
	for (int i = 0; i < word.size(); i++) {
        if (isalpha(word.at(i))) { hasLetter = true; }
    }
	return hasLetter;
};


// Procédure scan
void scan(std::string phrase, std::string::size_type &it_phrase, std::string::size_type &it_bis, int &code, std::string &action){  // Doit reconnaitre les éléments terminaux car ils sont entre quotes
	if(phrase[it_phrase] == '|'){
		it_bis = it_phrase+1;
		do{it_phrase += 1;}while(phrase[it_phrase] != '|');
		if(phrase[it_bis]=='\'' && phrase[it_phrase-1]=='\'' && atLeastOneLetter(phrase.substr(it_bis+1,(it_phrase-3)-it_bis+1))){
			action = "ELTER";
			code = 1;
		}
		else if(phrase[it_bis]!='\'' && atLeastOneLetter(phrase.substr(it_bis,(it_phrase-it_bis)))){
			action = "IDNTER";
			code = 0;
		}
		else {   // Sinon si c'est un vrai caractère et pas de quotes
			action = phrase.substr(it_bis,(it_phrase-it_bis));
			code = 0;
		}
	} else { std::cout << "Problème : on ne trouve pas de pipe" << std::endl; }
};

bool Analyse(node *ptr, std::string phrase, std::string::size_type &it_phrase, std::string::size_type &it_bis, int &code, std::string &action, node *A[5]){
	bool res_analys;
	switch(ptr->clas){
		case 1: 
		std::cout << "Conc" << std::endl;
		if (Analyse(ptr->conc_t->left, phrase, it_phrase, it_bis, code, action, A)){
			Analyse(ptr->conc_t->right, phrase, it_phrase, it_bis, code, action, A);
		} else {
			res_analys = false;
		}
		break;

		case 2:
		std::cout << "Plus" << std::endl;
		if (Analyse(ptr->plus_t->left, phrase, it_phrase, it_bis, code, action, A)){
			res_analys = true;
		} else {
			Analyse(ptr->plus_t->right, phrase, it_phrase, it_bis, code, action, A);
		}
		break;

		case 3:
		std::cout << "Ou" << std::endl;
		while(Analyse(ptr->ou_t->child, phrase, it_phrase, it_bis, code, action, A)){
			res_analys = true;
		}

		break;

		case 4:
		std::cout << "Fang" << std::endl;
		while (Analyse(ptr->fang_t->child, phrase, it_phrase,it_bis, code, action, A)){
			res_analys = true;
			
		}
		break;

		case 5:
		std::cout << "On rentre bien dans Atome" << std::endl;
		std::cout << "Atome dans l'arbre : " << ptr->atom_t->action << "  Dans la phrase : " << action << std::endl;
		if(ptr->atom_t->is_term){
			std::cout << "is_term true" << std::endl;
			if(ptr->atom_t->action == action) { //comparer le caractère trouvé dans l'arbre et celui de scan
				res_analys = true;
			  	scan(phrase, it_phrase, it_bis, code, action);
			} else {
				std::cout << "XXXX" << std::endl;
				res_analys = false;
			}
		} else {
			std::cout << "is_term false" << std::endl;
			if(ptr->atom_t->action == "N") {
			std::cout << "Noeud N, on passe à l'arbre N" << std::endl;
			//scan(phrase, it_phrase, it_bis, code, action);
			res_analys = Analyse(A[1], phrase, it_phrase, it_bis, code, action, A);
			} else if(ptr->atom_t->action == "E"){
			std::cout << "Noeud E, on passe à l'arbre E" << std::endl;
			//scan(phrase, it_phrase, it_bis, code, action);
			res_analys = Analyse(A[2], phrase, it_phrase, it_bis, code, action, A);
			} else if(ptr->atom_t->action == "T"){
			std::cout << "Noeud T, on passe à l'arbre T" << std::endl;
			//scan(phrase, it_phrase, it_bis, code, action);
			res_analys = Analyse(A[3], phrase, it_phrase, it_bis, code, action, A);
			} else if(ptr->atom_t->action == "F"){
			std::cout << "Noeud F, on passe à l'arbre F" << std::endl;
			//scan(phrase, it_phrase, it_bis, code, action);
			res_analys = Analyse(A[4], phrase, it_phrase, it_bis, code, action, A);
			}
			std::cout << "Pas un atome connu" << std::endl;

			if(ptr->atom_t->action == action){
				std::cout << "action==action" << std::endl;
				res_analys = true;
			} else {
				std::cout << "action pas égal action" << std::endl;
				res_analys = false;
			}
		}
		break;
	}
	std::cout << "Fin de fonction" << std::endl;
	return res_analys;
};