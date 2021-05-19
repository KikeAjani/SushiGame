// Fill out your copyright notice in the Description page of Project Settings.


#include "SushiGameStateBase.h"
#include "SushiList.h"
#include "Net/UnrealNetwork.h"


ASushiGameStateBase::ASushiGameStateBase() : Super()
{
	Hands = TArray<ASushiList*>();
	Plates = TArray<ASushiList*>();
}

void ASushiGameStateBase::AddToHand_Implementation(int PlayerID, SushiType Sushi)
{
	while (Hands.Num() <= PlayerID)
	{
		Hands.Add(NewObject<ASushiList>());
	}
	Hands[PlayerID]->Add(Sushi);
}

void ASushiGameStateBase::AddToPlate_Implementation(int PlayerID, SushiType Sushi)
{
	while (Plates.Num() <= PlayerID)
	{
		Plates.Add(NewObject<ASushiList>());
	}
	Plates[PlayerID]->Add(Sushi);
}

void ASushiGameStateBase::HandToPlate(int PlayerID, ASushi* Sushi)
{
	Hands[PlayerID]->Sushis.Remove(Sushi);
	Plates[PlayerID]->Sushis.Add(Sushi);
	Changes[PlayerID]->Add(Sushi->Type);
}

void ASushiGameStateBase::UpdateChanges_Implementation()
{
	//TODO chopsticks
	for (int ClientID = 0; ClientID < Changes.Num(); ++ClientID)
	{
		Hands[ClientID]->Sushis.Remove(Changes[ClientID]->Sushis[0]);
		Plates[ClientID]->Sushis.Add(Changes[ClientID]->Sushis[0]);
	}
}
