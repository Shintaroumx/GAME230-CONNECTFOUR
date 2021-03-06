#include "pch.h"
#include <iostream>
#include<string>

//global variable
char a[6][7];
int INPUT;
int ROW;
bool removeModeFlag=false;
bool wrapModeFlag = false;
bool modeSelectOver = false;
bool isGameOver = false;
bool reset = false;


void CheckInput() {
	int num;
	std::cin >> num;
	while (!std::cin.good())
	{
		std::cin.clear(); // Clear error flags.
		std::cin.ignore(1000, '\n'); // Ignore rest.
		std::cin >> num; // Try again.
	}
	std::cin.ignore(1000, '\n'); // Ignore rest.
}


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
	for (int i = 0; i < 6; i++) {
		markCount = 0;
		for (int j = 0; j < 7; j++) {
			if (a[i][j] == mark) {
				if (++markCount == 4) {
					return true;
				}
			}
			if (a[i][j] != mark) {
				markCount = 0;
			}
		}
	}

	for (int j = 0; j < 7; j++) {
		int markCount = 0;
		for (int i = 0; i < 6; i++) {
			if (a[i][j] == mark) {
				if (++markCount == 4) {
					return true;
				}
			}
			if (a[i][j] != mark) {
				markCount = 0;
			}
		}
	}

	for (int p = 0; p < 12; p++) {
		markCount = 0;
		for (int i = 0; i <= p; i++) {
			if (i < 6 && p - i < 7) {
				if (a[i][p - i] == mark) {
					if (++markCount == 4) {
						return true;
					}
				}
				if (a[i][p - i] != mark) {
					markCount = 0;
				}
			}
		}
	}

	for (int p = -5; p < 7; p++) {
		markCount = 0;
		for (int i = 5; i >= 0; i--) {
			if (i >= 0 && p + i < 7) {
				if (a[i][p + i] == mark) {
					if (++markCount == 4) {
						return true;
					}
				}
				if (a[i][p + i] != mark) {
					markCount = 0;
				}
			}
		}
	}


	if (wrapModeFlag) {
		if (a[ROW][0] == mark && a[ROW][1] == mark && a[ROW][2] == mark && a[ROW][6] == mark) {
			return true;
		}
		if (a[ROW][0] == mark && a[ROW][1] == mark && a[ROW][5] == mark && a[ROW][6] == mark) {
			return true;
		}
		if (a[ROW][0] == mark && a[ROW][4] == mark && a[ROW][5] == mark && a[ROW][6] == mark) {
			return true;
		}
		for (int i = 0; i < 3; i++) {
			if (a[i][1] == mark && a[i + 1][0] == mark && a[i + 2][6] == mark && a[i + 3][5] == mark) {
				return true;
			}
		}
		for (int i = 0; i < 3; i++) {
			if (a[i][5] == mark && a[i + 1][6] == mark && a[i + 2][0] == mark && a[i + 3][1] == mark) {
				return true;
			}
		}
		for (int i = 0; i < 3; i++) {
			if (a[i][2] == mark && a[i + 1][1] == mark && a[i + 2][0] == mark && a[i + 3][6] == mark) {
				return true;
			}
		}
		for (int i = 0; i < 3; i++) {
			if (a[i][0] == mark && a[i + 1][6] == mark && a[i + 1][5] == mark && a[i + 2][4] == mark) {
				return true;
			}
		}
		for (int i = 0; i < 3; i++) {
			if (a[i][0] == mark && a[i + 1][1] == mark && a[i + 1][2] == mark && a[i + 2][6] == mark) {
				return true;
			}
		}
		for (int i = 0; i < 3; i++) {
			if (a[i][4] == mark && a[i + 1][5] == mark && a[i + 1][6] == mark && a[i + 2][0] == mark) {
				return true;
			}
		}
		return false;
	}
}


void GetInput() {
	std::cin >> INPUT;
	INPUT--;
	std::cin.clear();
	std::cin.ignore(1000, '\n');
}


bool ProcessInput(int n, char mark) {

	if (!removeModeFlag) {
		if (n < 0 || n>6) {
			std::cout << "Please input an integer from 1 to 7!" << std::endl;
			return false;
		}
		if (a[0][n] != '*') {
			std::cout << "This coloum is full. Please choose another one!" << std::endl;
		}

		for (int i = 5; i >= 0; i--) {
			if (a[i][n] == '*') {
				ROW = i;
				return true;
			}
		}
	}

	if (removeModeFlag) {
		if (n < 0 || n>6&&n!=10&& n != 21&&n != 32&&n!=43&& n != 54&& n != 65&& n != 76) {
			std::cout << "Please input a valid number" << std::endl;
			return false;
		}
		if (a[0][n] != '*'&&n != 10 && n != 21&& n != 32 && n != 43 && n != 54 && n != 65 && n != 76) {
			std::cout << "This coloum is full. Please choose another one!" << std::endl;
		}

		if (n == 10 || n == 21 || n == 32 || n == 43 ||n == 54 || n == 65 || n == 76) {
			if (a[5][(n + 1) / 11 - 1] == mark) {
				return true;
			}
			else {
				std::cout << "You cannot remove your opponent's piece. Please choose your own piece!" << std::endl;
			}
		}

		for (int i = 5; i >= 0; i--) {
			if (a[i][n] == '*'&&n != 10 && n != 21 && n != 32 && n != 43 && n != 54 && n != 65 && n != 76) {
				ROW = i;
				return true;
			}
		}
	}
	return false;
}


