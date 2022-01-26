
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MoveStop.generated.h"

UCLASS()
class GRADUATIONPROJECT_API UBTT_MoveStop : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTT_MoveStop();

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
