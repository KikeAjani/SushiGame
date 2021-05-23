
#include "Sushi.h"
#include "Net/UnrealNetwork.h"


void ASushi::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASushi, Type);
}

ASushi::ASushi()
{
	//SetReplicates(true);
	bReplicates = true;

	SushiMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SushiMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

