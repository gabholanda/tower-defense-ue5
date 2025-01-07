// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerActor.h"
#include "FireTowerActor.generated.h"

/**
 *
 */
UCLASS()
class TOWER_DEFENSE_API AFireTowerActor : public ATowerActor
{
	GENERATED_BODY()

public:
	virtual void PerformInteraction_Implementation(AActor* Target);
};
