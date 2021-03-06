//#include "Containers/Array.h"
//#include "Containers/Set.h"
//#include "Math/UnrealMathUtility.h"
#include "BullCowCartridge.h"
#include "BullCowGame/HiddenWordList.h"

//#define DEBUG_MODE

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();
    ValidWords = GetValidWords(GHiddenWords);
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
        if (CurrentLives <= 0)
        {
            EndGame(false);
            return;
        }
        PrintBullsCows(Input);
        PrintRemainingLives();
    }
}

void UBullCowCartridge::InitGame()
{    
    const auto RandomIndex = FMath::RandRange(0, ValidWords.Num()-1);
    SetupGame(ValidWords[RandomIndex]);
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
    PrintLine(TEXT("Press <TAB> and guess the %i letter word!"), HiddenWord.Len());
    PrintRemainingLives();

#ifdef DEBUG_MODE
    PrintLine(TEXT("[DEBUG] HiddenWord: %s"), *HiddenWord);
#endif
}

// Filter words that have a certain length and also are valid isograms.
TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        const auto Length = Word.Len();
        if (Length >= MinLengthHiddenWords &&
            Length <= MaxLengthHiddenWords &&
            IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}

void UBullCowCartridge::SetupGame(const FString& NewHiddenWord)
{
    HiddenWord = NewHiddenWord;
    InitialLives = HiddenWord.Len() * 2;
    CurrentLives = InitialLives;
    bGameOver = false;
}

// Check for repeating letters
bool UBullCowCartridge::IsIsogram(const FString& Word)
{
    const TCHAR* Chars = *Word;
    auto UsedChars = TSet<TCHAR>();    
    UsedChars.Add(Chars[0]);    

    for (uint8 i = 1; i < Word.Len(); ++i)
    {
        if (UsedChars.Contains(Chars[i]))
        {
            return false;
        }           
        UsedChars.Add(Chars[i]);
    }
    return true;
}

bool UBullCowCartridge::HasCorrectLength(const FString& Word) const
{
    return Word.Len() == HiddenWord.Len();
}

// Checks if the FString is composed by only alphabetic (ANSICHAR) characters
bool UBullCowCartridge::IsAlpha(const FString& Word)
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
        PrintLine(TEXT("\nThe hidden word was: %s"), *HiddenWord);
    }
    bGameOver = true;
    CurrentLives = 0;
    PrintLine(TEXT("Press <ENTER> to play again."));
}

void UBullCowCartridge::PrintRemainingLives() const
{
    PrintLine(TEXT("Remaining lives: %i"), CurrentLives);
}

void UBullCowCartridge::PrintBullsCows(const FString& Guess) const
{
    uint8 Bulls;
    uint8 Cows;
    GetBullCows(Guess, Bulls, Cows);

    PrintLine(TEXT("[Bulls: %i | Cows: %i]"), Bulls, Cows);
}

void UBullCowCartridge::GetBullCows(const FString& Guess, uint8& OutBullCount, uint8& OutCowCount) const
{
    uint8 Bulls = 0;
    uint8 Cows = 0;
    const TCHAR* Chars = *Guess;

    for (uint8 i = 0; i < Guess.Len(); ++i)
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
    OutBullCount = Bulls;
    OutCowCount = Cows;
}
