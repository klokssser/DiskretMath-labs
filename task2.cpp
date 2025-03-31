#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;

int factorial(int value) {
	if (value <= 1)
		return 1;
	else
		return value * factorial(value - 1);
}

vector<int> getCode(string& text, const int& n) {
	
	vector<vector<int>> codes;

	vector<int> trafaret;
	for (int i = 0; i < n; ++i)
		trafaret.push_back(i);

	string str1(text.begin(), text.begin() + n);
	string str2(text.begin() + n, text.begin() + 2 * n);
	string str3(text.begin() + 2 * n, text.begin() + 3 * n);
	string str4(text.begin() + 3 * n, text.begin() + 4 * n);
	string str5(text.begin() + 4 * n, text.begin() + 5 * n);
	int fN = factorial(n);
	
	int maxCount{2};
	for (int i = 0; i < fN; ++i) {
		string copyStr1(str1), copyStr2(str2), copyStr3(str3), copyStr4(str4), copyStr5(str5);

		for (int i = 0; i < n; ++i) {
			copyStr1[i] = str1[trafaret[i]];
			copyStr2[i] = str2[trafaret[i]];
			copyStr3[i] = str3[trafaret[i]];
			copyStr4[i] = str4[trafaret[i]];
			copyStr5[i] = str5[trafaret[i]];
		}
		std::next_permutation(trafaret.begin(), trafaret.end());


		string res = copyStr1 + copyStr2 + copyStr3 + copyStr4 + copyStr5;
		res[0] = (res[0] >= -64 && res[0] <= -32 ? res[0] + 32 : res[0]);


		std::string russianWord;
		std::stringstream ss(res);
		std::istream_iterator<std::string> begin(ss);
		std::istream_iterator<std::string> end;
		std::vector<std::string> vstrings(begin, end);
		
		std::ifstream in("10000-russian-words.txt");
		int count{};
		for (int j = 0; j < 10000; ++j) {
			in >> russianWord;
			for (int ii = 0; ii < vstrings.size(); ++ii)
				if (vstrings[ii] == russianWord) {
					++count;
					if (count > maxCount) {
						maxCount = count;
						std::prev_permutation(trafaret.begin(), trafaret.end());
						codes.push_back(trafaret);
						std::next_permutation(trafaret.begin(), trafaret.end());
					}
				} 

		}

	}

	return codes[codes.size()-1];
}

void task2() {
	ifstream in("task2.txt");
	if (!in) {
		cerr << "Ошибка открытия файла 2.txt" << std::endl;
		exit(-1);
	}

	string text{ std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>() };
	remove_if(text.begin(), text.end(), [](char ch) {return ch == '\n'; }), text.end();

	const int n = 6; // размер кодового блока

	while (text.size() % n != 0)
		text.push_back(' ');
	
	vector<int> code = getCode(text, n);

	string res{};
	for (int i = 0; i < text.size()-2; i += n) {

		string subStr(text.begin() + i, text.begin() + i + n);
		for (int j = 0; j < n; ++j)
			res += subStr[code[j]];
	
	}

	cout << "Получен раскодированный код: ";
	for (int i = 0; i < n; ++i)
		cout << code[i] << ' ';


	std::cout << "\n\nПолученый текст:\n" << res << "\n\nЕсли получился неосмысленный текст добавьте русских слов в 10000-russian-words.txt"
		"\nили проверьте закодированный текст." << std::endl;

}