// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"

#include "GameFramework/PlayerController.h"
#include "SushiPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SUSHIGAME_API ASushiPlayerController : public APlayerController
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable)
		AActor* TapFocusable(FVector2D _vTapLocation);
	
};
