// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LightingStrikeAbility.h"
#include "TowerLightningStrike.generated.h"

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API UTowerLightningStrike : public ULightningStrikeAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
