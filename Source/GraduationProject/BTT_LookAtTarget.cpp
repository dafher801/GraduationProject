
#include "BTT_LookAtTarget.h"
#include "EnemyController.h"
#include "Enemy.h"

UBTT_LookAtTarget::UBTT_LookAtTarget()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTT_LookAtTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	EBTNodeResult::Type Result = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetCharacter())->
		LookAtTarget() ? EBTNodeResult::Type::Succeeded : EBTNodeResult::Type::Failed;

	return Result;
}

void UBTT_LookAtTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaTime)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaTime);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
