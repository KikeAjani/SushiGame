// Copyright Epic Games, Inc. All Rights Reserved.

#include "SushiGameGameMode.h"
#include "SushiGameStateBase.h"
#include "SushiList.h"
#include "SushiPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "SushiPlayerController.h"






ASushiGameGameMode::ASushiGameGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerControllerClass = ASushiPlayerController::StaticClass();
	DefaultPawnClass = ASushiPlayer::StaticClass();

	NumSushiPlayers = 0;
}

void ASushiGameGameMode::BeginPlay()
{
	Super::BeginPlay();
	InitMapNumCardsByType();
	
}

void ASushiGameGameMode::InitMapNumCardsByType()
{
	NumCardsByType.Add(SushiType::NIGIRI_EGG, 4);
	NumCardsByType.Add(SushiType::NIGIRI_SALMON, 5);
	NumCardsByType.Add(SushiType::NIGIRI_SQUID, 3);
	NumCardsByType.Add(SushiType::URAMAKI_3, 4);
	NumCardsByType.Add(SushiType::URAMAKI_4, 4);
	NumCardsByType.Add(SushiType::URAMAKI_5, 4);
	NumCardsByType.Add(SushiType::TEMAKI, 12);
	NumCardsByType.Add(SushiType::MAKI_1, 4);
	NumCardsByType.Add(SushiType::MAKI_2, 5);
	NumCardsByType.Add(SushiType::MAKI_3, 3);
	NumCardsByType.Add(SushiType::TEA, 3);
	NumCardsByType.Add(SushiType::TAKEOUT_BOX, 3);
	NumCardsByType.Add(SushiType::MENU, 3);
	NumCardsByType.Add(SushiType::WASABI, 3);
	NumCardsByType.Add(SushiType::SOY_SAUCE, 3);
	NumCardsByType.Add(SushiType::SPOON, 3);
	NumCardsByType.Add(SushiType::CHOPSTICKS, 3);
	NumCardsByType.Add(SushiType::SPECIAL_ORDER, 3);
	NumCardsByType.Add(SushiType::TEMPURA, 8);
	NumCardsByType.Add(SushiType::TOFU, 8);
	NumCardsByType.Add(SushiType::MISO_SOUP, 8);
	NumCardsByType.Add(SushiType::EEL, 8);
	NumCardsByType.Add(SushiType::SASHIMI, 8);
	NumCardsByType.Add(SushiType::DUMPLING, 8);
	NumCardsByType.Add(SushiType::EDAMAME, 8);
	NumCardsByType.Add(SushiType::ONIGIRI_CIRCLE, 2);
	NumCardsByType.Add(SushiType::ONIGIRI_SQUARE, 2);
	NumCardsByType.Add(SushiType::ONIGIRI_TRIANGLE, 2);
	NumCardsByType.Add(SushiType::ONIGIRI_RECT, 2);
	NumCardsByType.Add(SushiType::GREEN_TEA_ICECREAM, 15);
	NumCardsByType.Add(SushiType::PUDDING, 15);
	NumCardsByType.Add(SushiType::FRUIT_OO, 2);
	NumCardsByType.Add(SushiType::FRUIT_PO, 3);
	NumCardsByType.Add(SushiType::FRUIT_PP, 2);
	NumCardsByType.Add(SushiType::FRUIT_WO, 3);
	NumCardsByType.Add(SushiType::FRUIT_WP, 3);
	NumCardsByType.Add(SushiType::FRUIT_WW, 2);
}

