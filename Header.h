#pragma once
#include<typeinfo>

using namespace std;

class Chess;

class Chessman {
public:
	bool side;
protected:
	Chessman(const bool _side) {
		side = _side;
	}
	virtual bool is_possible(const int&x1, const int&y1, const int&x2, const int&y2, Chessman*board[][8]) = 0;
	Chessman(){}
	friend class Chess;
	virtual ~Chessman(){}
};

class King : virtual public Chessman {
protected:
	bool is_possible(const int&x1, const int&y1, const int&x2, const int&y2, Chessman*board[][8]);
public:
	King(const bool _side) {
		side = _side;
	}
	~King(){}
};

bool King::is_possible(const int&x1, const int&y1, const int&x2, const int&y2, Chessman*board[][8]) {
	short x = x1 + 1, y = y1;
	if (x2 == x && y2 == y) return true;
	x = x1 + 1, y = y1 + 1;
	if (x2 == x && y2 == y) return true;
	x = x1 + 1, y = y1 - 1;
	if (x2 == x && y2 == y) return true;
	x = x1 - 1, y = y1;
	if (x2 == x && y2 == y) return true;
	x = x1 - 1, y = y1 + 1;
	if (x2 == x && y2 == y) return true;
	x = x1 - 1, y = y1 - 1;
	if (x2 == x && y2 == y) return true;
	x = x1, y = y1 + 1;
	if (x2 == x && y2 == y) return true;
	x = x1, y = y1 - 1;
	if (x2 == x && y2 == y) return true;
	return false;
}

class Queen : virtual public Chessman {
protected:
	bool is_possible(const int&x1, const int&y1, const int&x2, const int&y2, Chessman*board[][8]);
public:
	Queen(const bool _side) {
		side = _side;
	}
};

bool Queen::is_possible(const int&x1, const int&y1, const int&x2, const int&y2, Chessman*board[][8]) {
	for (short x = x1 + 1, y = y1; x < 8; x++) {
		if (x2 == x && y2 == y) return true;
		if (board[x][y]) break;
	}
	for (short x = x1 - 1, y = y1; x >= 0; x--) {
		if (x2 == x && y2 == y) return true;
		if (board[x][y]) break;
	}
	for (short x = x1, y = y1 + 1; y < 8; y++) {
		if (x2 == x && y2 == y) return true;
		if (board[x][y]) break;
	}
	for (short x = x1, y = y1 - 1; y >= 0; y--) {
		if (x2 == x && y2 == y) return true;
		if (board[x][y]) break;
	}
	for (short x = x1 + 1, y = y1 + 1; x < 8 && y < 8; x++, y++) {
		if (x2 == x && y2 == y) return true;
		if (board[x][y]) break;
	}
	for (short x = x1 - 1, y = y1 + 1; x >= 0 && y < 8; x--, y++) {
		if (x2 == x && y2 == y) return true;
		if (board[x][y]) break;
	}
	for (short x = x1 + 1, y = y1 - 1; x < 8 && y >= 0; x++, y--) {
		if (x2 == x && y2 == y) return true;
		if (board[x][y]) break;
	}
	for (short x = x1 - 1, y = y1 - 1; x >= 0 && y >= 0; x--, y--) {
		if (x2 == x && y2 == y) return true;
		if (board[x][y]) break;
	}
	return false;
}

class Rook : virtual public Chessman {
protected:
	bool is_possible(const int&x1, const int&y1, const int&x2, const int&y2, Chessman*board[][8]);
public:
	Rook(const bool _side) {
		side = _side;
	}
};

bool Rook::is_possible(const int&x1, const int&y1, const int&x2, const int&y2, Chessman*board[][8]) {
	for (short x = x1 + 1, y = y1; x < 8; x++) {
		if (x2 == x && y2 == y) return true;
		if (board[x][y]) break;
	}
	for (short x = x1 - 1, y = y1; x >= 0; x--) {
		if (x2 == x && y2 == y) return true;
		if (board[x][y]) break;
	}
	for (short x = x1, y = y1 + 1; y < 8; y++) {
		if (x2 == x && y2 == y) return true;
		if (board[x][y]) break;
	}
	for (short x = x1, y = y1 - 1; y >= 0; y--) {
		if (x2 == x && y2 == y) return true;
		if (board[x][y]) break;
	}
	return false;
}

class Bishop : virtual public Chessman {
protected:
	bool is_possible(const int&x1, const int&y1, const int&x2, const int&y2, Chessman*board[][8]);
public:
	Bishop(const bool _side) {
		side = _side;
	}
};

