#include "Menu.h"

using namespace std;

int Menu::current_option;
const string Menu::options[7] = { "Play", "Load", "Help", "Exit", " PvP ", "PvC", "Back" };

void Menu::mainScreen()
{
	unordered_map<string, void(*)()> function_map = {
		{options[0], playMenu},
		{options[1], loadScreen},
		{options[2], helpScreen},
		{options[3], exitScreen},
		{options[4], playPvP},
		{options[5], playPvC},
		{options[6], goBack} };
	Common::playSound(8);
	printAnimation();
	bool loadMenu = 1;
	while (true)
	{
		if (loadMenu)
			mainMenu();
		switch (Common::getConsoleInput())
		{
		case 2:
			changeOption(0, 1);
			loadMenu = 0;
			break;
		case 5:
			changeOption(1, 1);
			loadMenu = 0;
			break;
		case 6:
			if (current_option == 0)
				loadMenu = 0;
			else
				loadMenu = 1;
			function_map[options[current_option]]();
			break;
		default:
			Common::playSound(4);
			loadMenu = 0;
		}
	}

	Common::clearConsole();
}

void Menu::printLogo()
{
	ifstream fi;
		fi.open("Logo.txt");
		if (!fi)
		{
			cout << "Cannot open file" << endl;
		}
		else
		{
			int c = 4;
			Common::gotoXY(18, c);
			string temp;
			while (!fi.eof())
			{
				c++;
				Common::gotoXY(18, c);
				getline(fi, temp, '\n');
				cout << temp << endl;
			}
			fi.close();
		}
}

void Menu::printAnimation()
{
	/*Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::clearConsole();

	int color[] = { BLUE, GREEN, PURPLE, RED };

	ifstream fi;

	for (int i = 0; i < 4; i++)
	{
		fi.open("logo.txt");
		if (!fi)
		{
			cout << "Cannot open file" << endl;
		}
		else
		{
			int c = 10;
			Common::gotoXY(18, c);
			string temp;
			Common::setConsoleColor(BRIGHT_WHITE, color[i]);
			while (!fi.eof())
			{
				c++;
				Common::gotoXY(18, c);
				getline(fi, temp, '\n');
				cout << temp << endl;
				Sleep(300);
			}
			fi.close();
			Sleep(500);
			Common::setConsoleColor(BRIGHT_WHITE, BLACK);
		}
	}*/
}

void Menu::changeOption(bool direction, bool flag)
{
	int top = 21;
	if ((direction == 0 && (current_option == 4 || current_option == 0))
	|| (direction == 1 && (current_option == 3 || current_option == 6)))
	{
		Common::playSound(4);
		return;
	}
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(54 - (int)options[current_option].length() / 2, top + current_option % 4 * 2);
	cout << options[current_option];
	if (flag)
	{
		Common::gotoXY(44, top + current_option % 4 * 2);
		cout << ' ';
		Common::gotoXY(64, top + current_option % 4 * 2);
		cout << ' ';
	}
	(direction == 1) ? current_option++ : current_option--;
	if (flag)
	{
		Common::playSound(2);
		Common::setConsoleColor(BRIGHT_WHITE, RED);
		Common::gotoXY(44, top + current_option % 4 * 2);
		cout << '~';
		Common::gotoXY(54 - (int)options[current_option].length() / 2, top + current_option % 4 * 2);
		cout << options[current_option];
		Common::gotoXY(64, top + current_option % 4 * 2);
		cout << '~';
	}
}

void Menu::mainMenu()
{
	Common::setConsoleColor(BRIGHT_WHITE, RED);
	Common::clearConsole();
	printLogo();
	current_option = 3;
	changeOption(0, 0);
	changeOption(0, 0);
	changeOption(0, 1);
}

void Menu::playMenu()
{
	system("cls");
	printLogo();
	current_option = 7;
	changeOption(0, 0);
	changeOption(0, 0);
	changeOption(0, 1);
}

void Menu::playPvP()
{
	Game g;
	g.setUpGame(0);
	g.startGame();
}

void Menu::helpScreen()
{
	Common::showCursor(false);
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::clearConsole();

	int left = 13, top = 2, width = 81, height = 23;
	int line1 = 6, line2 = 19, line3 = 24;
	printRectangle(left, top, width, height);
	Common::gotoXY(left + 1, line1);
	for (int i = 0; i < width; i++)
	{
		cout << '-';
	}
	Common::gotoXY(left + 1, line2);
	for (int i = 0; i < width; i++)
	{
		cout << '-';
	}
	
	Common::setConsoleColor(BRIGHT_WHITE, BLUE);
	Common::gotoXY(left + 10, top + 1);
	cout << "Intrucstion: + Up:    W, up arrow";
	Common::gotoXY(left + 50, top + 1);
	cout << "+ Down:  S, down arrow";
	Common::gotoXY(left + 10, top + 3);
	cout << "             + Left:  A, left arrow";
	Common::gotoXY(left + 50, top + 3);
	cout << "+ Right: D, right arrow";

	int left1 = left + 5;
	Common::gotoXY(left1, top + 6);
	cout << "The player 1 is represented by 'X' symbol and it is the first turn.";
	Common::gotoXY(left1, top + 7);
	cout << "The player 2 is represented by 'O symbol and it is the second turn.";
	Common::gotoXY(left1, top + 9);
	cout << "Players: + Press 'Enter' to tick into the rectangle on the board.";
	Common::gotoXY(left1, top + 10);
	cout << "         + Press 'ESC' to exit the game.";
	Common::gotoXY(left1, top + 11);
	cout << "         + Press 'H' to open the Help screen.";
	Common::gotoXY(left1, top + 13);
	cout << "The player can't win if the row is blocked at both end by the other symbols.";
	Common::gotoXY(left1, top + 15); 
	cout << "The row can be horizontal, vertical, or diagonal.";
	
	Common::gotoXY(left + 18, top + 18);
	cout << "Teacher: + Truong Toan Thinh";
	Common::gotoXY(left + 18, top + 19);
	cout << "Student: + Tran Nguyen Thanh Binh - 21127584";
	Common::gotoXY(left + 18, top + 21);
	cout << "         + Nguyen Thi Cam Nhung   - 21127386";
	Common::gotoXY(left + 18, top + 22);
	cout << "         + Bui Nguyen Tin         - 21127702";

	Common::setConsoleColor(BRIGHT_WHITE, RED);
	Common::gotoXY(44, 28);
	cout << "~     Back     ~";

	while (Common::getConsoleInput() != 6)
	{
		Common::playSound(4);
	}
}

