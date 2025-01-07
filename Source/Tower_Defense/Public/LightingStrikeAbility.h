a// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LightingStrikeAbility.generated.h"

/**
 *
 */
	UCLASS()
	class TOWER_DEFENSE_API ULightingStrikeAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	ULightingStrikeAbility();
	// Overrides ActivateAbility
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RayDistance = 1000.0f;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<AActor> LightningStrikeClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	UAnimMontage* LightningStrikeMontage;


};
