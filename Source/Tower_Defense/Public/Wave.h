// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"

#include "Wave.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct TOWER_DEFENSE_API FWaveStruct
{
	GENERATED_BODY()

public:
	// Too bad Unreal doesn't support TQueue for this situation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Properties")
	TArray<TSubclassOf<AEnemyCharacter>> Enemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Properties")
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Properties")
	float SpawnInterval;
};