bool Bishop::is_possible(const int&x1, const int&y1, const int&x2, const int&y2, Chessman*board[][8]) {
	for (short x = x1 + 1, y = y1 + 1; x < 8 && y < 8; x++, y++) {
		if (x2 == x && y2 == y) return true;
		if (board[x][y]) break;
	}
	for (short x = x1 - 1, y = y1 + 1; x >= 0 && y < 8; x--, y++) {
		if (x2 == x && y2 == y) return true;
		if (board[x][y]) break;
	}
	for (short x = x1 + 1, y = y1 - 1; x < 8 && y >= 0; x++, y--) {
		if (x2 == x && y2 == y) return true;
		if (board[x][y]) break;
	}
	for (short x = x1 - 1, y = y1 - 1; x >= 0 && y >= 0; x--, y--) {
		if (x2 == x && y2 == y) return true;
		if (board[x][y]) break;
	}
	return false;
}

class Knight : virtual public Chessman {
protected:
	bool is_possible(const int&x1, const int&y1, const int&x2, const int&y2, Chessman*board[][8]);
public:
	Knight(const bool _side) {
		side = _side;
	}
};

bool Knight::is_possible(const int&x1, const int&y1, const int&x2, const int&y2, Chessman*board[][8]) {
	if (x1 + 2 == x2 && (y1 + 1 == y2 || y1 - 1 == y2)) return true;
	if (x1 - 2 == x2 && (y1 + 1 == y2 || y1 - 1 == y2)) return true;
	if (x1 + 1 == x2 && (y1 + 2 == y2 || y1 - 2 == y2)) return true;
	if (x1 - 1 == x2 && (y1 + 2 == y2 || y1 - 2 == y2)) return true;
	return false;
}


class Pawn : virtual public Chessman {
protected:
	bool is_possible(const int&x1, const int&y1, const int&x2, const int&y2, Chessman*board[][8]);
public:
	Pawn(const bool _side) {
		side = _side;
	}
};

bool Pawn::is_possible(const int&x1, const int&y1, const int&x2, const int&y2, Chessman*board[][8]) {
	if (side) {
		if (x1 + 1 < 8 && y1 + 1 < 8 && board[x1 + 1][y1 + 1]) {
			if (x1 - 1 < 8 && y1 + 1 < 8 && board[x1 - 1][y1 + 1])
				if (y1 + 1 < 8 && !board[x1][y1 + 1]) {
					if (y1 == 1 && y1 + 2 < 8 && !board[x1][y1 + 2]) {
						if ((x2 == x1 && (y1 < y2 && y1 + 2 >= y2)) || (y2 == y1 + 1 && (x2 == x1 + 1 || x2 == x1 - 1))) return true;
						else return false;
					}
					else if ((x2 == x1 && y1 + 1 == y2) || (y2 == y1 + 1 && (x2 == x1 + 1 || x2 == x1 - 1))) return true;
					else return false;
				}
				else if (y2 == y1 + 1 && (x2 == x1 + 1 || x2 == x1 - 1)) return true;
				else return false;
			else if (y1 + 1 < 8 && !board[x1][y1 + 1]) {
				if (y1 == 1 && y1 + 2 < 8 && !board[x1][y1 + 2]) {
					if ((x2 == x1 && (y1 < y2 && y1 + 2 >= y2)) || (y2 == y1 + 1 && x2 == x1 + 1)) return true;
					else return false;
				}
				else if ((x2 == x1 && y1 + 1 == y2) || (y2 == y1 + 1 && x2 == x1 + 1)) return true;
				else return false;
			}
			else if (y2 == y1 + 1 && x2 == x1 + 1) return true;
			else return false;
		}
		else if (x1 - 1 < 8 && y1 + 1 < 8 && board[x1 - 1][y1 + 1])
			if (y1 + 1 < 8 && !board[x1][y1 + 1]) {
				if (y1 == 1 && y1 + 2 < 8 && !board[x1][y1 + 2]) {
					if ((x2 == x1 && (y1 < y2 && y1 + 2 >= y2)) || (y2 == y1 + 1 && x2 == x1 - 1)) return true;
					else return false;
				}
				else if ((x2 == x1 && y1 + 1 == y2) || (y2 == y1 + 1 && x2 == x1 - 1)) return true;
				else return false;
			}
			else if (y2 == y1 + 1 && x2 == x1 - 1) return true;
			else return false;
		else if (y1 + 1 < 8 && !board[x1][y1 + 1]) {
			if (y1 == 1 && y1 + 2 < 8 && !board[x1][y1 + 2]) {
				if (x2 == x1 && (y1 < y2 && y1 + 2 >= y2)) return true;
				else return false;
			}
			else if (x2 == x1 && y1 + 1 == y2) return true;
			else return false;
		}
	}
	else if (x1 + 1 < 8 && y1 - 1 >= 0 && board[x1 + 1][y1 - 1]) {
		if (x1 - 1 < 8 && y1 - 1 >= 0 && board[x1 - 1][y1 - 1])
			if (y1 - 1 >= 0 && !board[x1][y1 - 1]) {
				if (y1 == 6 && y1 - 2 >= 0 && !board[x1][y1 - 2]) {
					if ((x2 == x1 && (y1 > y2 && y1 - 2 <= y2)) || (y2 == y1 - 1 && (x2 == x1 + 1 || x2 == x1 - 1))) return true;
					else return false;
				}
				else if ((x2 == x1 && y1 - 1 == y2) || (y2 == y1 - 1 && (x2 == x1 + 1 || x2 == x1 - 1))) return true;
				else return false;
			}
			else if (y2 == y1 - 1 && (x2 == x1 + 1 || x2 == x1 - 1)) return true;
			else return false;
		else if (y1 - 1 >= 0 && !board[x1][y1 - 1]) {
			if (y1 == 6 && y1 - 2 >= 0 && !board[x1][y1 - 2]) {
				if ((x2 == x1 && (y1 > y2 && y1 - 2 <= y2)) || (y2 == y1 - 1 && x2 == x1 + 1)) return true;
				else return false;
			}
			else if ((x2 == x1 && y1 - 1 == y2) || (y2 == y1 - 1 && x2 == x1 + 1)) return true;
			else return false;
		}
		else if (y2 == y1 - 1 && x2 == x1 + 1) return true;
		else return false;
	}
	else if (x1 - 1 < 8 && y1 - 1 >= 0 && board[x1 - 1][y1 - 1])
		if (y1 - 1 >= 0 && !board[x1][y1 - 1]) {
			if (y1 == 6 && y1 - 2 >= 0 && !board[x1][y1 - 2]) {
				if ((x2 == x1 && (y1 > y2 && y1 - 2 <= y2)) || (y2 == y1 - 1 && x2 == x1 - 1)) return true;
				else return false;
			}
			else if ((x2 == x1 && y1 - 1 == y2) || (y2 == y1 - 1 && x2 == x1 - 1)) return true;
			else return false;
		}
		else if (y2 == y1 - 1 && x2 == x1 - 1) return true;
		else return false;
	else if (y1 - 1 >= 0 && !board[x1][y1 - 1]) {
		if (y1 == 6 && y1 - 2 >= 0 && !board[x1][y1 - 2]) {
			if (x2 == x1 && (y1 > y2 && y1 - 2 <= y2)) return true;
			else return false;
		}
		else if (x2 == x1 && y1 - 1 == y2) return true;
		else return false;
	}
	else return false;
}

