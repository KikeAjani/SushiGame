// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Sushi.h"
#include "CoreMinimal.h"
#include "SushiPlayer.generated.h"

class ASushi;


UCLASS()
class SUSHIGAME_API ASushiPlayer : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		uint8 PlayerID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TMap<SushiType, UStaticMesh*> MeshesByType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ASushi* Selection;

	public:
	ASushiPlayer();


protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void PickSushi(ASushi* Sushi);
	
};
