
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

	UFUNCTION() virtual void OnHit(class UPrimitiveComponent* OtherComp, class AActor* OtherActor,
		class UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit);

protected:

	virtual void BeginPlay() override;

	virtual void LookAtTarget() override;
	virtual void Move() override;
	virtual void Fire(float DeltaTime) override;

protected:

	class ACharacter* Player;

};
