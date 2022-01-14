
#include "WeaponSystem.h"
#include "Unit.h"

AWeaponSystem::AWeaponSystem()
{
	
}

void AWeaponSystem::AddWeapon(TSubclassOf<AWeapon> WeaponClassName, EWeaponName WeaponName)
{
	FAttachmentTransformRules AttachRules = { EAttachmentRule::KeepRelative, true };

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = Cast<APawn>(GetOwner());

	WeaponMap.Add(WeaponName, GetWorld()->SpawnActor<AWeapon>(WeaponClassName, SpawnParameters));
	WeaponMap[WeaponName]->Init();
	UsingWeapons.Add(WeaponName, WeaponMap[WeaponName]);
}

void AWeaponSystem::UseWeapon(EWeaponName WeaponName)
{
	if (WeaponMap.Find(WeaponName))
		UsingWeapons.Add(WeaponName, WeaponMap[WeaponName]);
}

void AWeaponSystem::ChangeWeapon(EWeaponName WeaponName)
{
	if (WeaponMap.Find(WeaponName))
	{
		UsingWeapons.Empty();
		UsingWeapons.Add(WeaponName, WeaponMap[WeaponName]);
	}
}

void AWeaponSystem::ChangeWeapon(const TMap<EWeaponName, class AWeapon*>& ChangeWeapons)
{

}

void AWeaponSystem::Fire()
{
	for (TPair<EWeaponName, AWeapon*> iter : UsingWeapons)
	{
		if (iter.Value->GetActivated())
			iter.Value->Fire();
	}
}
