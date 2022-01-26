
#include "BTT_MoveStop.h"
#include "EnemyController.h"
#include "Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTT_MoveStop::UBTT_MoveStop()
{

}

EBTNodeResult::Type UBTT_MoveStop::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(
		OwnerComp.GetAIOwner(), OwnerComp.GetAIOwner()->GetCharacter()->GetActorLocation());

	return EBTNodeResult::Succeeded;
}
