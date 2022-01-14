
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StatusData.h"
#include "Unit.generated.h"

UCLASS()
class GRADUATIONPROJECT_API AUnit : public ACharacter
{
	GENERATED_BODY()

public:

	AUnit();

public:

	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	FStatus GetBaseStatus() const;

	FStatus GetCurrentStatus() const;

	bool GetActivated() const;
	void SetActivated(bool Activated);

	TSubclassOf<class AWeapon> GetWeaponClassName() const;

protected:

	virtual void BeginPlay() override;

	virtual void LookAtTarget();
	virtual void Move();
	virtual void Fire(float DeltaTime);

protected:

	UPROPERTY()
		class AWeaponSystem* WeaponSystem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
		TSubclassOf<class AWeapon> WeaponClassName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		FStatus BaseStatus;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		FStatus CurrentStatus;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Calculation")
		FRotator RotationErrorCalculation;

	FVector MoveVector;
	FRotator BodyRotation;

	FVector TargetLocation;

	float TimeElapsedSinceAttack;

	bool bActivated;

};
