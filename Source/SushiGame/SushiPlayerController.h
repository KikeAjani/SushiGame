
#pragma once

#include "CoreMinimal.h"
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
		void Touched(ETouchIndex::Type FingerIndex, FVector Location);
	UFUNCTION(BlueprintCallable)
		void PickSushi(FVector2D _vTapLocation);

	UFUNCTION(NetMulticast, Reliable)
		void StartTurn();

	UFUNCTION(NetMulticast, Reliable)
		void FinishTurn();

	UFUNCTION(BlueprintImplementableEvent)
		void StartTurnBP();

	UFUNCTION(BlueprintImplementableEvent)
		void FinishTurnBP();
	
protected:
	virtual void SetupInputComponent() override;
	
};
