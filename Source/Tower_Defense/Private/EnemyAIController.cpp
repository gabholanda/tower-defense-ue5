// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include <NavigationSystem.h>

const void AEnemyAIController::StartPathing()
{
	EPathFollowingRequestResult::Type Result = MoveToLocation(Destinations[Index], 1.0f);
	ReceiveMoveCompleted.AddDynamic(this, &AEnemyAIController::OnLocationReached);

	switch (Result)
	{
	case EPathFollowingRequestResult::Failed:
		UE_LOG(LogTemp, Warning, TEXT("Pathfollowing: MoveTo failed!"));
		break;
	case EPathFollowingRequestResult::AlreadyAtGoal:
		UE_LOG(LogTemp, Log, TEXT("Pathfollowing: Already at goal!"));
		break;
	case EPathFollowingRequestResult::RequestSuccessful:
		UE_LOG(LogTemp, Log, TEXT("Pathfollowing: MoveTo request successful!"));
		break;
	}
}

void AEnemyAIController::OnLocationReached(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if (Result == EPathFollowingResult::Type::Success)
	{
		Index++;
		if (Index < Destinations.Num())
		{
			MoveToLocation(Destinations[Index], Radius);
			return;
		}
	}
	ReceiveMoveCompleted.RemoveDynamic(this, &AEnemyAIController::OnLocationReached);
}