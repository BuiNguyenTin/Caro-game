#include "Board.h"

Board::Board(int p_size, int pX, int pY) :
	_size(p_size), _left(pX), _top(pY)
{
	_pArr = new Point * [p_size];
	for (int i = 0; i < p_size; i++)
		_pArr[i] = new Point[p_size];
	_countX = _countO = 0;
	_winPos = nullptr;
}

Board::~Board()
{
	for (int i = 0; i < _size; i++)
		delete[] _pArr[i];
	delete[] _pArr,
		_pArr = nullptr;
	delete[] _winPos;
	_winPos = nullptr;
}

int Board::getSize()
{
	return _size;
}

int Board::getLeft()
{
	return _left;
}

int Board::getTop()
{
	return _top;
}

int Board::getCountX()
{
	return _countX;
}

int Board::getCountO()
{
	return _countO;
}

int Board::getXAt(int i, int j)
{
	return _pArr[i][j].getX();
}

int Board::getYAt(int i, int j)
{
	return _pArr[i][j].getY();
}

void Board::resetData()
{
	if (_size == 0)
		return;									// Firstly calling constructor before calling resetData
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			_pArr[i][j].setX(4 * j + _left + 3); // x-value of boardgame
			_pArr[i][j].setY(2 * i + _top + 1); // y-value of boardgame
			_pArr[i][j].setCheck(0);
		}
	}
	_countX = _countO = 0;
}

void Board::drawBoard()
{
	if (_pArr == NULL)
		return;
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::clearConsole();

	//Ve duong tren
	Common::gotoXY(_left + 1, _top);
	cout <<'*';
	for (int i = 1; i < _size * 4; i++)
	{
		Sleep(5);
		cout << '-';
	}
	cout << '*';


	//Ve duong ben phai
	for (int i = 1; i < _size * 2; i++)
	{
		Sleep(10);
		Common::gotoXY(_size * 4 + _left + 1, i + _top);
		cout << '|';
	}
	Common::gotoXY(_size * 4 + _left + 1, _size * 2 + _top);
	cout << '*';


	//Ve duong duoi
	for (int i = 1; i < _size * 4; i++)
	{
		Common::gotoXY(_size * 4 + _left - i + 1, _size * 2 + _top);
		Sleep(5);
		cout << '-';
	}
	Common::gotoXY(_left + 1, _size * 2 + _top);
	cout << '*';

	//Ve duong ben trai
	for (int i = 1; i < _size * 2; i++)
	{
		Sleep(10);
		Common::gotoXY(_left + 1, _size * 2 + _top - i);
		cout << '|';
	}

	//Ve cac duong doc
	for (int i = 1; i < _size * 2; i++)
	{
		for (int j = 4; j < _size * 4; j += 4)
		{
			if (i % 2 != 0)
			{
				Common::gotoXY(j + _left + 1, i + _top);
				cout << '|';
			}
		}
		Sleep(10);
	}

	//Ve cac duong ngang
	for (int i = 1; i < _size * 4; i++)
	{
		for (int j = 2; j < _size * 2; j += 2)
		{
			Common::gotoXY(i + _left + 1, j + _top);
			if (i % 4 == 0)
				cout << '+';
			else
				cout << '-';
		}
		Sleep(5);
	}
}

int Board::checkBoard(int pX, int pY, bool pTurn)
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY)
			{
				if (_pArr[i][j].getCheck() == 0)
				{
					if (pTurn)
					{
						_countX++;
						_pArr[i][j].setCheck(1);
					}
					else
					{
						_countO++;
						_pArr[i][j].setCheck(-1);
					}
					return _pArr[i][j].getCheck();
				}
				else
					return 0;
			}
		}
	}
	throw "Problem with cursor";
}

int Board::testBoard(int pX, int pY) //i,j la row,col cua bang
{
	if (_countX + _countO == _size * _size)
		return 0; // draw
	int i, j;
	[&] {
		for (i = 0; i < _size; i++)
		{
			for (j = 0; j < _size; j++)
			{
				if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY)
					return;
			}
		}
	}();
	int turn = _pArr[i][j].getCheck();
	if (checkRow(i, j, turn) || checkCol(i, j, turn) || checkDiag1(i, j, turn) || checkDiag2(i, j, turn))
		return (turn == 1) ? 1 : -1;
	return 2; // continue
}

int Board::getCheckAtXY(int pX, int pY)
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY)
				return _pArr[i][j].getCheck();
		}
	}
	throw "Problem with cursor position";
}

