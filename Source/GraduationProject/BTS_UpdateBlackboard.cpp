
#include "BTS_UpdateBlackboard.h"
#include "EnemyController.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTS_UpdateBlackboard::UBTS_UpdateBlackboard()
{

}

void UBTS_UpdateBlackboard::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UpdatePlayerLocation(OwnerComp);
	UpdateMovable(OwnerComp);
	UpdateVisibleFromTarget(OwnerComp);
}

void UBTS_UpdateBlackboard::UpdatePlayerLocation(UBehaviorTreeComponent& OwnerComp)
{
	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (Player)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(
			AEnemyController::TargetPosKey, Player->GetActorLocation());
	}
}

void UBTS_UpdateBlackboard::UpdateVisibleFromTarget(UBehaviorTreeComponent& OwnerComp)
{
	FHitResult HitResult;
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);

	FVector SelfLocation = OwnerComp.GetAIOwner()->GetCharacter()->GetActorLocation();
	FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AEnemyController::TargetPosKey);

	bool bVisibleFromTarget = !(GetWorld()->LineTraceSingleByObjectType(
		HitResult, SelfLocation, TargetLocation, CollisionObjectQueryParams));

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(
		AEnemyController::VisibleFromTargetKey, bVisibleFromTarget);
}

void UBTS_UpdateBlackboard::UpdateMovable(UBehaviorTreeComponent& OwnerComp)
{
	AEnemy* Owner = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetCharacter());
	bool Movable = !(Owner->GetAccessibleDistanceToPlayer() > Owner->GetDistanceFromPlayer() &&
		OwnerComp.GetBlackboardComponent()->GetValueAsBool(AEnemyController::VisibleFromTargetKey));

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyController::MovableKey, Movable);
}

void UBTS_UpdateBlackboard::UpdateAssailable(UBehaviorTreeComponent& OwnerComp)
{
	OwnerComp.GetBlackboardComponent()->GetValueAsBool(AEnemyController::VisibleFromTargetKey);
}
