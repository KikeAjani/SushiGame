
#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "SushiPlayerController.generated.h"


UCLASS()
class SUSHIGAME_API ASushiPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
		AActor* TapFocusable(FVector2D _vTapLocation);

	UFUNCTION(NetMulticast, Reliable)
	//UFUNCTION(BlueprintImplementableEvent)
		void StartTurn();

	UFUNCTION(NetMulticast, Reliable)
	//UFUNCTION(BlueprintImplementableEvent)
		void FinishTurn();

	UFUNCTION(BlueprintImplementableEvent)
		void StartTurnBP();

	UFUNCTION(BlueprintImplementableEvent)
		void FinishTurnBP();
};
