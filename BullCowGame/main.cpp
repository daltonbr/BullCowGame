/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;


void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;	// our game instance

// the entry point for our application
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
	
    return 0;
}

// introduce the game
void PrintIntro()
{
	std::cout << "\n  ___________________________    __________________ \n";
	std::cout << "\n |Welcome to Bulls and Cows! |  | A fun word game! |\n";
	std::cout << "\n |_____________\\ ____________|  |/_________________|\n";
	std::cout << "\n                \\               /               \n";
	std::cout << "      _________}____{        |____|__________" << std::endl;
	std::cout << "     /|        |O  o|        | oO | o  O o O|\\"<< std::endl;
	std::cout << "    *|\\_______/(    )        (    )__O__o_o_| *" << std::endl;
	std::cout << "     |        | (oo)          (oo)   |      |" << std::endl;
	std::cout << std::endl;

	std::cout << "Can you guess the \"" << BCGame.GetHiddenWordLength();
	std::cout << "\" letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game
	// is NOT and there are still tries remaining
		
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();

	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "[Try " << CurrentTry << "/" << BCGame.GetMaxTries();
		std::cout << "]. Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a \"" << BCGame.GetHiddenWordLength() << "\" length word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter only lowercases.\n\n";
			break;
		case EGuessStatus::Not_Alpha:
			std::cout << "Please enter only letters [a-z].\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Your entry was NOT an isogram. It must be a word with NO repeating letters.\n\n";
			break;
		default:
			// assume that there is no error
			break;
		}
	} while (Status != EGuessStatus::OK);

	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? [y/n] ";
	FText Response = "";
	std::getline(std::cin, Response);
	
	return (Response[0] == 'y' || Response[0] == 'Y');	
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE! YOU WIN!\n";
	}
	else
	{
		std::cout << "BETTER LUCK NEXT TIME!\n";
	}
}