void PrintBoard(char mark) {
	if (INPUT != 10 && INPUT != 21 && INPUT != 32 && INPUT != 43 && INPUT != 54 && INPUT != 65 && INPUT != 76) {
	    a[ROW][INPUT] = mark;
}

	if (removeModeFlag) {
		if (INPUT == 10&&a[5][0]==mark) {
			for (int k = 4; k >= 0; k--) {
				a[k + 1][0] = a[k][0];
			}
			a[0][0] = '*';
		}

		if (INPUT == 21 && a[5][1] == mark) {
			for (int k = 4; k >= 0; k--) {
				a[k + 1][1] = a[k][1];
			}
			a[0][1] = '*';
		}

		if (INPUT == 32 && a[5][2] == mark) {
			for (int k = 4; k >= 0; k--) {
				a[k + 1][2] = a[k][2];
			}
			a[0][2] = '*';
		}

		if (INPUT == 43 && a[5][3] == mark) {
			for (int k = 4; k >= 0; k--) {
				a[k + 1][3] = a[k][3];
			}
			a[0][3] = '*';
		}

		if (INPUT == 54 && a[5][4] == mark) {
			for (int k = 4; k >= 0; k--) {
				a[k + 1][4] = a[k][4];
			}
			a[0][4] = '*';
		}

		if (INPUT == 65 && a[5][5] == mark) {
			for (int k = 4; k >= 0; k--) {
				a[k + 1][5] = a[k][5];
			}
			a[0][5] = '*';
		}

		if (INPUT == 76 && a[5][6] == mark) {
			for (int k = 4; k >=0; k--) {
				a[k +1][6] = a[k][6];
			}
			a[0][6] = '*';
		}
	}

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


void ModeSelect() {
    std::string wm;
	std::string rm;
	bool wmSelectOver=false;
	bool rmSelectOver=false;

	while (!wmSelectOver) {
		std::cout << "Would you like to turn on the wrapmode? Enter 'y' or 'n'" << std::endl;
		std::cin >> wm;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		if (wm == "y") {
			wrapModeFlag = true;
			wmSelectOver = true;
			break;
		}
		if (wm == "n") {
			wrapModeFlag = false;
			wmSelectOver = true;
			break;
		}
		if (wm != "y"&&wm != "n") {
			std::cout << "Please enter a valid letter" << std::endl;
			wmSelectOver = false;
		}
		
	}

	while (!rmSelectOver) {
		std::cout << "Would you like to turn on the removemode? Enter 'y' or 'n'" << std::endl;
		std::cin >> rm;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		if (rm == "y") {
			std::cout << "Please double the number if you want to commit a remove. For example, enter 33 if you want to remove the 3rd coloum at the bottom." << std::endl;
			removeModeFlag = true;
			rmSelectOver = true;
			modeSelectOver = true;
			break;
		}
		if (rm == "n") {
			removeModeFlag = false;
			rmSelectOver = true;
			modeSelectOver = true;
			break;
		}
		if (rm != "y"&&rm != "n") {
			std::cout << "Please enter a valid letter" << std::endl;
			rmSelectOver = false;
		}
	}

}


void Restart() {
	isGameOver = false;
	modeSelectOver = false;
	reset = true;
	Initial();
}



int main()
{
	bool isInputOver; 
	bool startTrigger=false;
	std::string  endInfo;

	while (!modeSelectOver) {
		ModeSelect();
	}

	if (modeSelectOver) {
		Initial();

		while (!isGameOver) {
			reset = false;
			isInputOver = false;
			while (!isInputOver) {
				PrintText(1);
				GetInput();
				isInputOver = ProcessInput(INPUT, 'X');
			}
			std::cout << std::endl;
			PrintBoard('X');
			isGameOver = CheckWin('X');
			if (isGameOver) {
				PrintText(1);
				std::cout << "Would you like to play again? Enter 'y' to restart and any other key to exit." << std::endl;
				std::cin >> endInfo;
				if (endInfo == "y") {
					Restart();
					std::cin.clear();
					std::cin.ignore(1000, '\n');
				}
				else {
					break;
				}
			}

			isInputOver = false;
			if(!reset) {
			while (!isInputOver) {
				PrintText(2);
				GetInput();
				isInputOver = ProcessInput(INPUT, 'O');
			}
			std::cout << std::endl;
			PrintBoard('O');
			isGameOver = CheckWin('O');
			if (isGameOver) {
				PrintText(2);
				std::cout << "Would you like to play again? Enter 'y' to restart and any other key to exit." << std::endl;
				std::cin >> endInfo;
				if (endInfo == "y") {
					Restart();
					std::cin.clear();
					std::cin.ignore(1000, '\n');
				}
				else {
					break;
				}
			}
		}

			if (Draw()) {
				std::cout << "Game draw!" << std::endl;
				std::cout << "Would you like to play again? Enter 'y' to restart and any other key to exit." << std::endl;
				std::cin >> endInfo;
				if (endInfo == "y") {
					Restart();
					std::cin.clear();
					std::cin.ignore(1000, '\n');
				}
				else {
					break;
				}
			}
		}
	}

	std::cin.get();
	return 0;
}




