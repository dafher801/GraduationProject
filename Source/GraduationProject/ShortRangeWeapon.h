
#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Containers/Array.h"
#include "ShortRangeWeapon.generated.h"

UCLASS()
class GRADUATIONPROJECT_API AShortRangeWeapon : public AWeapon
{
	GENERATED_BODY()

public:

	AShortRangeWeapon();

public:

	virtual void Init();

	virtual void Tick(float DeltaTime) override;

	virtual void Disarm();

	virtual void Fire() override;

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Fire")
		float AssailableAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Fire")
		TArray<TEnumAsByte<EObjectTypeQuery>> TargetObjectTypes;

};
