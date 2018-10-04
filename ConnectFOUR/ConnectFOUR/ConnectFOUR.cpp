#include "pch.h"
#include <iostream>


//global variable
char a[6][7];
int INPUT;
int ROW;
bool warpModeFlag;
bool removeModeFlag;


void Initial() {
	//coloum number
	for (int i = 0; i < 7; i++) {
		std::cout << i+1 << " ";
	}
	std::cout << std::endl;
	//board
	int i, j;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 7; j++) {
			a[i][j] = '*';
			std::cout << a[i][j]<<" ";
			if (j == 6) {
				std::cout << std::endl;
			}
		}
	}
	
}



bool CheckWin(char mark) {
	int markCount = 0;
	int leftCount = 4;

	for (int i = 0; i < 4 && INPUT - i >= 0; ++i) {
		if (a[ROW][INPUT - i] == mark) {
			//--leftCount;
			if (++markCount == 4) {
				return true;
			}
	
		}
	}
	
	for (int i = 1; i < 4&&INPUT + i < 7; ++i) { 
		if (a[ROW][INPUT + i] == mark) {
			if (++markCount == 4) {
				return true;
			}
		}
	}
	

	markCount = 0;
	for (int i = 0; i < 4 && INPUT - i >0; ++i) {
		if (a[ROW + i][INPUT - i] == mark) {
			//--leftCount;
			if (++markCount == 4) {
				return true;
			}
			
		}
	}

	for (int i = 1; i < 4 && INPUT +i <8&&ROW-i>=0; ++i) {
		if (a[ROW - i][INPUT + i] == mark) {
			if (++markCount == 4) {
				return true;
			}
		}
	}
	
	markCount = 0;
	for (int i = 0; i < 4 && INPUT + i < 8&&ROW+i<=5; ++i) {
		if (a[ROW + i][INPUT + i] == mark) {
			//--leftCount;
			if (++markCount == 4) {
				return true;
			}
		
		}
	}
	
	for (int i = 1; i < 4 && INPUT - i >0 && ROW - i >= 0; ++i) {
		if (a[ROW - i][INPUT - i] == mark) {
			if (++markCount == 4) {
				return true;
			}
		}
	}

	markCount = 0;
	for (int i = 0; i < 4&&ROW+i<=5; ++i) {
		if (a[ROW + i][INPUT] == mark) {
			if (++markCount == 4) {
				return true;
			}
		}
	}
	
	return false;
}



void GetInput() {
	std::cin >> INPUT;
	INPUT--;
	std::cin.clear();
	std::cin.ignore();
}



bool ProcessInput(int n) {
	if (n < 0 || n>6) {
		std::cout << "Please input an integer from 1 to 7!"<<std::endl;
		return false;
	}

	if (a[0][INPUT] != '*') {
		std::cout << "This coloum is full. Please choose another one!" << std::endl;
	}

	for (int i = 5; i >= 0; i--) {
		if (a[i][n] == '*') {
			ROW = i;
			return true;
		}
	}
	return false;
}


void PrintBoard(char mark) {
	a[ROW][INPUT] = mark;

	//coloum number
	for (int i = 0; i < 7; i++) {
		std::cout << i+1 << " ";
	}
	std::cout << std::endl;
	//board
	int i, j;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 7; j++) {
			std::cout << a[i][j] << " ";
			if (j == 6) {
				std::cout << std::endl;
			}
		}
	}
}


void PrintText(int player) {
	bool isWin;

	if (player == 1) {
		isWin = CheckWin('X');
		if (!isWin) {
			std::cout << "now it's P1's turn to choose the number of coloum where you want to put your piece" << std::endl;
		}
		if (isWin) {
			std::cout << "P1 win!" << std::endl;
		}
	}

	if (player == 2) {
		isWin = CheckWin('O');
		if (!isWin) {
			std::cout << "now it's P2's turn to choose the number of coloum where you want to put your piece" << std::endl;
		}
		if (isWin) {
			std::cout << "P2 win!" << std::endl;
		}
	}
}


bool Draw() {
	int count=0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			if (a[i][j]!='*') {
				count++;
			}
		}
	}
	if (count==42) {
		return true;
	}
	return false;
}



int main()
{
	bool isGameOver=false;
	bool isInputOver;

	Initial();

	while (!isGameOver) {
		isInputOver = false;
		while (!isInputOver) {
			PrintText(1);
			GetInput();
			isInputOver = ProcessInput(INPUT);
		}
		std::cout << std::endl;
		PrintBoard('X');
		isGameOver = CheckWin('X');
		if (isGameOver) {
			PrintText(1);
			break;
		}
		isInputOver = false;
		while (!isInputOver) {
			PrintText(2);
			GetInput();
			isInputOver = ProcessInput(INPUT);
		}
		std::cout << std::endl;
		PrintBoard('O');
		isGameOver = CheckWin('O');
		if (isGameOver) {
			PrintText(2);
			break;
		}

		if (Draw()) {
			std::cout << "Game draw!"<<std::endl;
			break;
		}
	}

	std::cin.get();
	return 0;
}