TArray<SushiType> ASushiGameGameMode::FillGameDeck(const FConfigSushis& _configSushis)
{
	TArray<SushiType> deck;

	//NIGIRI
	for (int i = 0; i < (*NumCardsByType.Find(SushiType::NIGIRI_SALMON)); i++)
	{
		deck.Add(SushiType::NIGIRI_SALMON);
	}
	for (int i = 0; i < (*NumCardsByType.Find(SushiType::NIGIRI_SQUID)); i++)
	{
		deck.Add(SushiType::NIGIRI_SQUID);
	}
	for (int i = 0; i < (*NumCardsByType.Find(SushiType::NIGIRI_EGG)); i++)
	{
		deck.Add(SushiType::NIGIRI_EGG);
	}

	//ROLLS
	switch (_configSushis.roll)
	{
	case Roll::MAKI:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::MAKI_1)); i++)
		{
			deck.Add(SushiType::MAKI_1);
		}
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::MAKI_2)); i++)
		{
			deck.Add(SushiType::MAKI_2);
		}
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::MAKI_3)); i++)
		{
			deck.Add(SushiType::MAKI_3);
		}
	};  break;
	case Roll::TEMAKI:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::TEMAKI)); i++)
		{
			deck.Add(SushiType::TEMAKI);
		}
	};  break;
	case Roll::URAMAKI:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::URAMAKI_3)); i++)
		{
			deck.Add(SushiType::URAMAKI_3);
		}
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::URAMAKI_4)); i++)
		{
			deck.Add(SushiType::URAMAKI_4);
		}
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::URAMAKI_5)); i++)
		{
			deck.Add(SushiType::URAMAKI_5);
		}
	};  break;
	}

	//APPETIZERS
	FillAppetizersGameDeck(deck, _configSushis.apetizer1);
	FillAppetizersGameDeck(deck, _configSushis.apetizer2);
	FillAppetizersGameDeck(deck, _configSushis.apetizer3);

	//SPECIALS
	FillSpecialsGameDeck(deck, _configSushis.special1);
	FillSpecialsGameDeck(deck, _configSushis.special2);

	//FRUITS
	int NumDesserts = 5;
	if (NumSushiPlayers >= 6)
	{
		NumDesserts = 7;
	}
	switch (_configSushis.dessert)
	{
	case Dessert::FRUIT: {
		FillFruitsGameDeck(deck, NumDesserts);
	}break;
	case Dessert::GREEN_TEA_ICECREAM: {
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::GREEN_TEA_ICECREAM)); i++)
		{
			deck.Add(SushiType::GREEN_TEA_ICECREAM);
		}
	}break;
	case Dessert::PUDDING: {
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::PUDDING)); i++)
		{
			deck.Add(SushiType::PUDDING);
		}	}break;
	}
	return deck;
}

void ASushiGameGameMode::FillFruitsGameDeck(TArray<SushiType>& _deck, int NumDesserts)
{
	for (int i = 0; i < NumDesserts; i++)
	{
		int random = FMath::FRandRange(static_cast<uint8>(SushiType::FRUIT_WW), static_cast<uint8>(SushiType::FRUIT_WO));
		SushiType type = (SushiType)random;

		switch (type)
		{
		case  SushiType::FRUIT_WW:
		{
			int numWW = *NumCardsByType.Find(SushiType::FRUIT_WW);
			if (numWW > 0)
			{
				_deck.Add(SushiType::FRUIT_WW);
				NumCardsByType.Emplace(SushiType::FRUIT_WW, numWW - 1);
			}
		} break;

		case  SushiType::FRUIT_OO:
		{
			int numOO = *NumCardsByType.Find(SushiType::FRUIT_OO);
			if (numOO > 0)
			{
				_deck.Add(SushiType::FRUIT_OO);
				NumCardsByType.Emplace(SushiType::FRUIT_OO, numOO - 1);
			}
		} break;

		case  SushiType::FRUIT_PO:
		{
			int numPO = *NumCardsByType.Find(SushiType::FRUIT_PO);
			if (numPO > 0)
			{
				_deck.Add(SushiType::FRUIT_PO);
				NumCardsByType.Emplace(SushiType::FRUIT_PO, numPO - 1);
			}
		} break;

		case  SushiType::FRUIT_PP:
		{
			int numPP = *NumCardsByType.Find(SushiType::FRUIT_PP);
			if (numPP > 0)
			{
				_deck.Add(SushiType::FRUIT_PP);
				NumCardsByType.Emplace(SushiType::FRUIT_PP, numPP - 1);
			}
		} break;

		case  SushiType::FRUIT_WO:
		{
			int numWO = *NumCardsByType.Find(SushiType::FRUIT_WO);
			if (numWO > 0)
			{
				_deck.Add(SushiType::FRUIT_WO);
				NumCardsByType.Emplace(SushiType::FRUIT_OO, numWO - 1);
			}
		} break;
		case  SushiType::FRUIT_WP:
		{
			int numWP = *NumCardsByType.Find(SushiType::FRUIT_WP);
			if (numWP > 0)
			{
				_deck.Add(SushiType::FRUIT_WP);
				NumCardsByType.Emplace(SushiType::FRUIT_WP, numWP - 1);
			}
		} break;
		}
	}
}

