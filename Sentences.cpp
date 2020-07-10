#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include "Set.h"

bool readSent(const char* filename, vector <Set <unsigned char>>& sentences);
bool readSent(const char* filename, vector<vector<string>>& sent_numb);

bool readSyl(const char* filename, vector <Set <string>>& sentences);

int main()
{
	setlocale(LC_ALL, "Russian");
	/*vector <Set<unsigned char>> sentences;
	vector <vector<string>> sent_numb;
	readSent("Text.txt", sentences); //формируем набор множеств
	readSent("Text.txt", sent_numb); //формируем набор предложений
	ofstream out("Results.txt");
	int i = 0;
	for (vector<Set<unsigned char>>::iterator it = sentences.begin(); it != sentences.end(); it++) {
		int j = i;
		for (vector<Set<unsigned char>>::iterator it2 = it; it2 != sentences.end(); it2++) { //сравниваем каждое множество с остальными, идущими после него
			if ((*it) == (*it2) && it != it2) {									//если множества равны, выводим множества и предложения
				out << "Одинаковые множества " << endl << "Множество 1: " << *it << endl << "Множество 2: " << *it2 << endl << "Предложение 1: ";
				for (vector<string>::iterator it3 = sent_numb.at(i).begin(); it3 != sent_numb.at(i).end(); it3++)
					out << *it3;
				out << endl << "Предложение 2: ";
				for (vector<string>::iterator it3 = sent_numb.at(j).begin(); it3 != sent_numb.at(j).end(); it3++)
					out << *it3;
				out << endl << endl;
			}
			if ((*it) - (*it2) == (*it)) {		//если множества не содержат одинаковых символов, выводим множества и предложения
				out << "Разные множества " << endl << "Множество 1: " << *it << endl << "Множество 2: " << *it2 << endl << "Предложение 1: ";
				for (vector<string>::iterator it3 = sent_numb.at(i).begin(); it3 != sent_numb.at(i).end(); it3++)
					out << *it3;
				out << endl << "Предложение 2: ";
				for (vector<string>::iterator it3 = sent_numb.at(j).begin(); it3 != sent_numb.at(j).end(); it3++)
					out << *it3;
				out << endl << endl;
			}
			j++;
		}
		i++;

	}*/
	vector <Set <string>> syllables;
	readSyl("Text2.txt", syllables);
	bool a;
	for (vector<Set<string>>::iterator it = syllables.begin(); it != syllables.end(); it++) {
		for (vector<Set<string>>::iterator it2 = it; it2 != syllables.end(); it2++) {
			if (it != it2) {
				a = *it == *it2;
				cout << *it << " == " << *it2 << " = " << a<<endl;
			}
		}
	}

	return 0;
}

bool readSent(const char* filename, vector <Set <unsigned char>>& sentences) {
	ifstream in(filename);
	if (!in.is_open())
	{
		cout << "Can't open the file.";
		return false;
	}
	while (!in.eof()) {
		set <unsigned char> sent;
		unsigned char c = ' ';
		unsigned char cc;
		while (c != '.' && c != '!' && c != '?') {
			in >> cc;
			if (int(cc) >= 192 && int(cc) <= 255) { //если считанный символ - символ русского алфавита
				if (int(cc) < 224)
					cc += unsigned char(32); // приводим все заглавные символы к строчным 
				sent.insert(cc);			//заполняем множество символов
			}
			c = cc;
		}
		if (!sent.empty())					//заполняем множество из множеств символов
			sentences.push_back(sent);
	}
	in.close();
	return true;
}

bool readSent(const char* filename, vector<vector<string>>& sent_numb) {
	ifstream in(filename);
	string s;
	if (!in.is_open())
	{
		cout << "Can't open the file.";
		return false;
	}
	while (!in.eof()) {
		vector <string> sent;
		do {
			in >> s;				//считываем строку
			sent.push_back(s);		//вставляем строку в множество строк
			sent.push_back(" ");   //добавляем пробел между словами
		} while (s.find('.') > 100 && s.find('?') > 100 && s.find('!') > 100);		//пока не встретим . ! или ?
		sent_numb.push_back(sent);		//записываем предложение в вектор предложений
	}
	in.close();
	return true;
}

bool readSyl(const char* filename, vector <Set <string>>& syllables) {
	ifstream in(filename);
	string s;
	if (!in.is_open())
	{
		cout << "Can't open the file.";
		return false;
	}
	while (!in.eof()) {
		Set <string> syl;
		bool end = false;
		do {
			in >> s;	
			if (s.find('.') < 100) {
				s.pop_back();
				end = true;
			}
			syl.addToSet(s);	
		} while (end==0);		//пока не встретим . ! или ?
		syllables.push_back(syl);		//записываем слоги в вектор слогов
	}
	in.close();
	return true;
}
