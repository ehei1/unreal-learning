// Fill out your copyright notice in the Description page of Project Settings.

#include <Camera/CameraComponent.h>
#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// 무언가를 붙일 더미 루트 컴포넌트를 만듭니다
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// 카메라와 보이는 오브젝트를 만듭니다
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	// 루트 컴포넌트에 카메라와 보이는 오브젝트를 붙입니다. 카메라를 이격 및 회전시킵니다.
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// "Grow" 액션에 따라 키우고 줄이는 것을 처리합니다
	{
		float CurrentScale = OurVisibleComponent->GetComponentScale().X;
		if (bGrowing)
		{
			if (CurrentVelocity.X || CurrentVelocity.Y) {
				CurrentScale = 2.f;
			}
			else {
				// 1 초에 걸쳐 두 배 크기로 키웁니다
				CurrentScale += DeltaTime;
			}
		}
		else
		{
			// 키운 속도대로 절반으로 줄입니다
			CurrentScale -= (DeltaTime * 0.5f);
		}
		// 시작 크기 아래로 줄이거나 두 배 이상으로 키우지 않도록 합니다.
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
		OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));
	}

	// "MoveX" 와 "MoveY" 축에 따라 이동을 처리합니다
	{
		if (!CurrentVelocity.IsZero())
		{
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
			SetActorLocation(NewLocation);
		}
	}
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// "Grow" 키를 누르거나 뗄 때 반응합니다
	InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	// "MoveX" 와 "MoveY" 두 이동 충의 값에 매 프레임 반응합니다
	InputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
}

void AMyPawn::Move_XAxis(float AxisValue)
{
	if (AxisValue) {
		auto speedDelta = AxisValue > 0 ? -0.001f : 0.001f;
		auto velocity = CurrentVelocity.X / 100.f + speedDelta;

		// 초당 100 유닛을 앞 또는 뒤로 움직입니다
		CurrentVelocity.X = FMath::Clamp(velocity, -5.f, 5.f) * 100.f;
	}
	else {
		CurrentVelocity.X = 0;
	}	
}

void AMyPawn::Move_YAxis(float AxisValue)
{
	if (AxisValue) {
		auto speedDelta = AxisValue > 0 ? -0.001f : 0.001f;
		auto velocity = CurrentVelocity.Y / 100.f + speedDelta;

		// 초당 100 유닛을 앞 또는 뒤로 움직입니다
		CurrentVelocity.Y = FMath::Clamp(velocity, -5.f, 5.f) * 100.f;
	}
	else {
		CurrentVelocity.Y = 0;
	}

}

void AMyPawn::StartGrowing()
{
	bGrowing = true;
}

void AMyPawn::StopGrowing()
{
	bGrowing = false;
}