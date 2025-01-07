
#include "FireballAbility.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemComponent.h"
#include "Tower_DefenseCharacter.h"

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

	ATower_DefenseCharacter* Character = Cast<ATower_DefenseCharacter>(ActorInfo->OwnerActor);
	if (Character && FireballClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Character;

		FVector SpawnLocation = Character->GetActorLocation() + Character->GetActorForwardVector() * 200.0f;
		FRotator SpawnRotation = Character->GetActorRotation();

		AActor* Fireball = GetWorld()->SpawnActor<AActor>(FireballClass, SpawnLocation, SpawnRotation, SpawnParams);
	}

	if (FireballMontage && Character)
	{
		Character->PlayAnimMontage(FireballMontage);
	}

	// End the ability
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
