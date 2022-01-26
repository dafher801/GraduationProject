
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_LookAtTarget.generated.h"

UCLASS()
class GRADUATIONPROJECT_API UBTT_LookAtTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTT_LookAtTarget();

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaTime) override;

	
};
