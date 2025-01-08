#include "LightningTower.h"

#include "AbilityInputID.h"
#include "AbilitySystemComponent.h"
#include "TowerDataAsset.h"

void ALightningTower::BeginPlay()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(LightningAbility, 1, static_cast<int32>(EAbilityInputID::TowerLightningStrike), this));
	}

	if (TowerData)
	{
		SetCost(TowerData->Cost);
	}
}