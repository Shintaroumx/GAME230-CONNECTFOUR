#include "pch.h"
#include "AI.h"
#include "math.h"
#include<random>


static int iNFINITY = 100;   // ��ʾ�����ֵ
static int WIN = +iNFINITY;   // MAX���������Ϊ������
static int LOSE = -iNFINITY;   // MAX����С���棨��MIN�������棩Ϊ������
static int DOUBLE_LINK = iNFINITY / 2;   // ���ͬһ�С��л�Խ�������������������
static int INPROGRESS = 1;   // �Կɼ����£�û��ʤ����;֣�
static int DRAW = 0;   // �;�
static int** WIN_STATUS= {
	  { 0, 1, 2 },
	  { 3, 4, 5 },
	  { 6, 7, 8 },
	  { 0, 3, 6 },
	  { 1, 4, 7 },
	  { 2, 5, 8 },
	  { 0, 4, 8 },
	  { 2, 4, 6 }
};
/**
 * ��ֵ�������ṩһ������ʽ��ֵ����������ϷAI�ĸߵ�
 */
int gameState(char* board) {
	int result = INPROGRESS;
	bool isFull = true;

	// is game over?
	for (int pos = 0; pos < 9; pos++) {
		char chess = board[pos];
		if (chess== '*') {
			isFull = false;
			break;
		}
	}
	// is Max win/lose?
	for (int* status : WIN_STATUS) {
		char chess = board[status[0]];
		if (chess == '*') {
			break;
		}
		int   i = 1;
		for (; i < status.length; i++) {
			if (board[status[i]] != chess) {
				break;
			}
		}
		if (i == status.length) {
			result = chess == 'X' ? WIN : LOSE;
			break;
		}
	}
	if (result != WIN && result != LOSE) {
		if (isFull) {
			// is draw
			result = DRAW;
		}
		else {
			// check double link
			// finds[0]->'x', finds[1]->'o'
			int* finds = new   int[2];
			for (int* status : WIN_STATUS) {
				char chess = '*';
				bool hasEmpty = false;
				int count = 0;
				for (int i = 0; i < status.length; i++) {
					if (board[status[i]] == '*') {
						hasEmpty = true;
					}
					else {
						if (chess == '*') {
							chess = board[status[i]];
						}
						if (board[status[i]] == chess) {
							count++;
						}
					}
				}
				if (hasEmpty && count > 1) {
					if (chess == 'X') {
						finds[0]++;
					}
					else {
						finds[1]++;
					}
				}
			}
			// check if two in one line
			if (finds[1] > 0) {
				result = -DOUBLE_LINK;
			}
			else if (finds[0] > 0) {
				result = DOUBLE_LINK;
			}
		}
	}
	return result;
}


/**
 * ��'x'�ĽǶ������ǵļ�С�����㷨
 */
 int minimax(char* board, int   depth) {
	int* bestMoves = new int[9];
	int index = 0;

	int bestValue = -iNFINITY;
	for (int pos = 0; pos < 9; pos++) {

		if (board[pos] == '*') {
			board[pos] = 'X';

			int value = min(board, depth, -iNFINITY, +iNFINITY);
			if (value > bestValue) {
				bestValue = value;
				index = 0;
				bestMoves[index] = pos;
			}
			else
				if (value == bestValue) {
					index++;
					bestMoves[index] = pos;
				}

			board[pos] = '*';
		}

	}

	/*if (index > 1) {
		index = (new Random(System.currentTimeMillis()).nextInt() >>> 1) % index;
	}*/

}

/**
 * ����'x'����ֵԽ�����Խ����
 */
int max(char* board, int   depth, int   alpha, int   beta) {

	int evalValue = gameState(board);

	bool isGameOver = (evalValue == WIN || evalValue == LOSE || evalValue == DRAW);
	if (beta <= alpha) {
		return   evalValue;
	}
	if (depth == 0 || isGameOver) {
		return evalValue;
	}

	int bestValue = -iNFINITY;
	for (int pos = 0; pos < 9; pos++) {

		if (board[pos] == '*') {
			// try
			board[pos] ='X';

			//   maximixing
			bestValue = fmax(bestValue, min(board, depth - 1, fmax(bestValue, alpha), beta));

			// reset
			board[pos] = '*';
		}

	}

	return bestValue;

}

/**
 * ����'o'����ֵԽС����Խ����
 */
int min(char* board, int   depth, int   alpha, int   beta) {

	int evalValue = gameState(board);

	bool isGameOver = (evalValue == WIN || evalValue == LOSE || evalValue == DRAW);
	if (alpha >= beta) {
		return evalValue;
	}
	// try
	if (depth == 0 || isGameOver || alpha >= beta) {
		return evalValue;
	}

	int bestValue = +iNFINITY;
	for (int pos = 0; pos < 9; pos++) {

		if (board[pos] == '*') {
			// try
			board[pos] = 'O';

			//   minimixing
			bestValue = fmin(bestValue, max(board, depth - 1, alpha, fmin(bestValue, beta)));

			// reset
			board[pos] = '*';
		}

	}

	return bestValue;

}


AI::AI()
{
}


AI::~AI()
{
}