bool Board::checkCol(int i, int j, int turn)
{
	int up = 0, down = 0;
	int count = 0, col = i;
	while (col <= _size - 1 && _pArr[col][j].getCheck() == _pArr[i][j].getCheck() && _pArr[i][j].getCheck() == turn)
	{
		if (col == _size - 1)
		{
			count++;
			down = col;
			break;
		}
		else
		{
			count++;
			col++;
			down = col;
		}
	}
	count--;
	col = i;
	while (col >= 0 && _pArr[col][j].getCheck() == _pArr[i][j].getCheck() && _pArr[i][j].getCheck() == turn)
	{
		if (col == 0)
		{
			count++;
			up = col;
			break;
		}
		else
		{
			count++;
			col--;
			up = col;
		}
	}
	if (count > 4)
	{
		if ((down == _size - 1 && _pArr[down][j].getCheck() == turn))
		{
			_winPos = new Point[5]{ {down - 4,j},{down - 3,j },{down - 2,j },{down - 1,j },{down ,j } };
			return true;
		}
		else if ((up == 0 && _pArr[up][j].getCheck() == turn))
		{
			_winPos = new Point[5]{ {up + 4,j},{up + 3,j },{up + 2,j },{up + 1,j },{up ,j } };
			return true;
		}
		else if (_pArr[down][j].getCheck() == -turn && _pArr[up][j].getCheck() != -turn)
		{
			_winPos = new Point[5]{ {down - 5,j},{down - 4,j },{down - 3,j },{down - 2,j },{down - 1,j } };
			return true;
		}
		else if (_pArr[up][j].getCheck() == -turn && _pArr[down][j].getCheck() != -turn)
		{
			_winPos = new Point[5]{ {up + 5,j},{up + 4 ,j },{up + 3,j },{up + 2,j },{up + 1,j } };
			return true;
		}
		else if (_pArr[up][j].getCheck() == _pArr[down][j].getCheck() && _pArr[down][j].getCheck() != -turn)
		{
			_winPos = new Point[5]{ {down - 5,j},{down - 4,j },{down - 3,j },{down - 2,j },{down - 1,j } };
			return true;
		}
	}
	return false;
}

bool Board::checkRow(int i, int j, int turn)
{
	int left = 0, right = 0;
	int count = 0, row = j;
	while (row <= _size - 1 && _pArr[i][row].getCheck() == _pArr[i][j].getCheck() && _pArr[i][j].getCheck() == turn)
	{
		if (row == _size - 1)
		{
			count++;
			right = row;
			break;
		}
		else
		{
			count++;
			row++;
			right = row;
		}
	}
	count--;
	row = j;
	while (row >= 0 && _pArr[i][row].getCheck() == _pArr[i][j].getCheck() && _pArr[i][j].getCheck() == turn)
	{
		if (row == 0)
		{
			count++;
			left = row;
			break;
		}
		else
		{
			count++;
			row--;
			left = row;
		}
	}
	if (count > 4)
	{
		if (right == _size - 1 && _pArr[i][right].getCheck() == turn)
		{
			_winPos = new Point[5]{ {i,right},{i ,right - 1},{i ,right - 2},{i,right - 3},{i,right - 4} };
			return true;
		}
		else if (left == 0 && _pArr[i][left].getCheck() == turn)
		{
			_winPos = new Point[5]{ {i,left},{i ,left + 1},{i ,left + 2},{i,left + 3},{i,left + 4} };
			return true;
		}
		else if (_pArr[i][right].getCheck() == -turn && _pArr[i][left].getCheck() != -turn)
		{
			_winPos = new Point[5]{ {i,right - 1},{i ,right - 2},{i ,right - 3},{i ,right - 4},{i ,right - 5} };
			return true;
		}
		else if (_pArr[i][left].getCheck() == -turn && _pArr[i][right].getCheck() != -turn)
		{
			_winPos = new Point[5]{ {i,left + 1},{i ,left + 2},{i ,left + 3},{i ,left + 4},{i ,left + 5} };
			return true;
		}
		else if (_pArr[i][left].getCheck() == _pArr[i][right].getCheck() && _pArr[i][right].getCheck() != -turn)
		{
			_winPos = new Point[5]{ {i,left + 1},{i ,left + 2},{i ,left + 3},{i ,left + 4},{i ,left + 5} };
			return true;
		}
	}
	return false;
}

