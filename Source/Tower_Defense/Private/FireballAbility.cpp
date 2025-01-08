
#include "FireballAbility.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemComponent.h"

UFireballAbility::UFireballAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UFireballAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	AActor* OwningActor = ActorInfo->OwnerActor.Get();
	if (OwningActor && FireballClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = OwningActor;

		FVector SpawnLocation = OwningActor->GetActorLocation() + OwningActor->GetActorForwardVector() * 200.0f;
		FRotator SpawnRotation = OwningActor->GetActorRotation();

		AActor* Fireball = GetWorld()->SpawnActor<AActor>(FireballClass, SpawnLocation, SpawnRotation, SpawnParams);
	}

	// End the ability
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
