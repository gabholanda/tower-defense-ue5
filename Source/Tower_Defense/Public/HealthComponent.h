// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthReachedZero);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthUpdate, int32, NewHealth);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWER_DEFENSE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

public:
	UFUNCTION(BlueprintGetter)
	int32 GetHealth() const;

	UFUNCTION(BlueprintSetter)
	void SetHealth(int32 NewAmount);

	UFUNCTION(BlueprintGetter)
	int32 GetMaxHealth() const;

	UFUNCTION(BlueprintSetter)
	void SetMaxHealth(int32 NewAmount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void ReceiveDamage(int32 Damage);

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercentage();

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthReachedZero OnHealthReachedZero;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthUpdate OnHealthUpdate;

private:
	UPROPERTY(BlueprintGetter = GetHealth, BlueprintSetter = SetHealth)
	int Health = 10;

	int MaxHealth = 10;

};
