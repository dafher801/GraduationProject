
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StatusData.h"
#include "Projectile.generated.h"

UCLASS()
class GRADUATIONPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	AProjectile();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Init();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION() 
		virtual void OnHit(class UPrimitiveComponent* OtherComp, class AActor* OtherActor,
			class UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit);

	bool GetActivated() const;
	void SetActivated(bool Activated);

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
		class UCapsuleComponent* CapsuleCollision;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
		class UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Helper")
		class UArrowComponent* Direction;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement")
		class UProjectileMovementComponent* Movement;

	int Damage;

	float MaxMovementDistance;
	float CurrentMovementDistance;

	bool bActivated;

};
