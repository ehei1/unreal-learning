// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableCube.h"

// Sets default values
AMovableCube::AMovableCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovableCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovableCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

