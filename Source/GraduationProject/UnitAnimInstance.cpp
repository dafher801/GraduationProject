
#include "UnitAnimInstance.h"
#include "Unit.h"

UUnitAnimInstance::UUnitAnimInstance()
{

}

void UUnitAnimInstance::PlayFireMontage()
{
	AUnit* Unit = Cast<AUnit>(TryGetPawnOwner());

	if (IsValid(Unit) && !Montage_IsPlaying(FireMontage))
	{
		Montage_Play(FireMontage, Unit->GetCurrentStatus().AttackSpeed * FireMontage->GetPlayLength());
	}
}

void UUnitAnimInstance::AnimNotify_Fire()
{
	AUnit* Unit = Cast<AUnit>(TryGetPawnOwner());

	if (IsValid(Unit))
		Unit->Fire(GetWorld()->DeltaTimeSeconds);
}

void UUnitAnimInstance::AnimNotify_ExitFire()
{
	AUnit* Unit = Cast<AUnit>(TryGetPawnOwner());

	if (IsValid(Unit))
		Unit->ExitFire();
}
