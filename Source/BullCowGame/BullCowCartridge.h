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

private:
    FString HiddenWord;
    uint8 InitialLives;
    uint8 CurrentLives;
    bool bGameOver;

    void PrintGreeting() const;
    void SetupGame(const FString HiddenWord, const uint8 lives);
    bool IsIsogram(const FString& Word) const;
    bool HasCorrectLength(const FString& Word) const;
    bool IsAlpha(const FString& Word) const;
    void EndGame(bool bGameWasWin);
    void InitGame();
    void ShowRemainingLives() const;
};
