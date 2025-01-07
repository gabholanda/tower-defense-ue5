// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerActor.generated.h"

UCLASS(Abstract)
class TOWER_DEFENSE_API ATowerActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATowerActor();

public:
    UFUNCTION(BlueprintGetter)
    int32 GetResourceAmount() const;

    UFUNCTION(BlueprintSetter)
    void SetResourceAmount(int32 NewAmount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Abstract Functions")
	void PerformInteraction(AActor* Target);

private:
    // Private variable exposed via getter and setter
    UPROPERTY(BlueprintGetter = GetResourceAmount, BlueprintSetter = SetResourceAmount)
    int32 ResourceAmount;

};
