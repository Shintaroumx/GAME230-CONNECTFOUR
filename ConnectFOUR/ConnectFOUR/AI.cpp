#include "pch.h"
#include "AI.h"
#include "math.h"


static int  iNFINITY = 100;   // ��ʾ�����ֵ
static int  WIN = +iNFINITY;   // MAX���������Ϊ������
static int  LOSE = -iNFINITY;   // MAX����С���棨��MIN�������棩Ϊ������
static int  DOUBLE_LINK = iNFINITY / 2;   // ���ͬһ�С��л�Խ�������������������
static int  INPROGRESS = 1;   // �Կɼ����£�û��ʤ����;֣�
static int  DRAW = 0;   // �;�
static int WIN_STATUS[][] = {
	  {   0, 1, 2 },
	  { 3, 4, 5 },
	  { 6, 7, 8 },
	  { 0, 3, 6 },
	  { 1, 4, 7 },
	  { 2, 5, 8 },
	  { 0, 4, 8 },
	  { 2, 4, 6   }
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
		if (chess==nullptr) {
			isFull = false;
			break;
		}
	}
	// is Max win/lose?
	for (int* status : WIN_STATUS) {
		char   chess = board[status[0]];
		if (chess == empty) {
			break;
		}
		int   i = 1;
		for (; i < status.length; i++) {
			if (board[status[i]] != chess) {
				break;
			}
		}
		if (i == status.length) {
			result = chess == x ? WIN : LOSE;
			break;
		}
	}
	if (result != WIN & result != LOSE) {
		if (isFull) {
			// is draw
			result = DRAW;
		}
		else {
			// check double link
			// finds[0]->'x', finds[1]->'o'
			int* finds = new   int[2];
			for (int* status : WIN_STATUS) {
				char   chess = empty;
				bool   hasEmpty = false;
				int   count = 0;
				for (int i = 0; i < status.length; i++) {
					if (board[status[i]] == empty) {
						hasEmpty = true;
					}
					else {
						if (chess == empty) {
							chess = board[status[i]];
						}
						if (board[status[i]] == chess) {
							count++;
						}
					}
				}
				if (hasEmpty && count > 1) {
					if (chess == x) {
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
			else   if (finds[0] > 0) {
				result = DOUBLE_LINK;
			}
		}
	}
	return   result;
}


/**
 * ��'x'�ĽǶ������ǵļ�С�����㷨
 */
 int minimax(char* board, int   depth) {
	int* bestMoves = new int[9];
	int   index = 0;

	int   bestValue = -iNFINITY;
	for (int pos = 0; pos < 9; pos++) {

		if (board[pos] == empty) {
			board[pos] = x;

			int   value = min(board, depth, -iNFINITY, +iNFINITY);
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

			board[pos] = empty;
		}

	}

	if (index > 1) {
		index = (new   Random(System.currentTimeMillis()).nextInt() >>> 1) % index;
	}
	return   bestMoves[index];

}
/**
 * ����'x'����ֵԽ�����Խ����
 */
int   max(char* board, int   depth, int   alpha, int   beta) {

	int   evalValue = gameState(board);

	bool isGameOver = (evalValue == WIN || evalValue == LOSE || evalValue == DRAW);
	if (beta <= alpha) {
		return   evalValue;
	}
	if (depth == 0 || isGameOver) {
		return   evalValue;
	}

	int   bestValue = -iNFINITY;
	for (int pos = 0; pos < 9; pos++) {

		if (board[pos] == empty) {
			// try
			board[pos] = x;

			//   maximixing
			bestValue = fmax(bestValue, min(board, depth - 1, fmax(bestValue, alpha), beta));

			// reset
			board[pos] = empty;
		}

	}

	return   evalValue;

}

/**
 * ����'o'����ֵԽС����Խ����
 */

int   min(char* board, int   depth, int   alpha, int   beta) {

	int   evalValue = gameState(board);

	bool isGameOver = (evalValue == WIN || evalValue == LOSE || evalValue == DRAW);
	if (alpha >= beta) {
		return   evalValue;
	}
	// try
	if (depth == 0 || isGameOver || alpha >= beta) {
		return   evalValue;
	}

	int   bestValue = +iNFINITY;
	for (int pos = 0; pos < 9; pos++) {

		if (board[pos] == empty) {
			// try
			board[pos] = o;

			//   minimixing
			bestValue = fmin(bestValue, max(board, depth - 1, alpha, fmin(bestValue, beta)));

			// reset
			board[pos] = empty;
		}

	}

	return   evalValue;

}


AI::AI()
{
}


AI::~AI()
{
}
