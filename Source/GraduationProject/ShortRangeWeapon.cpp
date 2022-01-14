
#include "ShortRangeWeapon.h"
#include "Unit.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Components/CapsuleComponent.h"

AShortRangeWeapon::AShortRangeWeapon()
{

}

void AShortRangeWeapon::Init()
{
	Super::Init();
}

void AShortRangeWeapon::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);
}

void AShortRangeWeapon::Disarm()
{
	Super::Disarm();
}

void AShortRangeWeapon::Fire()
{
	Super::Fire();

	TArray<AActor*> OverlapActors;

	float Radius = WeaponStatus.Range + Cast<AUnit>(GetInstigator())->GetCurrentStatus().Range;
	float Damage = WeaponStatus.ATK + Cast<AUnit>(GetInstigator())->GetCurrentStatus().ATK;
	float Angle; 
	
	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetInstigator()->GetActorLocation(), 
		Radius, TargetObjectTypes, AUnit::StaticClass(), TArray<AActor*>(), OverlapActors);

	for (AActor* iter : OverlapActors)
	{
		Angle = FMath::Abs((iter->GetActorLocation() -
			GetInstigator()->GetActorLocation()).Rotation().Yaw -
			GetInstigator()->GetActorRotation().Yaw);

		if (Angle < AssailableAngle)
		{
			UGameplayStatics::ApplyDamage(iter, Damage,
				UGameplayStatics::GetPlayerController(GetWorld(), 0), this, NULL);
		}
	}
}

void AShortRangeWeapon::BeginPlay()
{
	Super::BeginPlay();
}
