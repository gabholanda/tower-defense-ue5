// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireballAbility.h"
#include "TowerFireballAbility.generated.h"

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API UTowerFireballAbility : public UFireballAbility
{
	GENERATED_BODY()

public:

	// Overrides ActivateAbility
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
