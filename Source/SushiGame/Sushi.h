// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sushi.generated.h"

UENUM(BlueprintType)
enum class SushiType: uint8
{
	NONE,
	MAKI,
	NIGIRI_SALMON,
	NIGIRI_SQUID,
	NIGIRI_EGG,
	SASHIMI,
	TEMPURA,
	WASABI,
	CHOPSTICKS,
	DUMPLING,
	PUDDING,
};

UCLASS()
class SUSHIGAME_API ASushi : public AActor
{
	GENERATED_BODY()

public:
	ASushi();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* SushiMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		SushiType Type = SushiType::NONE;

};
