
#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Containers/Array.h"
#include "LongRangeWeapon.generated.h"

UCLASS()
class GRADUATIONPROJECT_API ALongRangeWeapon : public AWeapon
{
	GENERATED_BODY()

public:

	ALongRangeWeapon();

public:

	virtual void Init() override;

	virtual void Tick(float DeltaTime) override;

	virtual void Disarm() override;

	virtual void Fire() override;

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
		TArray<class AProjectile*> ProjectileArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
		TSubclassOf<class AProjectile> ProjectileClassName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
		int MaxProjectileNum;

	int CurrentProjectileNum;

};
