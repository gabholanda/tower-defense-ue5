// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "FireballAbility.generated.h"

/**x
 *
 */
UCLASS()
class TOWER_DEFENSE_API UFireballAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UFireballAbility();

	// Overrides ActivateAbility
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<AActor> FireballClass;
};
