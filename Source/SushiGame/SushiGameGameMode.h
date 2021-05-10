// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Sushi.h"
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SushiGameGameMode.generated.h"

USTRUCT(BlueprintType)
struct FConfigSushis
{

	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	Roll roll;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	Apetizer apetizer1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	Apetizer apetizer2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	Apetizer apetizer3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	Special special1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	Special special2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	Dessert dessert;

};

UCLASS()
class SUSHIGAME_API ASushiGameGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	int NumSushiPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TMap<SushiType, int32> NumCardsByType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FConfigSushis SushiConfiguration;
	/*
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 NumNigiriSalmon = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 NumNigiriEgg = 4;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 NumNigiriSquid = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 NumMaki1 = 4;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 NumMaki2 = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 NumMaki3 = 3;*/


private:
	const int NumTotalSushis = 181;

	UPROPERTY()
		TArray<SushiType> SushisToDeal;

	float TurnTime = 5.f;
	float TimeBetweenTurns = 2.f;


public:
	UFUNCTION(BlueprintCallable, Server, Reliable)
		void InitSushiGame();

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void CalculatePoints();

private:
	ASushiGameGameMode(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	void InitMapNumCardsByType();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	int NumOfSushisForPlayer();

	UFUNCTION(Server, Reliable)
		void StartTurn();
	UFUNCTION(Server, Reliable)
		void FinishTurn();


	TArray<SushiType> FillGameDeck(const FConfigSushis& _configSushis);
	void FillApetizersGameDeck(TArray<SushiType>& _deck, Apetizer apetizer);
	void FillSpecialsGameDeck(TArray<SushiType>& _deck, Special special);
	void FillFruitsGameDeck(TArray<SushiType>& _deck, int NumDesserts);
};
