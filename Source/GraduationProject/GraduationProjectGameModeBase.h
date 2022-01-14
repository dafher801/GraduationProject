
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Containers/Array.h"
#include "GraduationProjectGameModeBase.generated.h"

UCLASS()
class GRADUATIONPROJECT_API AGraduationProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AGraduationProjectGameModeBase();

public:

	virtual void Tick(float DeltaTime) override;

	void SpawnEnemy();

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY()
		FTimerHandle SpawnEnemyTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
		TArray<class AEnemy*> EnemyArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
		TSubclassOf<class AEnemy> EnemyClassName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
		float EnemySpawnCoolTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
		int MaxEnemyNum;

	int CurrentEnemyNum;

	class ASamplePlayer* Player;
	
};
