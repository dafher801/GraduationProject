
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_UpdateBlackboard.generated.h"

UCLASS()
class GRADUATIONPROJECT_API UBTS_UpdateBlackboard : public UBTService
{
	GENERATED_BODY()
	
public:

	UBTS_UpdateBlackboard();

public:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:

	void UpdatePlayerLocation(UBehaviorTreeComponent& OwnerComp);

	void UpdateVisibleFromTarget(UBehaviorTreeComponent& OwnerComp);

	void UpdateMovable(UBehaviorTreeComponent& OwnerComp);

	void UpdateAssailable(UBehaviorTreeComponent& OwnerComp);

};
