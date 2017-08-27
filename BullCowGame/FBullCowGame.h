#pragma once
#include <string>

/*
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <istream>
*/
class FBullCowGame {
public:
	int GetMaxTries() const;
	int GetCurrentTry() const;
	bool IsGameWon() const;
	
	void Reset();  // TODO make a more rich return value.	
	bool CheckGuessValidity(std::string);   // TODO make a more rich return value.
	void IncrementTries();

private:
	int MyCurrentTry = 1;
	int MyMaxTries = 5;
};