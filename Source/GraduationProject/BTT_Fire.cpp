
#include "BTT_Fire.h"
#include "EnemyController.h"
#include "Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_Fire::UBTT_Fire()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTT_Fire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemy* AI = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetCharacter());
	EBTNodeResult::Type NodeResultType = AI->IsFiring() ? EBTNodeResult::Failed : EBTNodeResult::InProgress;

	AI->BeginFire();

	return NodeResultType;
}

void UBTT_Fire::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaTime)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaTime);

	Cast<AEnemy>(OwnerComp.GetAIOwner()->GetCharacter())->LookAtTarget();

	if (!Cast<AEnemy>(OwnerComp.GetAIOwner()->GetCharacter())->IsFiring())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
