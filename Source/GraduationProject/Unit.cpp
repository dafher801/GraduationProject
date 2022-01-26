
#include "Unit.h"
#include "WeaponSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UnitAnimInstance.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AUnit::AUnit()
	: MoveVector(FVector::ZeroVector)
	, BodyRotation(FRotator::ZeroRotator)
	, TargetLocation(FVector::ZeroVector)
	, TimeElapsedSinceAttack(0.0f)
	, bFiring(false)
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

	TimeElapsedSinceAttack += DeltaTime;
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

bool AUnit::IsFiring() const
{
	return bFiring;
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

bool AUnit::Move()
{
	AddMovementInput(MoveVector);

	return true;
}

void AUnit::MoveExit()
{
	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, this);
}

bool AUnit::LookAtTarget()
{
	FVector2D UnitScreenLocation;
	FVector2D TargetScreenLocation;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController)
	{
		PlayerController->ProjectWorldLocationToScreen(GetActorLocation(), UnitScreenLocation, true);
		PlayerController->ProjectWorldLocationToScreen(TargetLocation, TargetScreenLocation, true);
	}
	else
		return false;

	BodyRotation = FVector(TargetScreenLocation - UnitScreenLocation, 0.0f).Rotation();

	SetActorRotation(BodyRotation + RotationErrorCalculation);

	return true;
}

void AUnit::BeginFire()
{
	if (!bFiring)
	{
		bFiring = true;
		TimeElapsedSinceAttack = 0.0f;
		Cast<UUnitAnimInstance>(GetMesh()->GetAnimInstance())->PlayFireMontage();
	}
}

void AUnit::Fire(float DeltaTime)
{
	WeaponSystem->Fire();
	TimeElapsedSinceAttack = 0.0f;
}

void AUnit::ExitFire()
{
	bFiring = false;
}
