
#pragma once

#include "CoreMinimal.h"
#include "LongRangeWeapon.h"
#include "LongRangeEnemyWeapon.generated.h"

UCLASS()
class GRADUATIONPROJECT_API ALongRangeEnemyWeapon : public ALongRangeWeapon
{
	GENERATED_BODY()

public:

	ALongRangeEnemyWeapon();

public:

	virtual void Tick(float DeltaTime) override;

};
