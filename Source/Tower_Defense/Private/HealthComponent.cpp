// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

int32 UHealthComponent::GetHealth() const
{
	return Health;
}

void UHealthComponent::SetHealth(int32 NewAmount)
{
	Health = FMath::Clamp(NewAmount, 0, MaxHealth);
}

int32 UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

void UHealthComponent::SetMaxHealth(int32 NewAmount)
{
	MaxHealth = NewAmount;
	Health = NewAmount;
}

void UHealthComponent::ReceiveDamage(int32 Damage)
{
	Health = FMath::Clamp(Health - Damage, 0, MaxHealth);

	OnHealthUpdate.Broadcast(Health);
	if (Health == 0)
	{
		OnHealthReachedZero.Broadcast();
	}
}

float UHealthComponent::GetHealthPercentage()
{
	return static_cast<float>(Health) / MaxHealth;
}

