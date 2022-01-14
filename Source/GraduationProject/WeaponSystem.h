
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.h"
#include "Containers/Array.h"
#include "Containers/Map.h"
#include "WeaponSystem.generated.h"

UCLASS()
class GRADUATIONPROJECT_API AWeaponSystem : public AActor
{
	GENERATED_BODY()

public:

	AWeaponSystem();

public:

	void AddWeapon(TSubclassOf<class AWeapon> WeaponClassName, EWeaponName WeaponName = EWeaponName::NORMAL);

	void UseWeapon(EWeaponName WeaponName);

	void ChangeWeapon(EWeaponName WeaponName);

	void ChangeWeapon(const TMap<EWeaponName, class AWeapon*>& ChangeWeapons);

	void Fire();

protected:
	
	UPROPERTY()
		TMap<EWeaponName, class AWeapon*> UsingWeapons;

	UPROPERTY()
		TMap<EWeaponName, class AWeapon*> WeaponMap;

};
