
#include "Enemy.h"
#include "SamplePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

AEnemy::AEnemy()
{
	SetActivated(false);
}

void AEnemy::Init()
{
	SpawnDefaultController();

	SetActivated(true);
}

void AEnemy::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);

	if (Player)
		TargetLocation = Player->GetActorLocation();

	LookAtTarget();
	Move();
	Fire(DeltaTime);
}

void AEnemy::OnHit(UPrimitiveComponent* OtherComp, AActor* OtherActor, UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit)
{
	if (OtherActor->ActorHasTag("PlayerProjectile"))
		SetActivated(false);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AEnemy::OnHit);
}

void AEnemy::LookAtTarget()
{
	Super::LookAtTarget();
}

void AEnemy::Move()
{
	MoveVector = TargetLocation - GetActorLocation();

	Super::Move();
}

void AEnemy::Fire(float DeltaTime)
{
	Super::Fire(DeltaTime);
}
