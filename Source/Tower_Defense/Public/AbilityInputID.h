#pragma once

#include "CoreMinimal.h"
#include "AbilityInputID.generated.h"

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
    None UMETA(DisplayName = "None"),
    Confirm UMETA(DisplayName = "Confirm"),  
    Cancel UMETA(DisplayName = "Cancel"),
    Fireball UMETA(DisplayName = "Fireball"),
};