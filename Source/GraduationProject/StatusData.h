
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "StatusData.generated.h"

USTRUCT()
struct FStatus : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float ATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float DEF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float Range;

	FORCEINLINE struct FStatus operator*(float Ratio)
	{
		FStatus ret;

		ret.HP = HP * Ratio;
		ret.ATK = ATK * Ratio;
		ret.AttackSpeed = AttackSpeed * Ratio;
		ret.DEF = DEF * Ratio;
		ret.MoveSpeed = MoveSpeed * Ratio;
		ret.Range = Range * Ratio;

		return ret;
	}

	FORCEINLINE struct FStatus operator+(const FStatus& Status)
	{
		HP += Status.HP;
		ATK += Status.ATK;
		DEF += Status.DEF;
		MoveSpeed += Status.MoveSpeed;
		AttackSpeed += Status.AttackSpeed;
		Range += Status.Range;

		return *this;
	}

	FORCEINLINE struct FStatus& operator+=(const FStatus& Status)
	{
		HP += Status.HP;
		ATK += Status.ATK;
		DEF += Status.DEF;
		MoveSpeed += Status.MoveSpeed;
		AttackSpeed += Status.AttackSpeed;
		Range += Status.Range;

		return *this;
	}
};

UCLASS()
class GRADUATIONPROJECT_API UStatusData : public UObject
{
	GENERATED_BODY()
};
