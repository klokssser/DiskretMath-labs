#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "tasks.h"

void checkInput(std::string input, std::string errorMessage = "Error, please repeat input: ",
	std::vector<std::string> permissibleStrs = std::vector<std::string>{ "yes", "no" }) {

	bool notCorrect{};
	do {
		notCorrect = true;
		for (int i = 0; i < permissibleStrs.size(); ++i)
			if (input == permissibleStrs[i]) {
				notCorrect = false;
				break;
			}
		if (notCorrect) {
			std::cout << errorMessage;
			std::cin >> input;
		}
	} while (notCorrect);
	std::cout << '\n';
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	
	std::string launchMain{};
	do {
		std::cout << "Введите программу для запуска(1-2): ";
		int numberProgram;
		std::cin >> numberProgram;
		std::string generateTask5{};

		switch (numberProgram) {
		case 1:
			task1();
			break;
		case 2:
			task2();
			break;
		default:
			std::cerr << "Ошибка main.cpp. Несуществующий номер программы.";
			return -1;
		}

		std::cout << "\nХотите повторить запуск программы(yes / no): ";
		std::cin >> launchMain;
		checkInput(launchMain, "Некорректный ввод, повторите ввод: ");
	} while (launchMain == "yes");
	
	return 0;
}
