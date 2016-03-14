#include <iostream> 
#include <Windows.h> 
#include <conio.h> 
#include <ctime> 
#define CLOCKS_PER_SEC 1

using namespace std;

const int BLANK = 000;
const int WALL = 35;
const int PILL = 111;
const int RIGHT = 074;
const int LEFT = 076;
const int UP = 118;
const int DOWN = 94;
const int GHOST1 = 87;

const int MAXROWS = 10;
const int MAXCOLUMNS = 29;
char keyboardValue = 127;
int PILLSTAKEN = 0;
int pacI = 1, pacJ = 1;
int ghostOneI = 7, ghostOneJ = 15;
int i = 0, j = 0;

char levelMatrix[MAXROWS][MAXCOLUMNS] =
{
	{ 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35 },

	{ 35, 000, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 35 },

	{ 35, 111, 35, 35, 35, 35, 111, 35, 35, 35, 35, 111, 35, 35, 35, 35, 35, 111, 35, 35, 35, 35, 111, 35, 35, 35, 111, 111, 35 },

	{ 35, 111, 111, 111, 111, 111, 111, 111, 111, 35, 111, 111, 111, 111, 111, 111, 111, 111, 111, 35, 111, 111, 111, 111, 111, 111, 111, 111, 35 },

	{ 35, 111, 111, 111, 111, 35, 35, 111, 111, 111, 111, 111, 111, 35, 35, 35, 111, 111, 111, 111, 111, 111, 35, 35, 111, 111, 111, 111, 35 },

	{ 35, 111, 111, 111, 111, 35, 35, 111, 111, 111, 111, 111, 111, 35, 35, 35, 111, 111, 111, 111, 111, 111, 35, 35, 111, 111, 111, 111, 35 },

	{ 35, 111, 111, 111, 111, 111, 111, 111, 111, 35, 111, 111, 111, 111, 111, 111, 111, 111, 111, 35, 111, 111, 111, 111, 111, 111, 111, 111, 35 },

	{ 35, 111, 111, 35, 35, 35, 111, 35, 35, 35, 35, 111, 35, 35, 35, 35, 35, 111, 35, 35, 35, 35, 111, 35, 35, 35, 111, 111, 35 },

	{ 35, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 35 },

	{ 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35 }

};

char ghostCurrent = levelMatrix[ghostOneI][ghostOneJ];


void getKeyPress();
bool blockValid(int block);
void Ghost();
void GoToXY(int column, int line);

bool ghostMoveUp();
bool ghostMoveDown();
bool ghostMoveLeft();
bool ghostMoveRight();

int pillCount = 157;
int lives = 3;

clock_t startTime = 0, endTime = 0;

bool pill = false;

int main()

{

	HANDLE  hConsole;

	int k = 14;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
	cout << "       ###############              " << endl;
	cout << "      ##################        " << endl;
	cout << "    #######################         " << endl;
	cout << "  ##############   ###########                  " << endl;
	cout << "##############################                  " << endl;
	cout << "#######################                 " << endl;
	cout << "####################            " << endl;
	cout << "################            " << endl;
	cout << "#############               " << endl;
	cout << "###########                 " << endl;
	cout << "#########                       " << endl;
	cout << "############            " << "PACMAN" << endl;
	cout << "##################          " << endl;
	cout << "#######################         " << endl;
	cout << "###########################                 " << endl;
	cout << "##############################                  " << endl;
	cout << "    #######################                 " << endl;
	cout << "      ####################              " << endl;
	cout << "        ################            " << endl;
	cout << endl;
	system("pause");
	char key = 0;
	system("mode 80, 50");
	int pills = 30;
	bool stopCounting = false;
	do
	{	
		
		GoToXY(0, 0);
		Ghost();
		getKeyPress();
		for (i = 0; i <= 9; i++)
		{
			for (j = 0; j <= 28; j++)
			{
				if (levelMatrix[i][j] == WALL)
				{
					k = 1;
					SetConsoleTextAttribute(hConsole, k);
				}
				else if (levelMatrix[i][j] == RIGHT || levelMatrix[i][j] == LEFT || levelMatrix[i][j] == UP || levelMatrix[i][j] == DOWN)
				{
					k = 14;
					SetConsoleTextAttribute(hConsole, k);
				}
				else if (levelMatrix[i][j] == GHOST1)
				{
					k = 4;
					SetConsoleTextAttribute(hConsole, k);
				}
				else if (levelMatrix[i][j] == BLANK)
				{
					k = 0;
					SetConsoleTextAttribute(hConsole, k);
				}
				else if (levelMatrix[i][j] == PILL)
				{
					k = 15;
					SetConsoleTextAttribute(hConsole, k);
				}

				cout << levelMatrix[i][j];
				if (j == 28)
					cout << endl;

				if (j == 28 && i == 9)
					stopCounting = true;
			}
		
		}
		Sleep(50);
		k = 15;
		PILLSTAKEN = 158 - pillCount;
		SetConsoleTextAttribute(hConsole, k);
		cout << "Zbyvajici zivoty " << lives << endl;
		cout << "Cas " << endTime/1000 << endl;
		endTime = clock();
		int elapsed = int((endTime - startTime) / CLOCKS_PER_SEC);
	} 
	while (lives > 0 || pillCount != 0);
	system("pause");
	return 0;
	
};




