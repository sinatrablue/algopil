#include<iostream>
#include"data_struct.hpp"

using namespace std;

int main(void) {

	//int prof=0;
	//GenForet(prof);
	//cout << "Entire forest generated." << endl;

	string phrase = "A='B'+C";
	string::size_type it_phrase=0;
	string code;
	int action;
	char caract;
	scan(phrase, it_phrase, code, action, caract);
	cout << it_phrase << " " << code << " " << action << " " << caract << endl;

	return EXIT_SUCCESS;
}
