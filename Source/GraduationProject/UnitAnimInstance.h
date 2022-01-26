
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UnitAnimInstance.generated.h"

UCLASS()
class GRADUATIONPROJECT_API UUnitAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UUnitAnimInstance();

public:

	void PlayFireMontage();

protected:

	UFUNCTION()
		void AnimNotify_Fire();

	UFUNCTION()
		void AnimNotify_ExitFire();

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Fire")
		class UAnimMontage* FireMontage;
	
};
