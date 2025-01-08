#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

#include "LightingStrikeAbility.generated.h"


/**
 *
 */
UCLASS()
class TOWER_DEFENSE_API ULightningStrikeAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	ULightningStrikeAbility();
	// Overrides ActivateAbility
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RayDistance = 1000.0f;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	int Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UNiagaraSystem* LightningEffect;

};
