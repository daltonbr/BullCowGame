#pragma once
#include "FBullCowGame.h"
#include <map>
#define Tmap std::map

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 3;
	const FString HIDDEN_WORD = "plan";
	
	//std::cout << "Reseting game\n";
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bIsGameWon = false;
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // not an isogram
	{
		return EGuessStatus::Not_Isogram;
	} 
	else if (false) // not all lowercase
	{
		return EGuessStatus::Not_Lowercase; // TODO write function
	} 
	else if (Guess.length() != GetHiddenWordLength()) // length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;	
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 HiddenChar = 0; HiddenChar < WordLength; HiddenChar++)
	{
		// compare letters against the guess
		for (int32 GuessChar = 0; GuessChar < WordLength; GuessChar++)
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
	bIsGameWon = BullCowCount.Bulls == WordLength;
	return BullCowCount;
}

// TODO implement IsIsogram
bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	Tmap<char, bool> LetterSeen;

	// loop through all the word letters
	for (auto Letter : Word)
	{
		Letter = towlower(Letter); // handle mixed case
		
		// if the current letter is in the map,
		if (LetterSeen[Letter])
		{
			return false; // we do NOT have an isogram
		} 
		else
		{			
			LetterSeen[Letter] = true; // add the letter to the map
		}

	}
	return true; // for example in cases where /0 is entered
}
