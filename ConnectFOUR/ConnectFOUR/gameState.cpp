#include "pch.h"
#include "gameState.h"


gameState::gameState(char* board)
{
	static int  INFINITY = 100;   // ��ʾ�����ֵ
	static int  WIN = +INFINITY;   // MAX���������Ϊ������
	static int  LOSE = -INFINITY;   // MAX����С���棨��MIN�������棩Ϊ������
	static int  DOUBLE_LINK = INFINITY / 2;   // ���ͬһ�С��л�Խ�������������������
	static int  INPROGRESS = 1;   // �Կɼ����£�û��ʤ����;֣�
	static int  DRAW = 0;   // �;�
	static int[][] WIN_STATUS = {
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
	 
		int   result = INPROGRESS;
		bool  isFull = true;

		// is game over?
		for (int pos = 0; pos < 9; pos++) {
			char   chess = board[pos];
			if (empty == chess) {
				isFull = false;
				break;
			}
		}
		// is Max win/lose?
		for (int[] status : WIN_STATUS) {
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
				int[] finds = new   int[2];
				for (int[] status : WIN_STATUS) {
					char   chess = empty;
					boolean   hasEmpty = false;
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



gameState::~gameState()
{
}
