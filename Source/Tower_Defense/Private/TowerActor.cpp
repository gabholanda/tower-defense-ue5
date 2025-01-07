#include "TowerActor.h"


ATowerActor::ATowerActor()
{

}

int32 ATowerActor::GetResourceAmount() const
{
	return ResourceAmount;
}

void ATowerActor::SetResourceAmount(int32 NewAmount)
{
	ResourceAmount = NewAmount;
}

void ATowerActor::PerformInteraction_Implementation(AActor* Target)
{
}

