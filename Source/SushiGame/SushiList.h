// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sushi.h"
#include "SushiList.generated.h"


UCLASS()
class SUSHIGAME_API ASushiList : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		TArray<ASushi*> Sushis;

public:
	ASushiList();

	UFUNCTION()
		void Add(SushiType _Type);

};
