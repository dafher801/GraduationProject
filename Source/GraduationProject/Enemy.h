
#pragma once

#include "CoreMinimal.h"
#include "Unit.h"
#include "Enemy.generated.h"

UCLASS()
class GRADUATIONPROJECT_API AEnemy : public AUnit
{
	GENERATED_BODY()

public:

	AEnemy();

public:

	virtual void Init();

	virtual void Tick(float DeltaTime) override;

	virtual bool Move() override;
	virtual bool LookAtTarget() override;
	virtual void Fire(float DeltaTime) override;

	UFUNCTION() virtual void OnHit(class UPrimitiveComponent* OtherComp, class AActor* OtherActor,
		class UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit);

	float GetAccessibleDistanceToPlayer() const;

	float GetDistanceFromPlayer() const;

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY()
		class ACharacter* Player;

	UPROPERTY()
		class UNavigationSystemV1* NavSystem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		float AccessibleDistanceToPlayer;

};
