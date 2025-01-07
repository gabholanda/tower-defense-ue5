// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tower_DefenseGameMode.h"
#include "Tower_DefenseCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "TowerResourceManager.h"

ATower_DefenseGameMode::ATower_DefenseGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	
	ResourceManager = NewObject<UTowerResourceManager>();
	ResourceManager->Initialize(InitialResourcesAmount); // Starting with 100 resources
}

void ATower_DefenseGameMode::BeginPlay()
{
	StartWave(CurrentWaveIndex);
}

void ATower_DefenseGameMode::StartWave(uint8 Index)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	if (CurrentWaveIndex >= Waves.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Current Wave Index higher than amount of Waves"));
		return;
	}

	GetWorld()->GetTimerManager().ClearTimer(NextWaveTimerHandle);
	SpawnedEnemies = 0;

	FWaveStruct CurrentWave = Waves[CurrentWaveIndex];
	// Set up a timer to spawn enemies
	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&ATower_DefenseGameMode::SpawnEnemy,
		CurrentWave.SpawnInterval,
		true
	);
}

void ATower_DefenseGameMode::CallWave()
{
	StartWave(CurrentWaveIndex);
}

void ATower_DefenseGameMode::SpawnEnemy()
{
	UWorld* World = GetWorld();

	if (!World)
	{
		return;
	}

	FWaveStruct& CurrentWave = Waves[CurrentWaveIndex];

	if (SpawnedEnemies >= CurrentWave.Enemies.Num())
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);

		CurrentWaveIndex++;

		GetWorld()->GetTimerManager().SetTimer(
			NextWaveTimerHandle,
			this,
			&ATower_DefenseGameMode::CallWave,
			NextWaveInterval,
			false
		);
		return;
	}

	if (CurrentWave.Enemies.Num() > 0)
	{
		// Randomly select an enemy type and spawn location
		int32 EnemyIndex = SpawnedEnemies % CurrentWave.Enemies.Num();

		// Spawn the enemy
		FActorSpawnParameters SpawnParams;
		World->SpawnActor<AActor>(
			CurrentWave.Enemies[EnemyIndex],
			CurrentWave.SpawnLocation,
			FRotator::ZeroRotator,
			SpawnParams
		);

		SpawnedEnemies++;
	}
}
