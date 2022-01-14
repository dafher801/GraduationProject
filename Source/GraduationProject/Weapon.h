
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StatusData.h"
#include "Weapon.generated.h"

UENUM()
enum class EWeaponName
{
	WEAPON_NAME_BEGIN,
	NORMAL,
	SAMPLE_PLAYER_WEAPON,
	WEAPON_NAME_END
};

UCLASS()
class GRADUATIONPROJECT_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	AWeapon();

public:

	virtual void Init();

	virtual void Tick(float DeltaTime) override;

	virtual void Disarm();

	UFUNCTION(Blueprintcallable)
		virtual void Fire();

	FStatus GetWeaponStatus() const;

	bool GetActivated() const;
	void SetActivated(bool Activated);

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
		FStatus WeaponStatus;

	bool bActivated;

};
