// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sushi.generated.h"

UENUM(BlueprintType)
enum class SushiType: uint8
{
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
	NONE,
};

UCLASS()
class SUSHIGAME_API ASushi : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASushi();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* SushiMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		SushiType Type;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
