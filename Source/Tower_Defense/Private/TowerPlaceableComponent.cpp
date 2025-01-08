#include "TowerPlaceableComponent.h"

UTowerPlaceableComponent::UTowerPlaceableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTowerPlaceableComponent::OnBuildTower(UClass* Tower)
{
	UWorld* World = GetWorld();

	if (!World)
	{
		return;
	}

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	FVector CubeLocation = Owner->GetActorLocation();
	FVector SpawnLocation = CubeLocation + SpawnLocationOffset;
	FActorSpawnParameters SpawnParams;
	PlacedTower = GetWorld()->SpawnActor<AActor>(Tower, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
}

bool UTowerPlaceableComponent::HasPlacedTower()
{
	return PlacedTower != nullptr;
}
