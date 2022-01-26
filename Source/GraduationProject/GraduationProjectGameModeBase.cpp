
#include "GraduationProjectGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "SamplePlayer.h"
#include "Enemy.h"

#include <random>
#include <ctime>

AGraduationProjectGameModeBase::AGraduationProjectGameModeBase()
	: CurrentEnemyNum(0)
{
	srand((int)time(NULL));
}

void AGraduationProjectGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGraduationProjectGameModeBase::SpawnEnemy()
{
	FVector SpawnLocation;
	
	do
	{
		SpawnLocation = FVector(FRandomStream(rand()).FRandRange(-1000.0f, 1000.0f), 
			FRandomStream(rand()).FRandRange(-1000.0f, 1000.0f), Player->GetActorLocation().Z);

	} while (FVector::Distance(SpawnLocation, Player->GetActorLocation()) < Player->GetCurrentStatus().Range);

	if (CurrentEnemyNum >= MaxEnemyNum)
		CurrentEnemyNum = 0;

	for (int i = CurrentEnemyNum++; i < MaxEnemyNum; i++)
	{
		if (!EnemyArray[i]->GetActivated())
		{
			EnemyArray[i]->Init();
			EnemyArray[i]->SetActorLocation(SpawnLocation);
			return;
		}
	}
}

void AGraduationProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ASamplePlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	for (int i = 0; i < MaxEnemyNum; i++)
	{
		EnemyArray.Add(GetWorld()->SpawnActor<AEnemy>(EnemyClassName));
	}

	GetWorldTimerManager().SetTimer(SpawnEnemyTimer, this, 
		&AGraduationProjectGameModeBase::SpawnEnemy, EnemySpawnCoolTime, true);
}
