#include<iostream>
#include"data_struct.hpp"

using namespace std;

int main(void){

	//int prof=0;
	//GenForet(prof);
	//cout << "Entire forest generated." << endl;

	string phrase = "A='B'+C";
	string::size_type it_phrase=0;
	string code;
	int action;
	char caract;

	for(std::string::size_type i = it_phrase; i < phrase.size(); i++){  // On itère dans les caractères de la phrase à tester
		scan(phrase, it_phrase, code, action, caract); // On scanne le caractère i de la phrase et la fonction passe automatiquement au suivant pour l'appel suivant
		cout << it_phrase << " " << code << " " << action << " " << caract << endl;
		
	}


	// test de scan
	/*
	scan(phrase, it_phrase, code, action, caract);
	cout << it_phrase << " " << code << " " << action << " " << caract << endl;
	scan(phrase, it_phrase, code, action, caract);
	cout << it_phrase << " " << code << " " << action << " " << caract << endl;
	scan(phrase, it_phrase, code, action, caract);
	cout << it_phrase << " " << code << " " << action << " " << caract << endl;
	scan(phrase, it_phrase, code, action, caract);
	cout << it_phrase << " " << code << " " << action << " " << caract << endl;
	scan(phrase, it_phrase, code, action, caract);
	cout << it_phrase << " " << code << " " << action << " " << caract << endl;
	*/


	return EXIT_SUCCESS;
}
