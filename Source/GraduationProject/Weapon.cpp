
#include "Weapon.h"
#include "Projectile.h"
#include "Unit.h"

AWeapon::AWeapon()
{
 	PrimaryActorTick.bCanEverTick = true;

	SetActivated(false);
}

void AWeapon::Init()
{
	SetActivated(true);
}

void AWeapon::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);
}

void AWeapon::Disarm()
{
	SetActivated(false);
}

void AWeapon::Fire()
{
	
}

FStatus AWeapon::GetWeaponStatus() const
{
	return WeaponStatus;
}

bool AWeapon::GetActivated() const
{
	return bActivated;
}

void AWeapon::SetActivated(bool Activated)
{
	bActivated = Activated;
	SetActorHiddenInGame(!bActivated);
	SetActorTickEnabled(bActivated);
	SetActorEnableCollision(bActivated);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}
