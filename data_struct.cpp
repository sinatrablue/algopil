#include<iostream>
#include"data_struct.hpp"

using namespace std;

int main(void){

	/*  ---------------------------------------------------------
	PHASE D'INITIATION ET DÉCLARATIONS */
	// Déclarations bougées dans le main depuis GenForet parce qu'on veut se servir de ces noeuds et les passer à Analyse() ensuite
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

	A[S] = AS ;
	std::cout << "S generated" << std::endl;
	A[N] = AN ;
	std::cout << "N generated" << std::endl;
	A[E] = AE ;
	std::cout << "E generated" << std::endl;
	A[T] = AT ;
	std::cout << "T generated" << std::endl;
	A[F] = AF ;
	std::cout << "F generated" << std::endl;

	int prof=0;
	GenForet(prof, S, N, E, T, F, A);
	cout << "Entire forest generated." << endl;
	/* ------------------------------------------------------------- */

	string phrase = "S0->['a'].'b'";
	string::size_type it_phrase=0;
	int code;
	string action;

	scan(phrase, it_phrase, code, action); // On scanne le premier caractère de la phrase pour commencer
	// Analyse de la phrase
	int i=0;
	bool res=false;
	while(i<6 && res==false){  // Tant qu'on a pas testé sur tous les arbres ou que tous les atomes n'ont pas été vérifiés comme OK
		res = Analyse(A[i], i);
		i++;
	}

	// Affichage final
	if(res){
		cout << "OK, la phrase appartient bien à la grammaire" << endl;
	} else {
		cout << "NOT OK, la phrase est étrangère à la grammaire" << endl;
	}

	return EXIT_SUCCESS;
}
