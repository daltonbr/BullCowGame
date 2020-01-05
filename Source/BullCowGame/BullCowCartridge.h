#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
    virtual void OnInput(const FString& Input) override;
    const uint8 MinLengthHiddenWords = 4;
    const uint8 MaxLengthHiddenWords = 6;

private:
    FString HiddenWord;
    uint8 InitialLives;
    uint8 CurrentLives;
    bool bGameOver;
    TArray<FString> ValidWords;

    void PrintGreeting() const;
    TArray<FString> GetValidWords(const TArray<FString>& WordList) const;
    void SetupGame(const FString& NewHiddenWord);
    static bool IsIsogram(const FString& Word);
    bool HasCorrectLength(const FString& Word) const;
    static bool IsAlpha(const FString& Word);
    void EndGame(bool bGameWasWin);
    void InitGame();
    void PrintRemainingLives() const;
    void PrintBullsCows(const FString& Guess) const;
    void GetBullCows(const FString& Guess, uint8& OutBullCount, uint8& OutCowCount) const;
};
