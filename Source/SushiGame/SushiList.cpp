
#include "SushiList.h"
#include "Net/UnrealNetwork.h"


void ASushiList::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASushiList, Sushis);
}

ASushiList::ASushiList()
{
	bReplicates = true;
	bAlwaysRelevant = true;

}

void ASushiList::Add(SushiType _Type)
{
	ASushi* Sushi = NewObject<ASushi>();
	Sushi->Type = _Type;
	Sushis.Add(Sushi);
}
