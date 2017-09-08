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

// strongly typed enum c++11 (Unreal Coding Standards)
enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Has_Numbers
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor
	//~FBullCowGame(); // destructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();  // TODO make a more rich return value.	
	FBullCowCount SubmitValidGuess(FString);


private:
	// see constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bIsGameWon;

	bool IsIsogram(FString) const;
};