bool Board::checkDiag1(int i, int j, int turn)
{
	int LR_Col = 0, LR_Row = 0, UL_Col = 0, UL_Row = 0;
	// kiểm tra đường chéo huyền
	int row = i, col = j, count = 0;
	while (col <= _size - 1 && row <= _size - 1 && _pArr[i][j].getCheck() == _pArr[row][col].getCheck() && _pArr[row][col].getCheck() == turn)
	{
		if ((col == _size - 1 && row == _size - 1) || (col == _size - 1) || (row == _size - 1))
		{
			count++;
			LR_Col = col;
			LR_Row = row;
			break;
		}
		else
		{
			count++;
			row++;
			col++;
			LR_Col = col;
			LR_Row = row;
		}
	}
	row = i; col = j, count--;
	while (row >= 0 && col >= 0 && _pArr[i][j].getCheck() == _pArr[row][col].getCheck() && _pArr[row][col].getCheck() == turn)
	{
		if ((col == 0 && row == 0) || (col == 0) || (row == 0))
		{
			count++;
			UL_Col = col;
			UL_Row = row;
			break;
		}
		else
		{
			count++;
			row--;
			col--;
			UL_Col = col;
			UL_Row = row;
		}
	}
	if (count > 4)
	{
		if (LR_Col == _size - 1 && _pArr[LR_Row][LR_Col].getCheck() == turn)
		{
			_winPos = new Point[5]{ {LR_Row,LR_Col},{LR_Row - 1 ,LR_Col - 1},{LR_Row - 2,LR_Col - 2},{LR_Row - 3,LR_Col - 3},{LR_Row - 4,LR_Col - 4} };
			return true;
		}
		if (UL_Col == 0 && _pArr[UL_Row][UL_Col].getCheck() == turn)
		{
			_winPos = new Point[5]{ {UL_Row + 0 ,UL_Col + 0},{UL_Row + 1,UL_Col + 1},{UL_Row + 2,UL_Col + 2},{UL_Row + 3,UL_Col + 3},{UL_Row + 4,UL_Col + 4} };
			return true;
		}
		if (LR_Row == _size - 1 && _pArr[LR_Row][LR_Col].getCheck() == turn)
		{
			_winPos = new Point[5]{ {LR_Row,LR_Col},{LR_Row - 1 ,LR_Col - 1},{LR_Row - 2,LR_Col - 2},{LR_Row - 3,LR_Col - 3},{LR_Row - 4,LR_Col - 4} };
			return true;
		}
		if (UL_Row == 0 && _pArr[UL_Row][UL_Col].getCheck() == turn)
		{
			_winPos = new Point[5]{ {LR_Row - 1 ,LR_Col - 1},{LR_Row - 2,LR_Col - 2},{LR_Row - 3,LR_Col - 3},{LR_Row - 4,LR_Col - 4},{LR_Row - 5,LR_Col - 5} };
			return true;
		}
		if (_pArr[LR_Row][LR_Col].getCheck() == -turn && _pArr[UL_Row][UL_Col].getCheck() != -turn)
		{
			_winPos = new Point[5]{ {LR_Row - 1 ,LR_Col - 1},{LR_Row - 2,LR_Col - 2},{LR_Row - 3,LR_Col - 3},{LR_Row - 4,LR_Col - 4},{LR_Row - 5,LR_Col - 5} };
			return true;
		}
		if (_pArr[UL_Row][UL_Col].getCheck() == -turn && _pArr[LR_Row][LR_Col].getCheck() != -turn)
		{
			_winPos = new Point[5]{ {UL_Row + 1 ,UL_Col + 1},{UL_Row + 2,UL_Col + 2},{UL_Row + 3,UL_Col + 3},{UL_Row + 4,UL_Col + 4},{UL_Row + 5,UL_Col + 5} };
			return true;
		}
		if (_pArr[UL_Row][UL_Col].getCheck() == _pArr[LR_Row][LR_Col].getCheck() && _pArr[LR_Row][LR_Col].getCheck() != -turn)
		{
			_winPos = new Point[5]{ {UL_Row + 1 ,UL_Col + 1},{UL_Row + 2,UL_Col + 2},{UL_Row + 3,UL_Col + 3},{UL_Row + 4,UL_Col + 4},{UL_Row + 5,UL_Col + 5} };
			return true;
		}
	}
	return false;
}

