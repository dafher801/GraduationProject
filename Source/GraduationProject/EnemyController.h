
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

UCLASS()
class GRADUATIONPROJECT_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:

	AEnemyController();

public:

	virtual void OnPossess(class APawn* InPawn) override;

public:

	static const FName VisibleFromTargetKey;

	static const FName TargetPosKey;

	static const FName MovableKey;

	static const FName AssailableKey;
	
protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
		class UBlackboardData* BlackboardData;
};
