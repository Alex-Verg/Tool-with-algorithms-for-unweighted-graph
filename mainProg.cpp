#include "Graph.h"
#include "UserInterface.h"
#include <Windows.h>
#include <vector>
#include <utility>
#include <iostream>


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	UserInterface UI;

	UI.mainMenu();

	return 0;
}