bool Board::checkDiag2(int i, int j, int turn)
{
	int LL_Row = 0, LL_Col = 0, UR_Row = 0, UR_Col = 0;
	// kiểm tra đường chéo sắc
	int row = i, col = j, count = 0;
	while (col >= 0 && row <= _size - 1 && _pArr[i][j].getCheck() == _pArr[row][col].getCheck() && _pArr[row][col].getCheck() == turn)
	{
		if ((col == 0 && row == _size - 1) || (col == 0) || (row == _size - 1))
		{
			count++;
			LL_Col = col;
			LL_Row = row;
			break;
		}
		else
		{
			count++;
			row++;
			col--;
			LL_Col = col;
			LL_Row = row;
		}
	}
	row = i; col = j, count--;
	while (row >= 0 && col <= _size - 1 && _pArr[i][j].getCheck() == _pArr[row][col].getCheck() && _pArr[row][col].getCheck() == turn)
	{
		if ((row == 0 && col == _size - 1) || (col == _size - 1) || (row == 0))
		{
			count++;
			UR_Row = row;
			UR_Col = col;
			break;
		}
		else
		{
			count++;
			row--;
			col++;
			UR_Row = row;
			UR_Col = col;
		}
	}
	if (count > 4)
	{
		if (LL_Col == 0 && _pArr[LL_Row][LL_Col].getCheck() == turn)
		{
			_winPos = new Point[5]{ {LL_Row,LL_Col},{LL_Row - 1 ,LL_Col + 1},{LL_Row - 2,LL_Col + 2},{LL_Row - 3,LL_Col + 3},{LL_Row - 4,LL_Col + 4} };
			return true;
		}
		else if (UR_Col == _size - 1 && _pArr[UR_Row][UR_Col].getCheck() == turn)
		{
			_winPos = new Point[5]{ {UR_Row,UR_Col},{UR_Row + 1 ,UR_Col - 1},{UR_Row + 2,UR_Col - 2},{UR_Row + 3,UR_Col - 3},{UR_Row + 4,UR_Col - 4} };
			return true;
		}
		else if (LL_Row == _size - 1 && _pArr[LL_Row][LL_Col].getCheck() == turn)
		{
			_winPos = new Point[5]{ {LL_Row,LL_Col},{LL_Row - 1 ,LL_Col + 1},{LL_Row - 2,LL_Col + 2},{LL_Row - 3,LL_Col + 3},{LL_Row - 4,LL_Col + 4} };
			return true;
		}
		else if (UR_Row == 0 && _pArr[UR_Row][UR_Col].getCheck() == turn)
		{
			_winPos = new Point[5]{ {UR_Row,UR_Col},{UR_Row + 1 ,UR_Col - 1},{UR_Row + 2,UR_Col - 2},{UR_Row + 3,UR_Col - 3},{UR_Row + 4,UR_Col - 4} };
			return true;
		}
		else if (_pArr[LL_Row][LL_Col].getCheck() == -turn && _pArr[UR_Row][UR_Col].getCheck() != -turn)
		{
			_winPos = new Point[5]{ {LL_Row - 1 ,LL_Col + 1},{LL_Row - 2,LL_Col + 2},{LL_Row - 3,LL_Col + 3},{LL_Row - 4,LL_Col + 4},{LL_Row - 5,LL_Col + 5} };
			return true;
		}
		else if (_pArr[UR_Row][UR_Col].getCheck() == -turn && _pArr[LL_Row][LL_Col].getCheck() != -turn)
		{
			_winPos = new Point[5]{ {UR_Row + 1 ,UR_Col - 1},{UR_Row + 2,UR_Col - 2},{UR_Row + 3,UR_Col - 3},{UR_Row + 4,UR_Col - 4},{UR_Row + 5,UR_Col - 5} };
			return true;
		}
		else if (_pArr[UR_Row][UR_Col].getCheck() == _pArr[LL_Row][LL_Col].getCheck() && _pArr[LL_Row][LL_Col].getCheck() != -turn)
		{
			_winPos = new Point[5]{ {UR_Row + 1 ,UR_Col - 1},{UR_Row + 2,UR_Col - 2},{UR_Row + 3,UR_Col - 3},{UR_Row + 4,UR_Col - 4},{UR_Row + 5,UR_Col - 5} };
			return true;
		}

	}
	return false;
}

Point Board::PVC()
{
	int i, j;
	do
	{
		i = getRandomInt(0, 13), j = getRandomInt(0, 13);
	} while (_pArr[i][j].getCheck() != 0);
	return Point(getXAt(i, j), getYAt(i, j));
}

void Board::loadBoard(ifstream& inFile)
{
	if (_size == 0)
		return;
	int check = 0;
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			inFile >> check;
			_pArr[i][j].setX(4 * j + _left + 3);
			_pArr[i][j].setY(2 * i + _top + 1);
			_pArr[i][j].setCheck(check);
			if (check == 1)
			{
				_countX++;
			}
			else if (check == -1)
			{
				_countO++;
			}
		}
	}
}

void Board::saveBoard(ofstream& outFile)
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			outFile << setw(3) << _pArr[i][j].getCheck();
		}
		outFile << endl;
	}
}

Point* Board::getWinPos()
{
	Point* b = new Point[5];
	for (int i = 0; i < 5; i++)
	{
		int x = _winPos[i].getX(), y = _winPos[i].getY();
		b[i].setX(getXAt(x, y)), b[i].setY(getYAt(x, y));
	}
	return b;
}