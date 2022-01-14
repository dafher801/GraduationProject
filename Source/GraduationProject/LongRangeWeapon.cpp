
#include "LongRangeWeapon.h"
#include "Projectile.h"

ALongRangeWeapon::ALongRangeWeapon()
{

}

void ALongRangeWeapon::Init()
{
	Super::Init();
}

void ALongRangeWeapon::Tick(float DeltaTime)
{
	if (!bActivated)
		return;
	
	Super::Tick(DeltaTime);
}

void ALongRangeWeapon::Disarm()
{
	Super::Disarm();
}

void ALongRangeWeapon::Fire()
{
	Super::Fire();

	if (CurrentProjectileNum >= MaxProjectileNum)
		CurrentProjectileNum = 0;

	for (int i = CurrentProjectileNum++; i < MaxProjectileNum; i++)
	{
		if (!ProjectileArray[i]->GetActivated())
		{
			ProjectileArray[i]->Init();
			return;
		}
	}
}

void ALongRangeWeapon::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = GetInstigator();
	SpawnParameters.Owner = this;

	for (int i = 0; i < MaxProjectileNum; i++)
	{
		ProjectileArray.Add(GetWorld()->SpawnActor<AProjectile>(ProjectileClassName, SpawnParameters));
	}
}
