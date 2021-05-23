// Fill out your copyright notice in the Description page of Project Settings.


#include "SushiPlayerController.h"

#include "SushiPlayer.h"
#include "Kismet/GameplayStatics.h"


void ASushiPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;

}

void ASushiPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindTouch(IE_Pressed, this, &ASushiPlayerController::Touched);
}

void ASushiPlayerController::Touched(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		PickSushi(FVector2D(Location.X, Location.Y));
	}
}

void ASushiPlayerController::PickSushi(FVector2D _vTapLocation)
{
	FVector vWorldPosition;
	FVector vWorldDirection;
	UGameplayStatics::DeprojectScreenToWorld(this, _vTapLocation, vWorldPosition, vWorldDirection);
	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, vWorldPosition, vWorldPosition + (vWorldDirection * 2000), ECollisionChannel::ECC_GameTraceChannel1);

	ASushiPlayer* SushiPlayer = Cast<ASushiPlayer>(GetPawn());
	ASushi* Sushi = Cast<ASushi>(Hit.Actor.Get());
	if (SushiPlayer && Sushi)
	{
		//SushiPlayer->PickSushi(Sushi);
		SushiPlayer->Selection = Sushi;
	}
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