class Chess {
private:
	Chessman*WhiteKing;
	Chessman*BlackKing;
	friend void innit(Chess&obj);
public:
	Chessman*board[8][8];
	bool turn;
	Chess() {
		turn = true;
		innit(*this);
	}
	int DoMove(int x1, int y1, int x2, int y2);
};

int Chess::DoMove(int x1, int y1, int x2, int y2) {
	if (x2 > 7 || x2 < 0 || y2 > 7 || y2 < 0) return 6;
	if (x1 > 7 || x1 < 0 || y1 > 7 || y1 < 0) return 7;
	if (x1 == x2 && y1 == y2) return 5;
	if (board[x1][y1] == nullptr) return 1;
	if (board[x1][y1]->side != turn) return 2;
	if (board[x2][y2] && board[x2][y2]->side == turn) return 4;
	if (!board[x1][y1]->is_possible(x1, y1, x2, y2, board)) return 8;
	else {
		if (board[x2][y2]) {
			if (typeid(*board[x2][y2]) == typeid(King)) {
				if (board[x2][y2]->side) return -10;
				else return 10;
			}
		}
		board[x2][y2] = board[x1][y1];
		board[x1][y1] = nullptr;
		turn = !turn;
		return 0;
	}
}

void innit(Chess & obj)
{
	for (int i = 0; i < 8; i++) {
		obj.board[i][1] = new Pawn(true);
		obj.board[i][6] = new Pawn(false);
	}
	obj.board[0][0] = new Rook(true);
	obj.board[1][0] = new Knight(true);
	obj.board[2][0] = new Bishop(true);
	obj.board[3][0] = new Queen(true);
	obj.board[4][0] = new King(true);
	obj.WhiteKing = obj.board[3][0];
	obj.board[7][0] = new Rook(true);
	obj.board[6][0] = new Knight(true);
	obj.board[5][0] = new Bishop(true);
	obj.board[0][7] = new Rook(false);
	obj.board[1][7] = new Knight(false);
	obj.board[2][7] = new Bishop(false);
	obj.board[3][7] = new Queen(false);
	obj.board[4][7] = new King(false);
	obj.BlackKing = obj.board[3][7];
	obj.board[7][7] = new Rook(false);
	obj.board[6][7] = new Knight(false);
	obj.board[5][7] = new Bishop(false);
	for (short i = 0; i < 8; i++) {
		for (short j = 2; j < 6; j++) {
			obj.board[i][j] = nullptr;
		}
	}
}