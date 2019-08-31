#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();
    InitGame();
}

// When the player hits enter
void UBullCowCartridge::OnInput(const FString& Input)
{
    if (CurrentLives == 0)
    {
        ClearScreen();
        InitGame();
    }

    if (!HasCorrectLength(Input))
    {
        PrintLine(FString::Printf(TEXT("The hidden word is %i characters long, try again!"), HiddenWord.Len()));
        return;
    }

    if (!IsIsogram(Input))
    {
        PrintLine(TEXT("Your guess isn't an isogram, try again!"));
        return;
    }

    if (Input.ToLower() == HiddenWord.ToLower())
    {
        ShowWinMessage();
    }
    else
    {
        CurrentLives--;
        if (CurrentLives == 0)
        {
            GameOver();
        }
        PrintLine(TEXT("Remaining lives: %i"), CurrentLives); 
    }

    // Remove Life

    // Check lives > 0
        //if yes GuessAgain - show lives left
        //if no show GameOver (and HiddenWord?)

    //Prompt to PlayAgain, Press <ENTER> to play again
    // Check user input
    // PlayAgain or Quit
}

void UBullCowCartridge::InitGame()
{
    //TODO: change this hardcoded words
    SetupGame(TEXT("art"), 3);
    PrintGreeting();
}

void UBullCowCartridge::PrintGreeting() const
{
    PrintLine(TEXT("  ___________________________ "));
    PrintLine(TEXT(" |Welcome to Bulls and Cows! |"));
    PrintLine(TEXT(" |_____A fun word game_____  |"));
    PrintLine(TEXT("                \\"));
    PrintLine(TEXT("      _________}____{"));
    PrintLine(TEXT("     /| o Oo O | oO |"));
    PrintLine(TEXT("    *|\\_o_Oo__/(    )"));
    PrintLine(TEXT("     |        | (oo)"));
    // This is how we interpolate strings, but PrintLine make that easy for us
    //PrintLine(FString::Printf(TEXT("Press <TAB> and guess the %i letter word!"), HiddenWord.Len()));
    PrintLine(TEXT("Press <TAB> and guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("Press <ENTER> to confirm your guess!"));

    // DEBUG
    PrintLine(TEXT("[DEBUG] HiddenWord: %s"), *HiddenWord);
}

void UBullCowCartridge::SetupGame(const FString hiddenWord, const uint8 lives)
{
    //TODO: check for isogram - word with non repeating letters  
    HiddenWord = hiddenWord;
    InitialLives = lives;
    CurrentLives = InitialLives;
}

void UBullCowCartridge::ShowWinMessage()
{
    PrintLine(TEXT("You Win!"));
    PrintLine(TEXT("Press any key to play again"));
    CurrentLives = 0;
}

void UBullCowCartridge::GameOver()
{
    PrintLine(TEXT("You Lose!"));
    PrintLine(TEXT("Press any key to play again"));
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    //TODO
    return true;
}

bool UBullCowCartridge::HasCorrectLength(const FString& Word) const
{
    return Word.Len() == HiddenWord.Len();
}
