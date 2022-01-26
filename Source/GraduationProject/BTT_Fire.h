
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Fire.generated.h"

UCLASS()
class GRADUATIONPROJECT_API UBTT_Fire : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTT_Fire();

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
protected:

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaTime) override;

};
