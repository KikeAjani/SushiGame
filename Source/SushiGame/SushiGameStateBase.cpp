// Fill out your copyright notice in the Description page of Project Settings.


#include "SushiGameStateBase.h"
#include "SushiList.h"
#include "Net/UnrealNetwork.h"


ASushiGameStateBase::ASushiGameStateBase() : Super()
{
	Hands = TArray<ASushiList*>();
	Plates = TArray<ASushiList*>();
}

void ASushiGameStateBase::AddToHand_Implementation(int _PlayerID, SushiType Sushi)
{
	while (Hands.Num() <= _PlayerID)
	{
		Hands.Add(NewObject<ASushiList>());
	}
	Hands[_PlayerID]->Add(Sushi);
}

void ASushiGameStateBase::AddToPlate_Implementation(int _PlayerID, SushiType Sushi)
{
	while (Plates.Num() <= _PlayerID)
	{
		Plates.Add(NewObject<ASushiList>());
	}
	Plates[_PlayerID]->Add(Sushi);
}
