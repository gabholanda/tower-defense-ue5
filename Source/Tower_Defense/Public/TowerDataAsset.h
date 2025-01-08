// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TowerDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API UTowerDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
    int32 Cost;
};
