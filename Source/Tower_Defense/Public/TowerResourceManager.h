#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TowerResourceManager.generated.h"

/**
 * 
 */
UCLASS()
class TOWER_DEFENSE_API UTowerResourceManager : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(int32 StartingResources);
    bool SpendResources(int32 Amount);
    UFUNCTION(BlueprintCallable, Category=Resource)
    void AddResources(int32 Amount);
    UFUNCTION(BlueprintCallable, Category=Resource)
    int32 GetResources() const;

private:
    int32 CurrentResources;
};