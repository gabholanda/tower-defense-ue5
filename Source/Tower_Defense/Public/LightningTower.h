// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerActor.h"
#include "LightningTower.generated.h"

class UGameplayAbility;

UCLASS()
class TOWER_DEFENSE_API ALightningTower : public ATowerActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TSubclassOf<UGameplayAbility> LightningAbility;
};
