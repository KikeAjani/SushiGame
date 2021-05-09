// Fill out your copyright notice in the Description page of Project Settings.


#include "SushiPlayerController.h"
#include "SushiGameStateBase.h"


void ASushiPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ASushiGameStateBase* SushiGameState = Cast<ASushiGameStateBase>(GetWorld()->GetGameState());
	if (SushiGameState)
	{
		SushiGameState->TurnStartedDelegate.AddDynamic(this, &ASushiPlayerController::StartTurn);
		SushiGameState->TurnFinishedDelegate.AddDynamic(this, &ASushiPlayerController::FinishTurn);
	}
}

AActor* ASushiPlayerController::TapFocusable(FVector2D _vTapLocation)
{
	FVector vWorldPosition;
	FVector vWorldDirection;
	UGameplayStatics::DeprojectScreenToWorld(this, _vTapLocation, vWorldPosition, vWorldDirection);
	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, vWorldPosition, vWorldPosition + (vWorldDirection * 2000), ECollisionChannel::ECC_GameTraceChannel1);

	return Hit.Actor.Get();
}

void ASushiPlayerController::StartTurn_Implementation()
{
	if (GetPawn() && GetPawn()->IsLocallyControlled())
	{
		StartTurnBP();
	}
}

void ASushiPlayerController::FinishTurn_Implementation()
{
	if (GetPawn() && GetPawn()->IsLocallyControlled())
	{
		FinishTurnBP();
	}
}
