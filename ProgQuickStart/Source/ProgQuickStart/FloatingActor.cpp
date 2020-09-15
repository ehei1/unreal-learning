// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
	ActorPosition = GetActorLocation();
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	float DeltaHeight = FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime);
	auto radian = FMath::DegreesToRadians(Degree);
	
	auto x = FMath::Cos(radian) * Radius;
	auto y = FMath::Sin(radian) * Radius;

	NewLocation.X = ActorPosition.X + x;
	NewLocation.Y = ActorPosition.Y + y;
	NewLocation.Z += DeltaHeight * 20.f;
	RunningTime += DeltaTime;

	Degree += 1.f;
	
	SetActorLocation(NewLocation);
}

