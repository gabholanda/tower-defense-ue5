#include "FireTowerActor.h"

#include "AbilityInputID.h"
#include "AbilitySystemComponent.h"
#include "TowerDataAsset.h"

void AFireTowerActor::BeginPlay()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(FireballAbility, 1, static_cast<int32>(EAbilityInputID::TowerFireball), this));
	}

	if (TowerData)
	{
		SetCost(TowerData->Cost);
	}
}
