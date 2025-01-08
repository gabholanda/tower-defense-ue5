#include "TowerFireballAbility.h"

#include "EnemyCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"

void UTowerFireballAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	AActor* OwningActor = ActorInfo->OwnerActor.Get();
	AActor* TargetActor = nullptr;
	TArray<AActor*> OverlappingActors;
	OwningActor->GetOverlappingActors(OverlappingActors, AEnemyCharacter::StaticClass());

	for (AActor* Actor : OverlappingActors)
	{
		if (IsValid(Actor))
		{
			TargetActor = Actor;
			break;
		}
	}

	if (TargetActor && FireballClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = OwningActor;
		FVector TargetLocation = TargetActor->GetActorLocation();
		FVector SpawnLocation = OwningActor->GetActorLocation() + OwningActor->GetActorUpVector() * 200.0f;
		FRotator SpawnRotation = OwningActor->GetActorRotation();
		FVector Direction = (TargetLocation - SpawnLocation).GetSafeNormal();

		AActor* Fireball = GetWorld()->SpawnActor<AActor>(FireballClass, SpawnLocation, SpawnRotation, SpawnParams);

		if (UProjectileMovementComponent* MovementComponent = Fireball->GetComponentByClass< UProjectileMovementComponent>())
		{
			MovementComponent->Velocity = Direction * MovementComponent->InitialSpeed;
		}
	}

	// End the ability
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
