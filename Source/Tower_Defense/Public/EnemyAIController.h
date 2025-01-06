// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AITypes.h"

#include "EnemyAIController.generated.h"

UCLASS()
class TOWER_DEFENSE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	const void StartPathing();

private:
	UFUNCTION()
	void OnLocationReached(FAIRequestID RequestID, EPathFollowingResult::Type Result);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> Destinations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 1.0f;

private:
	uint8 Index = 0;

};
