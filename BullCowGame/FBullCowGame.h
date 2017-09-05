#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// all values initialized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor
	//~FBullCowGame(); // destructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	
	void Reset();  // TODO make a more rich return value.	
	bool CheckGuessValidity(FString);   // TODO make a more rich return value.
	FBullCowCount SubmitGuess(FString);
	void IncrementTries();

private:
	// see constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
};