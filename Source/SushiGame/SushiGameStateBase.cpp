// Fill out your copyright notice in the Description page of Project Settings.


#include "SushiGameStateBase.h"
#include "SushiList.h"
#include "Net/UnrealNetwork.h"


ASushiGameStateBase::ASushiGameStateBase() : Super()
{

}

void ASushiGameStateBase::Init_Implementation(int NumPlayers)
{
	Hands = TArray<ASushiList*>();
	Plates = TArray<ASushiList*>();
	Changes = TArray<ASushiList*>();

	for(int i=0; i<NumPlayers; i++)
	{
		Changes.Add(GetWorld()->SpawnActor<ASushiList>());
	}
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
	int index = -1;
	for(int i = 0; i< Plates[PlayerID]->Sushis.Num(); i++)
	{
		if(Plates[PlayerID]->Sushis[i]->Type == SushiType::NONE)
		{
			index = i;
			break;
		}
	}
	if(index != -1)
	{
		Plates[PlayerID]->Sushis[index]->Type = Sushi->Type;
		index = -1;
	}
	Changes[PlayerID]->Add(Sushi->Type);

	index = -1;
	for(int i = 0; i< Hands[PlayerID]->Sushis.Num(); i++)
	{
		if(Hands[PlayerID]->Sushis[i]->Type == Sushi->Type)
		{
			index = i;
			break;
		}
	}
	if(index != -1)
	{
		Hands[PlayerID]->Sushis[index]->Type = SushiType::NONE;

	}
}

void ASushiGameStateBase::UpdateChanges_Implementation()
{
	//TODO chopsticks
	for (int ClientID = 0; ClientID < Changes.Num(); ++ClientID)
	{
		Hands[ClientID]->Sushis.Remove(Changes[ClientID]->Sushis[0]);
		Plates[ClientID]->Sushis.Add(Changes[ClientID]->Sushis[0]);
	}
	for(int i=0; i<Changes.Num(); i++)
	{
		Changes[i]->Sushis.Reset();
	}
}
