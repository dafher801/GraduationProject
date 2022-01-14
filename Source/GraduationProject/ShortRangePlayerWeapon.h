
#pragma once

#include "CoreMinimal.h"
#include "ShortRangeWeapon.h"
#include "ShortRangePlayerWeapon.generated.h"

UCLASS()
class GRADUATIONPROJECT_API AShortRangePlayerWeapon : public AShortRangeWeapon
{
	GENERATED_BODY()
	
public:

	virtual void Fire() override;

};
