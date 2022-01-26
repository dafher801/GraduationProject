
#pragma once

#include "CoreMinimal.h"
#include "Unit.h"
#include "SamplePlayer.generated.h"

UCLASS()
class GRADUATIONPROJECT_API ASamplePlayer : public AUnit
{
	GENERATED_BODY()
	
public:

	ASamplePlayer();

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	virtual void BeginPlay() override;

	virtual bool Move() override;
	virtual bool LookAtTarget() override;
	virtual void Fire(float DeltaTime) override;

	void InputForward(float NewForwardValue);
	void InputRight(float NewRightValue);

	void PressedLeftMouse(FKey key);
	void ReleasedLeftMouse(FKey key);

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
		class USpringArmComponent* SpringArmComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
		class UCameraComponent* CameraComponent;

	float CurrentForwardValue;
	float CurrentRightValue;

	bool bPressedLeftMouse;
	float PressedTimeLeftMouse;

	FVector WorldDirection;

};
