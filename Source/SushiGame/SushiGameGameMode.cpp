// Copyright Epic Games, Inc. All Rights Reserved.

#include "SushiGameGameMode.h"
#include "SushiGameStateBase.h"
#include "SushiList.h"
#include "SushiPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "SushiPlayerController.h"


ASushiGameGameMode::ASushiGameGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerControllerClass = ASushiPlayerController::StaticClass();
	DefaultPawnClass = ASushiPlayer::StaticClass();

	NumSushiPlayers = 0;
}

void ASushiGameGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GetLocalRole() == ROLE_Authority)
	{
		ASushiPlayer* SushiPlayer = Cast<ASushiPlayer>(NewPlayer->GetPawn());
		if (SushiPlayer)
		{
			SushiPlayer->PlayerID = NumSushiPlayers;
		}
		NumSushiPlayers++;
	}
}

int ASushiGameGameMode::NumOfSushisForPlayer()
{
	return 8; //TODO
}

void ASushiGameGameMode::InitSushiGame_Implementation()
{
	ASushiGameStateBase* SushiGameState = Cast<ASushiGameStateBase>(GetWorld()->GetGameState());
	if ((GetLocalRole() == ROLE_Authority) && SushiGameState)
	{
		// Init empty Plates
		for (int i = 0; i < NumSushiPlayers; ++i)
		{
			for (int j = 0; j < NumOfSushisForPlayer(); ++j)
			{
				SushiGameState->AddToPlate(i, SushiType::MAKI); //PROVISIONAL TO TEST (SHOULD BE NONE)
			}
		}

		// Init Hands
		{
			// Init Sushis to deal
			for (int i = 0; i < NumTotalSushis; ++i)
			{
				SushisToDeal.Add(SushiType::MAKI); //TODO
			}

			// Deal (random)
			for (int i = 0; i < NumSushiPlayers; ++i)
			{
				for (int j = 0; j < NumOfSushisForPlayer(); ++j)
				{
					int RandomSushi = FMath::RandRange(0, SushisToDeal.Num() - 1);
					SushiGameState->AddToHand(i, SushisToDeal[RandomSushi]);

					SushisToDeal.RemoveAt(RandomSushi);
				}
			}
		}

		// Start game
		FTimerHandle TurnTimer;
		GetWorld()->GetTimerManager().SetTimer(TurnTimer, this, &ASushiGameGameMode::FinishTurn, TimeBetweenTurns, false);
	}
}

void ASushiGameGameMode::StartTurn_Implementation()
{
	ASushiGameStateBase* SushiGameState = Cast<ASushiGameStateBase>(GetWorld()->GetGameState());
	if ((GetLocalRole() == ROLE_Authority) && SushiGameState)
	{
		for (int i = 0; i < NumSushiPlayers; ++i)
		{
			ASushiPlayerController* SushiPlayerController = Cast<ASushiPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), i));
			if (SushiPlayerController)
			{
				SushiPlayerController->StartTurn();
			}
		}

		FTimerHandle TurnTimer;
		GetWorld()->GetTimerManager().SetTimer(TurnTimer, this, &ASushiGameGameMode::FinishTurn, TurnTime, false);
	}
}

void ASushiGameGameMode::FinishTurn_Implementation()
{
	ASushiGameStateBase* SushiGameState = Cast<ASushiGameStateBase>(GetWorld()->GetGameState());
	if ((GetLocalRole() == ROLE_Authority) && SushiGameState)
	{
		for (int i = 0; i < NumSushiPlayers; ++i)
		{
			ASushiPlayerController* SushiPlayerController = Cast<ASushiPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), i));
			if (SushiPlayerController)
			{
				SushiPlayerController->FinishTurn();
			}
		}

		FTimerHandle TurnTimer;
		GetWorld()->GetTimerManager().SetTimer(TurnTimer, this, &ASushiGameGameMode::StartTurn, TimeBetweenTurns, false);
	}
}

void ASushiGameGameMode::CalculatePoints_Implementation()
{
	if (GetLocalRole() == ROLE_Authority)
	{

	}
}
