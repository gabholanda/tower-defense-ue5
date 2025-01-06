#include "TowerResourceManager.h"

void UTowerResourceManager::Initialize(int32 StartingResources)
{
    CurrentResources = StartingResources;
}

bool UTowerResourceManager::SpendResources(int32 Amount)
{
    if (Amount > CurrentResources) return false;
    CurrentResources -= Amount;
    return true;
}

void UTowerResourceManager::AddResources(int32 Amount)
{
    CurrentResources += Amount;
}

int32 UTowerResourceManager::GetResources() const
{
    return CurrentResources;
}