bool ghostMoveUp()

{
	char ghostNextUp = levelMatrix[ghostOneI - 1][ghostOneJ];
	if (ghostNextUp != WALL)
	{
		if (ghostNextUp == PILL || ghostNextUp == 117)
		{
			levelMatrix[ghostOneI - 1][ghostOneJ] = 87;
			levelMatrix[ghostOneI][ghostOneJ] = 111;
			ghostOneI--;

		}
		else
		{

			pill = false;

			levelMatrix[ghostOneI][ghostOneJ] = BLANK;
			levelMatrix[ghostOneI - 1][ghostOneJ] = 87;
			ghostOneI--;
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool ghostMoveDown()
{
	char ghostNextDown = levelMatrix[ghostOneI + 1][ghostOneJ];
	if (ghostNextDown != WALL)
	{
		if (ghostNextDown == PILL || ghostNextDown == 117)
		{
			levelMatrix[ghostOneI + 1][ghostOneJ] = 87;
			levelMatrix[ghostOneI][ghostOneJ] = ghostNextDown;
			ghostOneI++;
		}
		else
		{
			levelMatrix[ghostOneI][ghostOneJ] = 000;
			levelMatrix[ghostOneI + 1][ghostOneJ] = 87;
			ghostOneI++;
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool ghostMoveLeft()
{
	char ghostNextLeft = levelMatrix[ghostOneI][ghostOneJ - 1];
	if (ghostNextLeft != WALL)
	{
		if (ghostNextLeft == PILL || ghostNextLeft == 117)
		{
			levelMatrix[ghostOneI][ghostOneJ - 1] = 87;
			levelMatrix[ghostOneI][ghostOneJ] = ghostNextLeft;
			ghostOneJ--;
		}
		else
		{
			levelMatrix[ghostOneI][ghostOneJ] = 000;
			levelMatrix[ghostOneI][ghostOneJ - 1] = 87;
			ghostOneJ--;
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool ghostMoveRight()
{
	char ghostNextRight = levelMatrix[ghostOneI][ghostOneJ + 1];
	if (ghostNextRight != WALL)
	{
		if (ghostNextRight == PILL || ghostNextRight == 117)
		{
			levelMatrix[ghostOneI][ghostOneJ + 1] = 87;
			levelMatrix[ghostOneI][ghostOneJ] = ghostNextRight;
			ghostOneJ++;
		}
		else
		{
			levelMatrix[ghostOneI][ghostOneJ] = 000;
			levelMatrix[ghostOneI][ghostOneJ + 1] = 87;
			ghostOneJ++;
		}
		return true;
	}
	else
	{
		return false;
	}
}
void Ghost()

{	
	if (pacI < ghostOneI)
	{
		if (!ghostMoveUp())
		{
		}
	}

	else if (pacI > ghostOneI)
	{
		if (!ghostMoveDown())
		{
		}
	}
	if (pacJ < ghostOneJ)
	{
		if (!ghostMoveLeft())
		{
		}
	}
	else if (pacJ > ghostOneJ)
	{
		if (!ghostMoveRight())
		{
		}
	}

	if (pacJ == ghostOneJ && pacI == ghostOneI)
	{
		lives--;
		levelMatrix[pacI][pacJ] = BLANK;
		levelMatrix[ghostOneI][ghostOneJ] = BLANK;
		pacI = 1;
		pacJ = 1;
		ghostOneI = 7;
		ghostOneJ = 15;
		levelMatrix[1][1] = RIGHT;
		levelMatrix[7][15] = GHOST1;
	}
}
void getKeyPress()
{

	if (GetAsyncKeyState(VK_UP))
	{
		if (levelMatrix[pacI - 1][pacJ] != WALL)
		{

			levelMatrix[pacI][pacJ] = BLANK;
			levelMatrix[pacI - 1][pacJ] = UP;
			pacI--;
		}
	}
	else if (GetAsyncKeyState(VK_LEFT)) //left 
	{
		if (levelMatrix[pacI][pacJ - 1] != WALL)
		{
			levelMatrix[pacI][pacJ] = BLANK;
			levelMatrix[pacI][pacJ - 1] = LEFT;
			pacJ--;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT)) //right 
	{
		if (levelMatrix[pacI][pacJ + 1] != WALL)
		{
			levelMatrix[pacI][pacJ] = BLANK;
			levelMatrix[pacI][pacJ + 1] = RIGHT;
			pacJ++;
		}

	}
	else if (GetAsyncKeyState(VK_DOWN)) //down 
	{
		if (levelMatrix[pacI + 1][pacJ] != WALL)
		{
			levelMatrix[pacI][pacJ] = BLANK;
			levelMatrix[pacI + 1][pacJ] = DOWN;
			pacI++;
		}
	}
}
void GoToXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!SetConsoleCursorPosition(hConsole, coord))
	{
	}
}

