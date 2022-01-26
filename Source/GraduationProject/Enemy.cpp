
#include "Enemy.h"
#include "EnemyController.h"
#include "SamplePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AEnemy::AEnemy()
	: Player(nullptr)
	, NavSystem(nullptr)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

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
}

bool AEnemy::Move()
{
	if (NavSystem && Controller && Player)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Player);
	}

	return GetActorLocation() == Player->GetActorLocation();
}

bool AEnemy::LookAtTarget()
{
	if (Player)
		TargetLocation = Player->GetActorLocation();
	else
		return false;

	return Super::LookAtTarget();
}

void AEnemy::Fire(float DeltaTime)
{
	Super::Fire(DeltaTime);
}

void AEnemy::OnHit(UPrimitiveComponent* OtherComp, AActor* OtherActor, UPrimitiveComponent* Other, FVector NormalImpulse, const FHitResult& hit)
{
	if (OtherActor->ActorHasTag("PlayerProjectile"))
		SetActivated(false);
}

float AEnemy::GetAccessibleDistanceToPlayer() const
{
	return AccessibleDistanceToPlayer;
}

float AEnemy::GetDistanceFromPlayer() const
{
	return FVector::Dist(GetActorLocation(), Player->GetActorLocation());
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AEnemy::OnHit);
}
