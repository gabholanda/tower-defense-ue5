#include "TowerActor.h"
#include "AbilityInputID.h"
#include "AbilitySystemComponent.h"

ATowerActor::ATowerActor()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

UAbilitySystemComponent* ATowerActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

int32 ATowerActor::GetCost() const
{
	return Cost;
}

void ATowerActor::SetCost(int32 NewAmount)
{
	Cost = NewAmount;
}
