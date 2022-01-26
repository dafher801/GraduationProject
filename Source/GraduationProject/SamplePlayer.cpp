
#include "SamplePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ASamplePlayer::ASamplePlayer()
	: CurrentForwardValue(0.0f)
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ASamplePlayer::Tick(float DeltaTime)
{
	if (!bActivated)
		return;

	Super::Tick(DeltaTime);

	LookAtTarget();
	Move();
	Fire(DeltaTime);
}

void ASamplePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &ASamplePlayer::InputForward);
	InputComponent->BindAxis("MoveRight", this, &ASamplePlayer::InputRight);

	InputComponent->BindAction("Fire", IE_Pressed, this, &ASamplePlayer::PressedLeftMouse);
	InputComponent->BindAction("Fire", IE_Released, this, &ASamplePlayer::ReleasedLeftMouse);
}

void ASamplePlayer::BeginPlay()
{
	Super::BeginPlay();
}

bool ASamplePlayer::LookAtTarget()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->
		DeprojectMousePositionToWorld(TargetLocation, WorldDirection);

	return Super::LookAtTarget();
}

bool ASamplePlayer::Move()
{
	MoveVector = FVector(CurrentForwardValue, CurrentRightValue, 0.0f);

	if (MoveVector.SizeSquared() > 0.0f)
	{
		return Super::Move();
	}

	return false;
}

void ASamplePlayer::Fire(float DeltaTime)
{
	if (bPressedLeftMouse && !bFiring && 
		(1.0f / CurrentStatus.AttackSpeed - TimeElapsedSinceAttack) <= 0)
	{
		Super::Fire(DeltaTime);
	}
}

void ASamplePlayer::InputForward(float NewForwardValue)
{
	CurrentForwardValue = NewForwardValue;
}

void ASamplePlayer::InputRight(float NewRightValue)
{
	CurrentRightValue = NewRightValue;
}

void ASamplePlayer::PressedLeftMouse(FKey key)
{
	bPressedLeftMouse = true;
}

void ASamplePlayer::ReleasedLeftMouse(FKey key)
{
	bPressedLeftMouse = false;
}
