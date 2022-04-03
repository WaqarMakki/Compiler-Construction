/*
	Name: Muhammad Waqar Makki
	Reg:  L1F18BSCS0028
	CC-Section-G2
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void readTable(int TT[45][21]){

	ifstream fin("table.txt");
	if (!fin){
		cout << "File not found..." << endl;
	}else{
		for (int i = 0; i < 45; i++)
			for (int j = 0; j < 21; j++)
				fin >> TT[i][j];
		fin.close();
	} 
}

void readStates(int *states){

	ifstream fin("states.txt");
	if (!fin){
		cout << "File not found..." << endl;
	}
	else{
		for (int i = 0; i < 45; i++)
			fin >> states[i];
		fin.close();
	}
}

void initlize_M(int *m){

	for (int i = 0; i < 131; i++){
		if ((i > 64 && i < 91) || (i > 96 && i < 123))
			m[i] = 1;
		else if (i > 47 && i < 58)
			m[i] = 2;
		else if (i == 33)
			m[i] = 3;
		else if (i == 61)
			m[i] = 4;
		else if (i == 42)
			m[i] = 5;
		else if (i == 43)
			m[i] = 6;
		else if (i == 47)
			m[i] = 7;
		else if (i == 45)
			m[i] = 8;
		else if (i == 62)
			m[i] = 9;
		else if (i == 60)
			m[i] = 10;
		else if (i == 38)
			m[i] = 11;
		else if (i == 124)
			m[i] = 12;
		else if (i == 37)
			m[i] = 13;
		else if (i == 58)
			m[i] = 14;
		else if (i == 91)
			m[i] = 15;
		else if (i == 123)
			m[i] = 16;
		else if (i == 125)
			m[i] = 17;
		else if (i == 93)
			m[i] = 18;
		else if (i == 95)
			m[i] = 19;
		else if (i == 46)
			m[i] = 20;
		else if (i == 130)
			m[i] = 21;
		else
			m[i] = -1;
	}
}

void createToken(int num, char *arr){

	ofstream fout("Output.txt", fstream::app);

	switch (num){
	case 1:
		fout << "< " << arr << ", id >\n";
		break;
	case 2:
		fout << "< " << arr << ", number >\n";
		break;
	case 3:
		fout << "< " << arr << ", != >\n";
		break;
	case 4:
		fout << "< " << arr << ", <> >\n";
		break;
	case 5:
		fout << "< " << arr << ", =:= >\n";
		break;
	case 6:
		fout << "< " << arr << ", == >\n";
		break;
	case 7:
		fout << "< " << arr << ", * >\n";
		break;
	case 8:
		fout << "< " << arr << ", + >\n";
		break;
	case 9:
		fout << "< " << arr << ", / >\n";
		break;
	case 10:
		fout << "< " << arr << ", - >\n";
		break;
	case 11:
		fout << "< " << arr << ", >> >\n";
		break;
	case 12:
		fout << "< " << arr << ", << >\n";
		break;
	case 13:
		fout << "< " << arr << ", ++ >\n";
		break;
	case 14:
		fout << "< " << arr << ", =+ >\n";
		break;
	case 15:
		fout << "< " << arr << ", %% >\n";
		break;
	case 16:
		fout << "< " << arr << ", || >\n";
		break;
	case 17:
		fout << "< " << arr << ", => >\n";
		break;
	case 18:
		fout << "< " << arr << ", =< >\n";
		break;
	case 19:
		fout << "< " << arr << ", % >\n";
		break;
	case 20:
		fout << "< " << arr << ", : >\n";
		break;
	case 21:
		fout << "< " << arr << ", :: >\n";
		break;
	case 22:
		fout << "< " << arr << ", -- >\n";
		break;
	case 23:
		fout << "< " << arr << ", [ >\n";
		break;
	case 24:
		fout << "< " << arr << ", { >\n";
		break;
	case 25:
		fout << "< " << arr << ", < >\n";
		break;
	case 26:
		fout << "< " << arr << ", >  >\n";
		break;
	case 27:
		fout << "< " << arr << ", } >\n";
		break;
	case 28:
		fout << "< " << arr << ", ] >\n";
		break;
	case 29:
		fout << "<" << arr << ", keyword >\n";
	}
	fout.close();
}

void readKeywords(string *&k){

	ifstream fin("keywords.txt");
	if (!fin){
		cout << "File not found..." << endl;
	}
	else{
		int i = 0;
		while (!fin.eof())
			getline(fin, k[i++]);
	}
	fin.close();
}

bool checkKeywords(string *keywords, char *out){
	
	string str;
	for (int i = 0; i < 60; i++){
		str = keywords[i];
		if (str == out)
			return true;
	}
	return false;
}

int main(){

	ifstream fin("input.txt");
	if (!fin)
		cout << "Unable to open the file...\n\n";
	else{

		string *keywords = new string[60];
		readKeywords(keywords);

		int j = 0;
		char arr[100];
		while (!fin.eof())
			fin >> arr[j++];

		int TT[45][21];
		readTable(TT);

		int states[45];
		readStates(states);

		int m[131];
		initlize_M(m);

		int cs = 0, p = 0, c = 0, p2 = 0;
		arr[j - 1] = '\0';
		char out[20] = { '\0' };
		while (p < j - 1){
			if (!states[cs]){
				int x = m[arr[p]]-1;
				cs = TT[cs][x];
				out[p2++] = arr[p];
				if (checkKeywords(keywords, out)){
					createToken(29, out);
					cs = 0;
					for (int i = 0; i < p2 - 1; i++)
						out[i] = '\0';
					p2 = 0;
					p--;
					continue;
				}
			}
			else{
				if (states[cs] < 0){
					int t = states[cs];
					t = t * -1;
					out[p2 - 1] = '\0';
					createToken(t, out);
					cs = 0;
					for (int i = 0; i < p2 - 1; i++)
						out[i] = '\0';
					p2 = 0;
					p--;
					continue;
				}
				else{
					createToken(states[cs], out);
					cs = 0;
					for (int i = 0; i < p2; i++)
						out[i] = '\0';
					p2 = 0;
					continue;
				}
			}
			p++;
		}
		cout << "Possible Lexemes are stored in 'Output.txt'\n\n" << endl;
		fin.close();
	}
	return 0;
}