
#include "BTT_Move.h"
#include "EnemyController.h"
#include "Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTT_Move::UBTT_Move()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTT_Move::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AEnemyController::TargetPosKey);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(OwnerComp.GetAIOwner(), TargetLocation);

	return EBTNodeResult::Succeeded;
}

void UBTT_Move::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaTime)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaTime);
	
	if (IsVisibleFromTarget(OwnerComp) && !IsAccessibleToTarget(OwnerComp))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(
			OwnerComp.GetAIOwner(), OwnerComp.GetAIOwner()->GetCharacter()->GetActorLocation());

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AEnemyController::TargetPosKey);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(OwnerComp.GetAIOwner(), TargetLocation);
}

bool UBTT_Move::IsVisibleFromTarget(UBehaviorTreeComponent& OwnerComp)
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsBool(AEnemyController::VisibleFromTargetKey);
}

bool UBTT_Move::IsAccessibleToTarget(UBehaviorTreeComponent& OwnerComp)
{
	AEnemy* AI = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetCharacter());
	FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AEnemyController::TargetPosKey);

	return AI->GetAccessibleDistanceToPlayer() < FVector::Dist(AI->GetActorLocation(), TargetLocation);
}
