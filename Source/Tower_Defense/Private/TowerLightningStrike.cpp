// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerLightningStrike.h"

#include "EnemyCharacter.h"
#include "HealthComponent.h"

void UTowerLightningStrike::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	AActor* OwningActor = ActorInfo->OwnerActor.Get();
	TArray<AActor*> OverlappingActors;
	OwningActor->GetOverlappingActors(OverlappingActors, AEnemyCharacter::StaticClass());

	for (AActor* Actor : OverlappingActors)
	{
		if (!LightningEffect)
		{
			continue;
		}

		if (IsValid(Actor))
		{
			if (UHealthComponent* HealthComponent = Actor->GetComponentByClass<UHealthComponent>())
			{
				HealthComponent->ReceiveDamage(Damage);
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(
					GetWorld(),
					LightningEffect,
					Actor->GetActorLocation() - FVector(0, 0, 300),
					FRotator::ZeroRotator
				);
			}
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}