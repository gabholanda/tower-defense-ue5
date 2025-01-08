#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TowerPlaceableComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWER_DEFENSE_API UTowerPlaceableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTowerPlaceableComponent();

public:
	UFUNCTION(BlueprintCallable)
	void OnBuildTower(UClass* Tower);

	bool HasPlacedTower();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SpawnLocationOffset;

private:
	AActor* PlacedTower = nullptr;
};