void ASushiGameGameMode::FillSpecialsGameDeck(TArray<SushiType>& _deck, Special special)
{
	switch (special)
	{
	case Special::CHOPSTICKS:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::CHOPSTICKS)); i++)
		{
			_deck.Add(SushiType::CHOPSTICKS);
		}
	}break;

	case Special::MENU:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::MENU)); i++)
		{
			_deck.Add(SushiType::MENU);
		}
	}break;

	case Special::SOY_SAUCE:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::SOY_SAUCE)); i++)
		{
			_deck.Add(SushiType::SOY_SAUCE);
		}
	}break;

	case Special::SPECIAL_ORDER:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::SPECIAL_ORDER)); i++)
		{
			_deck.Add(SushiType::SPECIAL_ORDER);
		}
	}break;

	case Special::SPOON:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::SPOON)); i++)
		{
			_deck.Add(SushiType::SPOON);
		}
	}break;

	case Special::TAKEOUT_BOX:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::TAKEOUT_BOX)); i++)
		{
			_deck.Add(SushiType::TAKEOUT_BOX);
		}
	}break;

	case Special::TEA:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::TEA)); i++)
		{
			_deck.Add(SushiType::TEA);
		}
	}break;

	case Special::WASABI:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::WASABI)); i++)
		{
			_deck.Add(SushiType::WASABI);
		}
	}break;
	}
}


void ASushiGameGameMode::FillAppetizersGameDeck(TArray<SushiType>& _deck, Apetizer apetizer)
{
	switch (apetizer)
	{
	case Apetizer::DUMPLING:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::DUMPLING)); i++)
		{
			_deck.Add(SushiType::DUMPLING);
		}
	} break;

	case Apetizer::EDAMAME:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::EDAMAME)); i++)
		{
			_deck.Add(SushiType::EDAMAME);
		}
	} break;

	case Apetizer::EEL:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::EEL)); i++)
		{
			_deck.Add(SushiType::EEL);
		}
	} break;

	case Apetizer::MISO_SOUP:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::MISO_SOUP)); i++)
		{
			_deck.Add(SushiType::MISO_SOUP);
		}
	} break;

	case Apetizer::SASHIMI:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::SASHIMI)); i++)
		{
			_deck.Add(SushiType::SASHIMI);
		}
	} break;

	case Apetizer::TEMPURA:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::TEMPURA)); i++)
		{
			_deck.Add(SushiType::TEMPURA);
		}
	} break;

	case Apetizer::TOFU:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::TOFU)); i++)
		{
			_deck.Add(SushiType::TOFU);
		}
	} break;

	case Apetizer::ONIGIRI:
	{
		for (int i = 0; i < (*NumCardsByType.Find(SushiType::ONIGIRI_CIRCLE)); i++)
		{
			_deck.Add(SushiType::ONIGIRI_CIRCLE);
		}

		for (int i = 0; i < (*NumCardsByType.Find(SushiType::ONIGIRI_RECT)); i++)
		{
			_deck.Add(SushiType::ONIGIRI_RECT);
		}

		for (int i = 0; i < (*NumCardsByType.Find(SushiType::ONIGIRI_TRIANGLE)); i++)
		{
			_deck.Add(SushiType::ONIGIRI_TRIANGLE);
		}

		for (int i = 0; i < (*NumCardsByType.Find(SushiType::ONIGIRI_SQUARE)); i++)
		{
			_deck.Add(SushiType::ONIGIRI_SQUARE);
		}
	} break;
	}
}

void ASushiGameGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GetLocalRole() == ROLE_Authority)
	{
		ASushiPlayer* SushiPlayer = Cast<ASushiPlayer>(NewPlayer->GetPawn());
		if (SushiPlayer)
		{
			SushiPlayer->PlayerID = NumSushiPlayers;
		}
		NumSushiPlayers++;
	}
}

int ASushiGameGameMode::NumOfSushisForPlayer()
{
	if (NumSushiPlayers <= 3) {	return 10; }
	if (NumSushiPlayers <= 5) {	return 9; }
	if (NumSushiPlayers <= 7) {	return 8; }
	return 7;
}

void ASushiGameGameMode::InitSushiGame_Implementation()
{
	ASushiGameStateBase* SushiGameState = Cast<ASushiGameStateBase>(GetWorld()->GetGameState());
	if ((GetLocalRole() == ROLE_Authority) && SushiGameState)
	{
		//Init GameState
		SushiGameState->Init(NumSushiPlayers);
		
		// Init empty Plates
		for (int i = 0; i < NumSushiPlayers; ++i)
		{
			for (int j = 0; j < NumOfSushisForPlayer(); ++j)
			{
				SushiGameState->AddToPlate(i, SushiType::NONE);
			}
		}

		// Init Hands
		{
			/* Init Sushis to deal
			for (int i = 0; i < NumTotalSushis; ++i)
			{
				SushisToDeal.Add(SushiType::MAKI_1); //TODO
			}*/

			//SushiConfiguration = _configSushis;
			SushisToDeal = FillGameDeck(SushiConfiguration);



			// Deal (random)
			for (int i = 0; i < NumSushiPlayers; ++i)
			{
				for (int j = 0; j < NumOfSushisForPlayer(); ++j)
				{
					int RandomSushi = FMath::RandRange(0, SushisToDeal.Num() - 1);
					SushiGameState->AddToHand(i, SushisToDeal[RandomSushi]);

					SushisToDeal.RemoveAt(RandomSushi);
				}
			}
		}

		// Start game
		FTimerHandle TurnTimer;
		GetWorld()->GetTimerManager().SetTimer(TurnTimer, this, &ASushiGameGameMode::FinishTurn, TimeBetweenTurns, false);
	}
}

void ASushiGameGameMode::StartTurn_Implementation()
{
	ASushiGameStateBase* SushiGameState = Cast<ASushiGameStateBase>(GetWorld()->GetGameState());
	if ((GetLocalRole() == ROLE_Authority) && SushiGameState)
	{
		for (int i = 0; i < NumSushiPlayers; ++i)
		{
			ASushiPlayerController* SushiPlayerController = Cast<ASushiPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), i));
			if (SushiPlayerController)
			{
				SushiPlayerController->StartTurn();
			}
		}

		FTimerHandle TurnTimer;
		GetWorld()->GetTimerManager().SetTimer(TurnTimer, this, &ASushiGameGameMode::FinishTurn, TurnTime, false);
	}
}

void ASushiGameGameMode::FinishTurn_Implementation()
{
	ASushiGameStateBase* SushiGameState = Cast<ASushiGameStateBase>(GetWorld()->GetGameState());
	if ((GetLocalRole() == ROLE_Authority) && SushiGameState)
	{
		SushiGameState->SwapHands();
		for (int i = 0; i < NumSushiPlayers; ++i)
		{
			ASushiPlayerController* SushiPlayerController = Cast<ASushiPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), i));
			if (SushiPlayerController)
			{
				ASushiPlayer* SushiPlayer = Cast<ASushiPlayer>(SushiPlayerController->GetPawn());
				SushiPlayer->PickSushi(SushiPlayer->Selection);
				
				SushiPlayerController->FinishTurn();
			}
		}

		FTimerHandle TurnTimer;
		GetWorld()->GetTimerManager().SetTimer(TurnTimer, this, &ASushiGameGameMode::StartTurn, TimeBetweenTurns, false);
	}
}

void ASushiGameGameMode::CalculatePoints_Implementation()
{
	if (GetLocalRole() == ROLE_Authority)
	{

	}
}
