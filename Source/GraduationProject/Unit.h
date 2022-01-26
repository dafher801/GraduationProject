
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

	virtual bool Move();
	void MoveExit();

	virtual bool LookAtTarget();

	virtual void BeginFire();
	virtual void Fire(float DeltaTime);
	virtual void ExitFire();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	FStatus GetBaseStatus() const;

	FStatus GetCurrentStatus() const;

	bool GetActivated() const;
	void SetActivated(bool Activated);

	bool IsFiring() const;

	TSubclassOf<class AWeapon> GetWeaponClassName() const;

protected:

	virtual void BeginPlay() override;

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

	bool bFiring;

};
