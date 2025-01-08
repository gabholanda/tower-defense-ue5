// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tower_DefenseCharacter.h"

#include "AbilityInputID.h"
#include "AbilitySystemComponent.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "FireballAbility.h"
#include "FireTowerActor.h"
#include "LightningTower.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TowerResourceManager.h"
#include "TowerPlaceableComponent.h"
#include "Tower_DefenseProjectile.h"
#include <Kismet/GameplayStatics.h>
#include <Tower_Defense/Tower_DefenseGameMode.h>
#include "TowerDataAsset.h"

//////////////////////////////////////////////////////////////////////////
// ATower_DefenseCharacter

ATower_DefenseCharacter::ATower_DefenseCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

UAbilitySystemComponent* ATower_DefenseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATower_DefenseCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(FireballAbility, 1, static_cast<int32>(EAbilityInputID::Fireball), this));
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(LightningStrikeAbility, 1, static_cast<int32>(EAbilityInputID::LightningStrike), this));
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void ATower_DefenseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->BindAbilityActivationToInputComponent(
			PlayerInputComponent,
			FGameplayAbilityInputBinds(
				"Confirm",
				"Cancel",
				"EAbilityInputID",
				static_cast<int32>(EAbilityInputID::Confirm),
				static_cast<int32>(EAbilityInputID::Cancel)
			)
		);
	}
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATower_DefenseCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATower_DefenseCharacter::Look);

		EnhancedInputComponent->BindAction(FireballAction, ETriggerEvent::Triggered, this, &ATower_DefenseCharacter::HandleFireballInput);
		EnhancedInputComponent->BindAction(LightningStrikeAction, ETriggerEvent::Triggered, this, &ATower_DefenseCharacter::HandleLightningStrikeInput);

		EnhancedInputComponent->BindAction(PickFireTowerAction, ETriggerEvent::Triggered, this, &ATower_DefenseCharacter::PickFireTower);
		EnhancedInputComponent->BindAction(PickLightningTowerAction, ETriggerEvent::Triggered, this, &ATower_DefenseCharacter::PickLightningTower);
		EnhancedInputComponent->BindAction(BuildPickedTowerAction, ETriggerEvent::Triggered, this, &ATower_DefenseCharacter::BuildPickedTower);
		EnhancedInputComponent->BindAction(CancelTowerPickAction, ETriggerEvent::Triggered, this, &ATower_DefenseCharacter::CancelTowerPick);
	}
}


void ATower_DefenseCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ATower_DefenseCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}

	if (PickedTowerClass)
	{
		FHitResult HitResult;
		FVector Start = FirstPersonCameraComponent->GetComponentLocation();
		FVector End = Start + (FirstPersonCameraComponent->GetForwardVector() * TraceDistance);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility))
		{
			AActor* HitActor = HitResult.GetActor();
			if (HitActor)
			{
				if (UMeshComponent* MeshComponent = HitActor->GetComponentByClass<UMeshComponent>())
				{
					if (UTowerPlaceableComponent* TowerPlaceableComponent = HitActor->GetComponentByClass<UTowerPlaceableComponent>())
					{
						PlaceableComponent = TowerPlaceableComponent;

						if (PlaceableComponent->HasPlacedTower())
						{
							MeshComponent->SetMaterial(0, BlockPlacementMaterial);
						}
						else
						{
							MeshComponent->SetMaterial(0, AllowPlacementMaterial);
						}
					}
				}
			}
		}
	}
}

void ATower_DefenseCharacter::PickFireTower(const FInputActionValue& Value)
{
	PickedTowerClass = FireTower;
	TowerCost = FireTowerData->Cost;
}

void ATower_DefenseCharacter::PickLightningTower(const FInputActionValue& Value)
{
	PickedTowerClass = LightningTower;
	TowerCost = LightningTowerData->Cost;
}

void ATower_DefenseCharacter::CancelTowerPick(const FInputActionValue& Value)
{
	PickedTowerClass = nullptr;
	TowerCost = 0;
}

void ATower_DefenseCharacter::BuildPickedTower(const FInputActionValue& Value)
{
	if (!PickedTowerClass)
	{
		return;
	}

	if (!PlaceableComponent || PlaceableComponent->HasPlacedTower())
	{
		return;
	}

	ATower_DefenseGameMode* GameMode = Cast<ATower_DefenseGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		if (UTowerResourceManager* ResourceManager = GameMode->GetResourceManager())
		{
			if (!ResourceManager->SpendResources(TowerCost))
			{
				return;
			}
		}
	}

	PlaceableComponent->OnBuildTower(PickedTowerClass);
}

void ATower_DefenseCharacter::HandleFireballInput(const FInputActionValue& Value)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->TryActivateAbilityByClass(FireballAbility);
	}
}

void ATower_DefenseCharacter::HandleLightningStrikeInput(const FInputActionValue& Value)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->TryActivateAbilityByClass(LightningStrikeAbility);
	}
}

void ATower_DefenseCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ATower_DefenseCharacter::GetHasRifle()
{
	return bHasRifle;
}