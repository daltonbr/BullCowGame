// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();
    PrintGreeting();
}

// When the player hits enter
void UBullCowCartridge::OnInput(const FString& Input)
{
    FString HiddenWord = TEXT("cake");
    ClearScreen();
    
}

void UBullCowCartridge::PrintGreeting() const
{
    PrintLine(TEXT("  ___________________________ "));
    PrintLine(TEXT(" |Welcome to Bulls and Cows! |"));
    PrintLine(TEXT(" |_____A fun word game_____  |"));
    PrintLine(TEXT("                \\"));
    PrintLine(TEXT("      _________}____{"));
    PrintLine(TEXT("     /|        | oO |"));
    PrintLine(TEXT("    *|\\_______/(    )"));
    PrintLine(TEXT("     |        | (oo)"));
    PrintLine(TEXT("Press <TAB> to focus"));
    PrintLine(TEXT("Press <ENTER> to confirm your guess!"));
}
