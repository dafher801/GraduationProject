
#include "Projectile.h"
#include "Unit.h"
#include "Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectile::AProjectile()
	: CurrentMovementDistance(0.0f)
{
 	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleCollision->SetConstraintMode(EDOFMode::Type::XYPlane);
	RootComponent = CapsuleCollision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Direction = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction"));
	Direction->SetupAttachment(RootComponent);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->ProjectileGravityScale = 0.0f;

	SetActivated(false);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CapsuleCollision->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::Init()
{
	SetActorLocation(GetInstigator()->GetActorLocation());
	SetActorRotation(GetInstigator()->GetActorRotation());

	Damage = 
		Cast<AWeapon>(GetOwner())->GetWeaponStatus().ATK +
		(Cast<AUnit>(GetInstigator()))->GetCurrentStatus().ATK;

	MaxMovementDistance = 
		Cast<AWeapon>(GetOwner())->GetWeaponStatus().Range +
		Cast<AUnit>(GetInstigator())->GetCurrentStatus().Range;

	CurrentMovementDistance = 0.0f;

	Movement->MaxSpeed = Movement->InitialSpeed = 1000.0f;
	Movement->Velocity = GetInstigator()->GetActorRotation().Vector() * Movement->MaxSpeed;

	SetActivated(true);
}

void AProjectile::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Log, TEXT("%f %f"), CurrentMovementDistance, MaxMovementDistance);

	if ((CurrentMovementDistance += (DeltaTime * Movement->MaxSpeed)) > MaxMovementDistance)
		SetActivated(false);
}

void AProjectile::OnHit(UPrimitiveComponent* OtherComp, AActor* OtherActor, UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit)
{
	Damage = 
		Cast<AWeapon>(GetOwner())->GetWeaponStatus().ATK + 
		Cast<AUnit>(GetInstigator())->GetCurrentStatus().ATK;

	UGameplayStatics::ApplyDamage(OtherActor, Damage,
		UGameplayStatics::GetPlayerController(GetWorld(), 0), this, NULL);

	SetActivated(false);
}

bool AProjectile::GetActivated() const
{
	return bActivated;
}

void AProjectile::SetActivated(bool Activated)
{
	bActivated = Activated;
	Movement->SetActive(bActivated);
	SetActorHiddenInGame(!bActivated);
	SetActorTickEnabled(bActivated);
	SetActorEnableCollision(bActivated);
}
