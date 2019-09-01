#include "BullCowCartridge.h"
#include <unordered_set>

//#define DEBUG_MODE

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();
    InitGame();
}

// When the player hits enter
void UBullCowCartridge::OnInput(const FString& Input)
{
    if (bGameOver)
    {
        ClearScreen();
        InitGame();
        return;
    }

    if (!IsAlpha(Input))
    {
        PrintLine(TEXT("Enter only alphabetic characters [a-zA-Z]"));
        return;
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
        EndGame(true);
    }
    else
    {
        --CurrentLives;
        if (CurrentLives == 0)
        {
            //TODO: Show HiddenWord?
            EndGame(false);
            return;
        }
        PrintBullsCows(Input);
        PrintRemainingLives();
    }
}

void UBullCowCartridge::InitGame()
{
    //TODO: change this hardcoded words
    SetupGame(TEXT("cake"), 4);
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
    PrintRemainingLives();

#ifdef DEBUG_MODE
    PrintLine(TEXT("[DEBUG] HiddenWord: %s"), *HiddenWord);
#endif
}

void UBullCowCartridge::SetupGame(const FString hiddenWord, const uint8 lives)
{
    //TODO: check for isogram - word with non repeating letters  
    HiddenWord = hiddenWord;
    InitialLives = lives;
    CurrentLives = InitialLives;
    bGameOver = false;
}

// Check for repeating letters
bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    const TCHAR* Chars = *Word;
    auto UsedChars = std::unordered_set<TCHAR>();

    UsedChars.insert(Chars[0]);

    for (uint8 i = 1; i < Word.Len(); ++i)
    {
        std::unordered_set<TCHAR>::iterator it = UsedChars.find(Chars[i]);

        if (UsedChars.find(Chars[i]) != UsedChars.end())
        {
            // Found - not an isogram - repeating letters
            return false;
        }
        else
        {
            // not found - we must keep looking
            UsedChars.insert(Chars[i]);
        }
    }
    return true;
}

bool UBullCowCartridge::HasCorrectLength(const FString& Word) const
{
    return Word.Len() == HiddenWord.Len();
}

// Checks if the FString is composed by only alphabetic (ANSICHAR) characters
bool UBullCowCartridge::IsAlpha(const FString& Word) const
{
    const TCHAR* Chars = *Word;
   
    for (uint8 i = 0; i < Word.Len(); ++i)
    {
        if (TChar<ANSICHAR>::IsAlpha(Chars[i]))
        {
            //PrintLine(TEXT("is alphabetic"));
        }
        else
        {
            //PrintLine(TEXT("is not alphabetic"));
            return false;
        }
    }
    return true;
}

// Display End Game message (win or lose scenarios) according to bGameWasWin
void UBullCowCartridge::EndGame(const bool bGameWasWin)
{
    if (bGameWasWin)
    {
        PrintLine(TEXT("You Win!"));
    }
    else
    {
        PrintLine(TEXT("You Lose!"));
    }
    bGameOver = true;
    CurrentLives = 0;
    PrintLine(TEXT("Press <ENTER> to play again."));
}

void UBullCowCartridge::PrintRemainingLives() const
{
    PrintLine(TEXT("Remaining lives: %i"), CurrentLives);
}

void UBullCowCartridge::PrintBullsCows(const FString& Word) const
{
    uint8 Bulls = 0;
    uint8 Cows = 0;
    const TCHAR* Chars = *Word;

    for (uint8 i = 0; i < Word.Len(); ++i)
    {
        if (Chars[i] == HiddenWord[i])
        {
            ++Bulls;
            continue;
        }

        for (uint8 j = 0; j < HiddenWord.Len(); j++)
        {
            if (Chars[i] == HiddenWord[j])
            {
                ++Cows;
                break;
            }
        }
    }

    PrintLine(TEXT("[Bulls: %i | Cows: %i]"), Bulls, Cows);
}
