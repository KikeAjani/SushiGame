// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sushi.generated.h"


UENUM(BlueprintType)
enum class Roll : uint8
{
	MAKI,
	TEMAKI,
	URAMAKI,
};

UENUM(BlueprintType)
enum class Apetizer : uint8
{
	DUMPLING,
	SASHIMI,
	TEMPURA,
	EEL,
	TOFU,
	ONIGIRI,
	EDAMAME,
	MISO_SOUP,
};

UENUM(BlueprintType)
enum class Special : uint8
{
	WASABI,
	CHOPSTICKS,
	SOY_SAUCE,
	TEA,
	MENU,
	SPOON,
	SPECIAL_ORDER,
	TAKEOUT_BOX,
};

UENUM(BlueprintType)
enum class Dessert : uint8
{
	PUDDING,
	GREEN_TEA_ICECREAM,
	FRUIT,
};

UENUM(BlueprintType)
enum class SushiType : uint8
{
	NONE,
	//nigiris
	NIGIRI_SALMON,
	NIGIRI_SQUID,
	NIGIRI_EGG,
	
	//rolls
	MAKI_1,
	MAKI_2,
	MAKI_3,
	TEMAKI,
	URAMAKI_3,
	URAMAKI_4,
	URAMAKI_5,

	//aperitizers
	DUMPLING,
	SASHIMI,
	TEMPURA,
	EEL,
	TOFU,
	ONIGIRI_CIRCLE,
	ONIGIRI_TRIANGLE,
	ONIGIRI_SQUARE,
	ONIGIRI_RECT,
	EDAMAME,
	MISO_SOUP,

	//specials
	WASABI,
	CHOPSTICKS,
	SOY_SAUCE,
	TEA,
	MENU,
	SPOON,
	SPECIAL_ORDER,
	TAKEOUT_BOX,

	//desserts
	PUDDING,
	GREEN_TEA_ICECREAM,
		//fruits
	FRUIT_WW = 100,
	FRUIT_PP = 101,
	FRUIT_OO = 102,
	FRUIT_WP = 103,
	FRUIT_PO = 104,
	FRUIT_WO = 105
};

UCLASS()
class SUSHIGAME_API ASushi : public AActor
{
	GENERATED_BODY()

public:
	ASushi();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* SushiMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		SushiType Type = SushiType::NONE;

};
