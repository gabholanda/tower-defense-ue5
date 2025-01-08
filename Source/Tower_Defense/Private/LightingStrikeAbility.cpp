// Fill out your copyright notice in the Description page of Project Settings.


#include "LightingStrikeAbility.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "HealthComponent.h"
#include "Tower_DefenseCharacter.h"
#include <Kismet/GameplayStatics.h>

ULightningStrikeAbility::ULightningStrikeAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void ULightningStrikeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	ATower_DefenseCharacter* Character = Cast<ATower_DefenseCharacter>(ActorInfo->OwnerActor);
	if (Character && LightningEffect)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Character;

		if (UCameraComponent* CameraComponent = Character->GetFirstPersonCameraComponent())
		{
			FVector CameraLocation = CameraComponent->GetComponentLocation();
			FRotator CameraRotation = CameraComponent->GetComponentRotation();
			FVector ForwardDirection = CameraRotation.Vector();

			FVector RayEnd = CameraLocation + (ForwardDirection * RayDistance);

			// Perform the ray trace
			FHitResult HitResult;
			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(Character);

			bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, RayEnd, ECC_Visibility, CollisionParams);

			if (bHit)
			{
				if (AActor* HitActor = HitResult.GetActor())
				{
					if (UHealthComponent* HealthComponent = HitActor->GetComponentByClass<UHealthComponent>())
					{
						HealthComponent->ReceiveDamage(Damage);
						UNiagaraFunctionLibrary::SpawnSystemAtLocation(
							GetWorld(),
							LightningEffect,
							HitResult.ImpactPoint - FVector(0, 0, 300),
							FRotator::ZeroRotator
						);
					}
				}
			}
		}
		FRotator SpawnRotation = Character->GetActorRotation();
	}

	// End the ability
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
