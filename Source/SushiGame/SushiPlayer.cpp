
// Fill out your copyright notice in the Description page of Project Settings.


#include "SushiPlayer.h"

// Sets default values
ASushiPlayer::ASushiPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASushiPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASushiPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASushiPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

