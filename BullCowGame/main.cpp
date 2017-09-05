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
FText GetGuess();
bool AskToPlayAgain();

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
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << MaxTries << std::endl;

	// loop for the number of turns asking for guesses
	// TODO change from FOR to WHILE loop once we are validating tries
	constexpr int32 NUMBER_OF_TURNS = 3;
	for (int32 i = 0; i < MaxTries; i++)
	{
		FText Guess = GetGuess(); // TODO make loop checking valid

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << std::endl;
	}

	// TODO summarize summary


}

// get a guess from the player
FText GetGuess()
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	FText Guess = "";
	std::cout << "Try " << CurrentTry << ". Enter your guess: ";
	std::getline(std::cin, Guess);
	BCGame.IncrementTries();
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? [Y/N] ";
	FText Response = "";
	std::getline(std::cin, Response);
	
	return (Response[0] == 'y' || Response[0] == 'Y');	
}
