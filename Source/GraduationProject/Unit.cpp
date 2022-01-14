
#include "Unit.h"
#include "WeaponSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AUnit::AUnit()
	: MoveVector(FVector::ZeroVector)
	, BodyRotation(FRotator::ZeroRotator)
	, TargetLocation(FVector::ZeroVector)
	, TimeElapsedSinceAttack(0.0f)
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetConstraintMode(EDOFMode::Type::XYPlane);

	SetActivated(true);
}

void AUnit::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);
}

void AUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AUnit::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount -= CurrentStatus.DEF;

	if (DamageAmount > 0)
		CurrentStatus.HP -= DamageAmount;
	else
		DamageAmount = 0;

	if (CurrentStatus.HP <= 0.0f)
	{
		SetActivated(false);
		DetachFromControllerPendingDestroy();
	}

	return DamageAmount;
}

FStatus AUnit::GetBaseStatus() const
{
	return BaseStatus;
}

FStatus AUnit::GetCurrentStatus() const
{
	return CurrentStatus;
}

bool AUnit::GetActivated() const
{
	return bActivated;
}

void AUnit::SetActivated(bool Activated)
{
	bActivated = Activated;
	GetCharacterMovement()->SetActive(bActivated);
	SetActorHiddenInGame(!bActivated);
	SetActorTickEnabled(bActivated);
	SetActorEnableCollision(bActivated);
}

TSubclassOf<class AWeapon> AUnit::GetWeaponClassName() const
{
	return WeaponClassName;
}

void AUnit::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;

	WeaponSystem = GetWorld()->SpawnActor<AWeaponSystem>(SpawnParameters);
	WeaponSystem->AddWeapon(WeaponClassName);

	CurrentStatus = BaseStatus;
	GetCharacterMovement()->MaxWalkSpeed = CurrentStatus.MoveSpeed;

	TimeElapsedSinceAttack = 1.0f / CurrentStatus.AttackSpeed;
}

void AUnit::LookAtTarget()
{
	FVector2D UnitScreenLocation;
	FVector2D TargetScreenLocation;

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->
		ProjectWorldLocationToScreen(GetActorLocation(), UnitScreenLocation, true);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->
		ProjectWorldLocationToScreen(TargetLocation, TargetScreenLocation, true);

	BodyRotation = FVector(TargetScreenLocation - UnitScreenLocation, 0.0f).Rotation();

	SetActorRotation(BodyRotation + RotationErrorCalculation);
}

void AUnit::Move()
{
	AddMovementInput(MoveVector);
}

void AUnit::Fire(float DeltaTime)
{
	if (1.0f / CurrentStatus.AttackSpeed - (TimeElapsedSinceAttack += DeltaTime) <= 0)
	{
		WeaponSystem->Fire();
		TimeElapsedSinceAttack = 0.0f;
	}
}