void Menu::printRectangle(int left, int top, int width, int height)
{
	Common::gotoXY(left, top);
	cout << '+';
	for (int i = 0; i < width; i++)
		cout << '-';
	cout << '+';

	int i = 0;
	for (; i < height; i++)
	{
		Common::gotoXY(left, top + i + 1);
		cout << '|';
		Common::gotoXY(left + width + 1, top + i + 1);
		cout << '|';
	}

	Common::gotoXY(left, top + i);
	cout << '+';
	for (i = 0; i < width; i++)
		cout << '-';
	cout << '+';
}

void Menu::exitScreen()
{
	Common::showCursor(false);
	Common::clearConsole();
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	printLogo();
	Common::gotoXY(40, 16);
	cout << "Do you want to exit Caro game?";
	string str[2] = { "Yes", "No" };
	int left[] = { 37,42,49,60,65,71 }, color[] = { BLACK, RED }, top = 20;
	bool choice = 0;
	bool loop = 1;
	auto print1 = [&]()
	{
		int i = 0;
		while (i < 2)
		{
			Common::playSound(2);
			Common::setConsoleColor(BRIGHT_WHITE, color[i]);
			Common::gotoXY(left[choice * 3], top);
			{
				if (i == 1)
				{
					cout << '~';
				}
				else cout << ' ';
			}
			Common::gotoXY(left[choice * 3 + 1], top);    
				cout << str[choice];
			Common::gotoXY(left[choice * 3 + 2], top);    
			{
				if (i == 1)
				{
					cout << '~';
				}
				else cout << ' ';
			}
			if (!i++)
				choice = !choice;
		}
	};
	print1();
	while (loop)
	{
		int key = Common::getConsoleInput();
		if ((key == 3 && choice == 1) || (key == 4 && choice == 0))
		{
			print1();
		}
		else if (key == 6)
		{
			if (!choice)
			{
				Common::setConsoleColor(BLACK, BRIGHT_WHITE);
				Common::clearConsole();
				Common::gotoXY(40, 16);
				cout << "Press any key to close Caro game";
				Sleep(200);
				Common::setConsoleColor(BLACK, BLACK);
				exit(0);
			}
			return;
		}
		else
		{
			Common::playSound(4);
		}
	}
}

void Menu::playPvC()
{
	Game g;
	g.setUpGame(1);
	g.startGame();
}

void Menu::loadScreen()
{
	Common::clearConsole();
	vector<string> fileName;

	ifstream fi;
	fi.open("ListLoad.txt");
	if (!fi)
	{
		cout << "Cannot open file List Load" << endl;
	}
	else
	{
		string temp;
		while (!fi.eof())
		{
			getline(fi, temp);
			fileName.push_back(temp);
		}
	}
	fi.close();
	if (!fileName.size())
	{
		Common::gotoXY(42, 15);
		cout << "No game files were found!";
		Sleep(3000);
		return;
	}
	int file = 0;
	changeFile(fileName, file);

	int j = 20;
	int sz;

	if (fileName.size() < 8)
	{
		sz = fileName.size();
	}
	else
	{
		sz = 8;
	}

	bool chosen = 0;
	while (!chosen)
	{
		int key = Common::getConsoleInput();
		if (key == 6)
		{
			Game g;
			g.setUpGame(3, fileName[file]);
			g.startGame();
			chosen = 1;
		}
		else if (key == 2)
		{
			if (file == 0)
			{
				file = sz - 1;
				changeFile(fileName, file);
				Common::playSound(2);
			}
			else
			{
				file--;
				changeFile(fileName, file);
				Common::playSound(2);
			}
		}
		else if (key == 5)
		{
			if (file == sz - 1)
			{
				file = 0;
				changeFile(fileName, file);
				Common::playSound(2);
			}
			else
			{
				file++;
				changeFile(fileName, file);
				Common::playSound(2);
			}
		}
		else if (key == 1)
		{
			chosen = 1;
		}
		else
		{
			Common::playSound(4);
		}
	}
}

void Menu::changeFile(vector<string>& fileName, int& file)
{
	system("cls");
	printLogo();
	
	int j = 20;
	int sz;

	if (fileName.size() < 8)
	{
		sz = fileName.size();
	}
	else
	{
		sz = 8;
	}
	
	for (int i = 0; i < sz; i++)
	{
		Common::gotoXY(40, j);
		j++;
		if (i == file)
		{
			Common::setConsoleColor(BRIGHT_WHITE, RED);
			cout << fileName[i];
			Common::setConsoleColor(BRIGHT_WHITE, BLACK);
		}
		else
		{
			cout << fileName[i];
		}
	}
}