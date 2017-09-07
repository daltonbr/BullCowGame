#pragma once
#include "FBullCowGame.h"
#include <iostream>


FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "plan";
	
	//std::cout << "Reseting game\n";
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
}


bool FBullCowGame::IsGameWon() const
{
	return false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// not an isogram
	if (false)
	{
		return EGuessStatus::Not_Isogram;
	} 
	else if (false) // not all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	} 
	else if (Guess.length() != GetHiddenWordLength()) // length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}

	// otherwise
		// OK
		return EGuessStatus::OK; // TODO make actual error
}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	/*if (!CheckGuessValidity(Guess))
	{
		std::cout << "Guess Invalid\n";
	}*/
	
	// increment the turn number
	MyCurrentTry++;

	// setup a return variable
	FBullCowCount BullCowCount;

	// loop through all letters in the guess
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 HiddenChar = 0; HiddenChar < HiddenWordLength; HiddenChar++)
	{
		// compare letters against the hidden word
		for (int32 GuessChar = 0; GuessChar < HiddenWordLength; GuessChar++)
		{
			// if they match then
			if (Guess[GuessChar] == MyHiddenWord[HiddenChar])
			{
				if (HiddenChar == GuessChar)
				{
					// increment bulls if they're in the same place
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	return BullCowCount;
}


void FBullCowGame::IncrementTries()
{
	MyCurrentTry++;
}

