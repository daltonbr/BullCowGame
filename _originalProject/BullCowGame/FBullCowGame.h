/* The game logic (no view code or direct user interaction)
 * The game is a simple guess the word game based on Mastermind
 */

#pragma once
#include <string>

 // complying with Unreal Coding Standards
using FString = std::string;
using int32 = int;

// feedback to user in a single struct
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
	Not_Alpha
};

/* Base class for the game Bulls and Cows */
class FBullCowGame {
public:
	FBullCowGame(); // constructor
	//~FBullCowGame(); // destructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);


private:
	// see constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsGameWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool IsAlpha(FString) const;
};