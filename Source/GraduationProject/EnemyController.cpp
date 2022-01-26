
#include "EnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

const FName AEnemyController::TargetPosKey = TEXT("TargetPos");

const FName AEnemyController::VisibleFromTargetKey = TEXT("VisibleFromTarget");

const FName AEnemyController::MovableKey = TEXT("Movable");

const FName AEnemyController::AssailableKey = TEXT("Assailable");

AEnemyController::AEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BlackboardData, Blackboard))
		RunBehaviorTree(BehaviorTree);
}