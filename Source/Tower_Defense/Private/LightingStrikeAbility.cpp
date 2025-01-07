// Fill out your copyright notice in the Description page of Project Settings.


#include "LightingStrikeAbility.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemComponent.h"
#include "Tower_DefenseCharacter.h"
#include "Camera/CameraComponent.h"

ULightingStrikeAbility::ULightingStrikeAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void ULightingStrikeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	ATower_DefenseCharacter* Character = Cast<ATower_DefenseCharacter>(ActorInfo->OwnerActor);
	if (Character && LightningStrikeClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Character;

		FVector SpawnLocation = Character->GetActorLocation() + Character->GetActorForwardVector() * 200.0f;
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
				SpawnLocation = HitResult.Location;
			}
		}
		FRotator SpawnRotation = Character->GetActorRotation();

		AActor* LightningStrike = GetWorld()->SpawnActor<AActor>(LightningStrikeClass, SpawnLocation, SpawnRotation, SpawnParams);
	}

	if (LightningStrikeMontage && Character)
	{
		Character->PlayAnimMontage(LightningStrikeMontage);
	}

	// End the ability
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
