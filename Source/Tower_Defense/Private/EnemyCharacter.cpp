// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "AITypes.h"

#include "EnemyAIController.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	EnemyController = Cast<AEnemyAIController>(GetController());

	if (!EnemyController.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: EnemyController is NULL!"), *GetClass()->GetName());
		return;
	}

	EnemyController->StartPathing();
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


