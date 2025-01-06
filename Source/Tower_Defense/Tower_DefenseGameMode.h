// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Wave.h"

#include "Tower_DefenseGameMode.generated.h"

class UTowerResourceManager;

UCLASS(minimalapi)
class ATower_DefenseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATower_DefenseGameMode();

protected:
	virtual void BeginPlay() override;

	void CallWave();
	// Spawn the enemies for the current wave
	void StartWave(uint8 Index);

	// Callback for enemy spawn
	void SpawnEnemy();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waves")
	TArray<FWaveStruct> Waves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waves")
	uint8 CurrentWaveIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int InitialResourcesAmount = 10;

	TWeakObjectPtr<UTowerResourceManager> ResourceManager;

	FTimerHandle SpawnTimerHandle;
	FTimerHandle NextWaveTimerHandle;

	float NextWaveInterval = 10.0f;
	int SpawnedEnemies = 0;
};



