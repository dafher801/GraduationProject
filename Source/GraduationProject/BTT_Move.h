
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Move.generated.h"

UCLASS()
class GRADUATIONPROJECT_API UBTT_Move : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTT_Move();

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaTime) override;

	bool IsVisibleFromTarget(UBehaviorTreeComponent& OwnerComp);

	bool IsAccessibleToTarget(UBehaviorTreeComponent& OwnerComp);

};
