#include "stdafx.h"

using namespace std;


int main()
{
	constexpr int WORLD_LENGTH = 9;

	// introduce the game
	cout << "Welcome to Bulls and Cows, a fun word game.\n";
	cout << "Can you guess the "<< WORLD_LENGTH << " letter isogram I'm thinking of?\n";
	cout << endl;

	// get a guess from the player
	string Guess = "";
	cout << "Enter your guess: ";
	getline(cin, Guess);
	
	// repeat the guess back to them
	cout << "Your guess was: " << Guess << endl;
	cout << endl;
	
    return 0;
}

