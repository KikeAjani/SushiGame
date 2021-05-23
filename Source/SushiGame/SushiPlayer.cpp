
#include "SushiPlayer.h"

#include "SushiGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


void ASushiPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASushiPlayer, PlayerID);
}

ASushiPlayer::ASushiPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASushiPlayer::BeginPlay()
{
	Super::BeginPlay();
	Selection = nullptr;
}

void ASushiPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASushiPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASushiPlayer::PickSushi(ASushi* Sushi)
{
	ASushiGameStateBase* GameState = Cast<ASushiGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	if (GameState)
	{
		GameState->HandToPlate(PlayerID, Sushi);
		Selection = nullptr;
	}
}
