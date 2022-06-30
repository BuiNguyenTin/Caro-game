#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "Point.h"
#include "Common.h"

using namespace std;

class Board
{
private:
	int _size;              //Kích cỡ bàn cờ
	int _left, _top;        //Tọa độ bắt đầu bàn cờ
	int _countX, _countO;   //Đếm số quân cờ mỗi người chơi
	Point* _winPos;        //Vị trí 5 quân cờ thắng
	Point** _pArr;         //Mảng vị trí ô cờ
public:
	Board(int, int, int);			//Phương thức dựng
	~Board();						//Phương thức hủy
	int getSize();					//Lấy kích cỡ
	int getLeft();					//Lấy tọa độ trái bắt đầu bàn cờ
	int getTop();					//Lấy tọa độ trên bắt đầu bàn cờ
	int getCountX();				//Lấy số quân cờ người chơi 1
	int getCountO();				//Lấy số quân cờ người chơi 2
	int getXAt(int, int);			//Lấy tọa độ x tại ô
	int getYAt(int, int);			//Lấy tọa độ y tại ô
	void resetData();				//Cài lại bàn cờ
	void drawBoard();				//Vẽ bảng cờ
	int checkBoard(int, int, bool); //Kiểm tra vị trí trên bàn cờ
	int testBoard(int, int);        //Kiểm tra thắng thua
	int getCheckAtXY(int, int);     //Lấy quân cờ ở ô
	bool checkRow(int, int, int);   //Kiểm tra thắng ỏ dòng
	bool checkCol(int, int, int);	//Kiểm tra thắng ở cột
	bool checkDiag1(int, int, int); //Kiểm tra thắng ở chéo huyền
	bool checkDiag2(int, int, int); //Kiểm tra thắng ở chéo sắc
	Point PVC();					//Tìm vị trí chế độ máy
	void loadBoard(ifstream&);		//Load vị trí X,O
	void saveBoard(ofstream&);		//Lưu vị trí X,O
	Point* getWinPos();				//Lấy vị trí thắng
};