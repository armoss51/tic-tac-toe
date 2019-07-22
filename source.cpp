#include <iostream>
#include<list>
#include <cstdlib>
#include<string>
#include <ctime>
using namespace std;


/*
 Program name  : MossAaronFinalProject.cpp
 Author        : Aaron Moss
 Date          : 7/15/2019
 Description   : Tic Tac Toe
*/


typedef struct 
{
	int *row;
}Win;


class Player 
{
private:
	string name;
	int score;
public:
	Player() :Player{ "" } {}
	Player(string n) :score{ 0 }, name{ n }{}

	void won() 
	{
		score++;
	}

	int getScore() 
	{ 
		return this->score; 
	}

	string getName() 
	{ 
		return this->name; 
	}
};

class Game 
{
private:
	char board[9];
	int emptyIndex[9];
	int gameOn;
	int emptyCount;
	Win win[8];

	void displayBoard() 
	{
		cout << endl;
		cout << "   |   |   " << endl;
		cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
		cout << "   |   |   " << endl;
		cout << "-----------" << endl;
		cout << "   |   |   " << endl;
		cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
		cout << "   |   |   " << endl;
		cout << "-----------" << endl;
		cout << "   |   |   " << endl;
		cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;
		cout << "   |   |   " << endl;
		cout << endl;
	}

	void playerInput(Player &player) 
	{
		int pos;
		cout << endl;
		cout << player.getName() << " Turn: ";
		cout << "Player choose: " << endl;
		cin >> pos;
		pos -= 1;
		if (emptyIndex[pos] == 1) 
		{
			cout << "--That spot is already taken--" << endl;
			playerInput(player);
		}
		else 
		{
			emptyIndex[pos] = 1;
			emptyCount -= 1;
			player.getName().compare("Player 1") == 0 ? board[pos] = 'X' : board[pos] = 'O';
		}

	}

	void computerInput() 
	{
		int pos;
		pos = rand() % 10;
		if (emptyIndex[pos] == 1) 
		{
			if (emptyCount < 0)
				return;
			computerInput();
		}
		else 
		{
			cout << "Computer choose: " << pos + 1 << endl;
			emptyIndex[pos] = 1;
			emptyCount -= 1;
			board[pos] = 'O';
		}

	}

	void play(Player &p1, Player &pc) 
	{
		char rematch = '\0';
		int hand = 0;
		gameOn = 1;
		displayBoard();
		while ((emptyCount > 0) && (gameOn != 0)) 
		{

			hand == 1 ? computerInput() : playerInput(p1);
			hand = !hand;
			displayBoard();
			checkWin(p1, pc);
		}
		if (emptyCount <= 0) 
		{
			cout << "It's a tie." << endl;
		}
		cout << endl;
		cout << "Play again? Y/N: ";
		cin >> rematch;
		if ((rematch == 'Y') || (rematch == 'y')) 
		{
			start();
			play(p1, pc);
		}

	}

	void checkWin(Player &p1, Player &pc) 
	{
		int i, j;
		bool flag = false;
		char first_symbol;
		for (i = 0; i < 8; i++) 
		{
			first_symbol = board[win[i].row[0]];

			if ((first_symbol != 'X') && (first_symbol != 'O')) 
			{
				flag = false;
				continue;
			}
			flag = true;
			for (j = 0; j < 3; j++) 
			{
				if (first_symbol != board[win[i].row[j]]) 
				{
					flag = false;
					break;
				}
			}
			if (flag) 
			{
				gameOn = 0;
				if (first_symbol == 'X') 
				{
					cout << "Player 1 WON" << endl;
					p1.won();
				}
				else 
				{
					cout << "Computer WON" << endl;	
					pc.won();
				}
				displayScore(p1, pc);
				break;
			}
		}
	}

	void displayScore(Player &p1, Player &pc) 
	{
		cout << endl;
		cout << "SCORE: ";
		cout << " Player 1: " << p1.getScore() << " Computer: " << pc.getScore() << endl;
	}

public:
	Game() : emptyCount{ 0 }, gameOn{ 1 }
	{
		start();
		win[0].row = new int[3]{ 0,1,2 };
		win[1].row = new int[3]{ 3,4,5 };
		win[2].row = new int[3]{ 6,7,8 };
		win[3].row = new int[3]{ 0,3,6 };
		win[4].row = new int[3]{ 1,4,7 };
		win[5].row = new int[3]{ 2,5,8 };
		win[6].row = new int[3]{ 0,4,8 };
		win[7].row = new int[3]{ 2,4,6 };
	}

	void start() 
	{
		gameOn = 1;

		emptyCount = 0;
		srand(time(0));
		for (size_t i = 0; i < 10; i++) 
		{
			emptyIndex[i] = 0;
			board[i] = (i + 1) + '0';
			emptyCount++;
		}
		emptyCount--;
	}

	void newGame() 
	{
		Player p("Player 1");
		Player c("Computer");
		cout << endl;
		cout << "Player 1: X || Computer: O" << endl;
		cout << endl;
		cout << endl;
		play(p, c);

	}

};


int main()
{
	int userInput;

	while (1) 
	{
		cout << "----------TIC TAC TOE----------" << endl;
		cout << "Select an option" << endl;
		cout << "1. New game" << endl;
		cout << "2. Quit " << endl;
		cout << endl;
		cin >> userInput;
		switch (userInput) 
		{
			case 1: 
			{
				Game *game = new Game;
				game->start();
				game->newGame();
			}
				break;
			case 2:
				return 0;
			default:
				cout << endl;
				cout << "Please enter a valid option." << endl;
				cout << endl;
		}

	}
	getchar();
	getchar();
	return 0;
}
