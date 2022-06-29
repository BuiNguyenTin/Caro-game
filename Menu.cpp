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
		{options[5], playPvC1},
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
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
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
	}
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
	for (int i = 1; i < height; i++)
	{
		Common::gotoXY(line3, top + i);
		cout << '|';
	}
	//Common::gotoXY(line3, line1);
	//putchar(197);
	//Common::gotoXY(line3, line2);
	//putchar(197);
	////=====================================================================//
	//Common::setConsoleColor(BRIGHT_WHITE, RED);
	//Common::gotoXY(left + 3, top + 2);
	//cout << "Moves:";
	//Common::gotoXY(left + 20, top + 1);
	//putchar(249); cout << "Up:    W, up arrow";
	//Common::gotoXY(left + 52, top + 1);
	//putchar(249); cout << "Down:  S, down arrow";
	//Common::gotoXY(left + 20, top + 3);
	//putchar(249); cout << "Left:  A, left arrow";
	//Common::gotoXY(left + 52, top + 3);
	//putchar(249); cout << "Right: D, right arrow";
	////=====================================================================//
	//Common::gotoXY(left + 3, top + 10);
	//cout << "Rules:";
	//Common::gotoXY(left + 13, top + 5);
	//int left1 = left + 13;
	//putchar(249); cout << "The player representing the 'X' symbol gets to take the first turn";
	//Common::gotoXY(left1, top + 6);
	//cout << " followed by the player representing the 'O' symbol.";
	//Common::gotoXY(left1, top + 8);
	//putchar(249); cout << "Players take turns placing their symbol on an open intersection";
	//Common::gotoXY(left1, top + 9);
	//cout << " on the board.";
	//Common::gotoXY(left1, top + 11);
	//putchar(249); cout << "The player that manages to create exactly five in a row first,";
	//Common::gotoXY(left1, top + 12);
	//cout << " without being blocked by another color or symbol at either end";
	//Common::gotoXY(left1, top + 13);
	//cout << " wins the round.";
	//Common::gotoXY(left1, top + 15);
	//putchar(249); cout << "The row can be horizontal, vertical, or diagonal as long as";
	//Common::gotoXY(left1, top + 16);
	//cout << " it is unbroken.";
	////=====================================================================//
	//Common::gotoXY(left + 3, top + 20);
	//cout << "About:";
	//Common::gotoXY(left + 28, top + 18);
	//cout << "Teacher:            Truong Toan Thinh";
	//Common::gotoXY(left + 28, top + 19);
	//cout << "Teaching assistant: Nguyen Hai Dang";
	//Common::gotoXY(left + 13, top + 21);
	//cout << "+ Nguyen Xuan Phat (19127504)       + Pham Tien Quan     (19127526)";
	//Common::gotoXY(left + 13, top + 22);
	//cout << "+ Dang Tu Thieu    (19127557)       + Luong Truong Thinh (19127559)";

	Common::setConsoleColor(BRIGHT_WHITE, RED);
	Common::gotoXY(47, 28);
	cout << '~';
	Common::gotoXY(52, 28);
	cout << "Back";
	Common::gotoXY(60, 28);
	cout << '~';
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

void Menu::playPvC1()
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
	int file = 8;
	changeFile(3, fileName, file);
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
		else if (key > 1 && key < 6)
		{
			changeFile(key, fileName, file);
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

void Menu::changeFile(int key, vector<string>& fileName, int& file)
{
	if (key == 3 || key == 4)
	{
		if (key == 3 && file > 7)
		{
			Common::playSound(2);
			file = (file / 8 - 1) * 8;
		}
		else if (key == 4 && file / 8 < fileName.size() / 8)
		{
			file = (file / 8 + 1) * 8;
		}
		else
		{
			Common::playSound(4);
			return;
		}
		Common::playSound(2);
		Common::setConsoleColor(BRIGHT_WHITE, BLACK);
		int i = 0;
		for (i = file + 1; i < file + 8; i++)
		{
			Common::gotoXY(0, 9 + i % 8 * 2);
			for (int j = 0; j < 107; j++)
				cout << ' ';
			if (i < fileName.size())
			{
				Common::gotoXY(54 - fileName[i].find('-'), 9 + i % 8 * 2);
				cout << fileName[i];
			}
		}
		Common::gotoXY(15, 16);
		(file - 8 < 0) ? putchar(32) : putchar(60);
		Common::gotoXY(93, 16);
		(file + 8 >= fileName.size()) ? putchar(32) : putchar(62);
		Common::setConsoleColor(BRIGHT_WHITE, RED);
		Common::gotoXY(0, 9);
		for (int j = 0; j < 107; j++)
			putchar(32);
		Common::gotoXY(54 - fileName[file].find('-'), 9);
		cout << fileName[file];
	}
	else if (key == 2 || key == 5)
	{
		if (key == 2 && file % 8 > 0)
		{
			Common::setConsoleColor(BRIGHT_WHITE, BLACK);
			Common::gotoXY(54 - fileName[file].find('-'), 9 + file % 8 * 2);
			cout << fileName[file];
			file--;
		}
		else if (key == 5 && file % 8 < 7 && file < fileName.size() - 1)
		{
			Common::setConsoleColor(BRIGHT_WHITE, BLACK);
			Common::gotoXY(54 - fileName[file].find('-'), 9 + file % 8 * 2);
			cout << fileName[file];
			file++;
		}
		else
		{
			Common::playSound(4);
			return;
		}
		Common::setConsoleColor(BRIGHT_WHITE, RED);
		Common::gotoXY(54 - fileName[file].find('-'), 9 + file % 8 * 2);
		cout << fileName[file];
	}
}