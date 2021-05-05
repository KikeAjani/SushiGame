// Fill out your copyright notice in the Description page of Project Settings.


#include "Sushi.h"

// Sets default values
ASushi::ASushi()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootSceneComponent;
	SushiMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	//RootComponent = SushiMesh;
}

// Called when the game starts or when spawned
void ASushi::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASushi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

