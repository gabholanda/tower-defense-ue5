// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerActor.generated.h"

class UAbilitySystemComponent;
class UTowerDataAsset;

UCLASS(Abstract)
class TOWER_DEFENSE_API ATowerActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATowerActor();

    // Implement IAbilitySystemInterface
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
public:
    UFUNCTION(BlueprintGetter)
    int32 GetCost() const;

    UFUNCTION(BlueprintSetter)
    void SetCost(int32 NewAmount);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
    UTowerDataAsset* TowerData;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
    UAbilitySystemComponent* AbilitySystemComponent;

private:
    UPROPERTY(BlueprintGetter = GetCost, BlueprintSetter = SetCost)
    int32 Cost;

};
