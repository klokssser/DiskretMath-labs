#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>


std::string getText() {
	std::ifstream in("task1.txt");
	if (!in)
		std::cerr << "Ошибка открытия файла task1.txt";
	else
		return std::string{ std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>() };
}

struct numSymbol {
	char symbol = '-';
	int count = 0;
};

inline bool cmp(numSymbol left, numSymbol right) {
	return left.count > right.count;
}

struct resultCmp {
	bool operator()(const std::string& a, const std::string& b) const {
		return a.size() < b.size() || (a.size() == b.size() && a < b);
	}
};


std::string plusOne(std::string num, int cc) {
	bool carry{};

	num[num.size() - 1] += 1;
	carry = num[num.size() - 1] - '0' >= cc;

	for (int i = num.size() - 1; carry; --i) {
		num[i] -= cc;

		if (i == 0) {
			num.push_back('0');
			break;
		}

		num[i - 1] += carry;
		carry = num[i - 1] - '0' >= cc;
	}

	return num;
}

void task1() {
	std::vector<numSymbol> alphabet(33);
	for (int i = 0; i < 32; ++i)
		alphabet[i].symbol = 'а' + i;
	alphabet[32].symbol = ' ';

	std::string text = getText();
	for (int i = 0; i < text.size(); ++i) {
		if (text[i] == ' ' || text[i] == '\n')
			++alphabet[32].count;
		else
			++alphabet[text[i] - 'А'].count;
	}

	std::sort(alphabet.begin(), alphabet.end(), cmp);

	for (int i = 32; i >= 0 && alphabet[i].count == 0; --i)
		alphabet.pop_back();



	std::cout << "Введите размер кодового алфавита: ";
	int codeN;
	std::cin >> codeN;

	std::cout << "Введите кодовый алфавит(для закодирования): ";
	std::vector<char> codingAlphabet(codeN);
	int value{};
	for (int i = 0; i < codeN; ++i) {
		std::cin >> value;
		codingAlphabet[i] = value + '0';
	}



	int n = alphabet.size();
	std::vector<numSymbol> tree(alphabet);
	for (int i = n - 1; i >= codeN - 1; i == n - 1 ? i -= (((n - codeN) % (codeN - 1) == 0) ? codeN - 1 : ((n - codeN) % (codeN - 1))) : i -= codeN - 1) {
		numSymbol sumSymb;

		for (int ii = i; ii > (i == n - 1 ? i - (((n - codeN) % (codeN - 1) == 0) ? codeN : ((n - codeN) % (codeN - 1)) + 1) : i - codeN); --ii)
			sumSymb.count += tree[ii].count;


		tree.push_back(sumSymb);
		for (int j = tree.size() - 1; j > 0 && tree[j].count > tree[j - 1].count; --j)
			std::swap(tree[j], tree[j - 1]);
	}



	std::map<std::string, numSymbol, resultCmp> result;
	int treeN = tree.size();
	std::string code{ "0" };
	for (int i = 1; i < treeN; ++i) {
		if (result.empty()) {
			for (int ii = 1; i < treeN && ii < codeN; ++ii) {
				if (tree[i].symbol != '-')
					result[code] = tree[i];
				code[code.size() - 1] = codingAlphabet[ii];
				++i;
			}
			if (i < treeN && tree[i].symbol != '-')
				result[code] = tree[i];
			code = plusOne(code, codeN);
		}
		else {
			bool correct;
			do {
				correct = true;
				for (auto p = result.rbegin(); p != result.rend(); ++p) {
					if (p->first.size() != code.size()) {
						std::string subStr = code.substr(0, p->first.size());
						if (p->first == subStr) {
							code = plusOne(subStr, codeN) + std::string(code.size() - subStr.size(), '0');
							correct = false;
						}
					}
				}
			} while (!correct);

			for (int ii = 1; i < treeN && ii < codeN; ++ii) {
				if (tree[i].symbol != '-')
					result[code] = tree[i];
				code[code.size() - 1] = codingAlphabet[ii];
				++i;
			}

			if (i < treeN && tree[i].symbol != '-')
				result[code] = tree[i];
			code = plusOne(code, codeN);
		}
	}

	double averageRedundancy{};

	std::cout << "\nЗакодированная таблица префиксным способом:" << std::endl;
	for (auto i = result.begin(); i != result.end(); ++i) {
		std::cout << "Символ: " << i->second.symbol << " количество в тексте\t" << std::setw(4)
			<< i->second.count << ", его код = " << std::setw(12) << i->first << std::endl;

		averageRedundancy += i->second.count * i->first.size() / (double)tree[0].count;
	}

	std::cout << "\nСредняя избыточность кода = " << std::setprecision(4) << averageRedundancy << std::endl;
}