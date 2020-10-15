// Fill out your copyright notice in the Description page of Project Settings.

#include <GameFramework/Actor.h>
#include <GameFramework/MovementComponent.h>
#include <Components/SphereComponent.h>
#include "OrbitMovementComponent.h"
#include "SateliteActor.h"

// Sets default values
ASateliteActor::ASateliteActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(0.1f);
	SphereComponent->SetCollisionProfileName(TEXT("Satelite"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));

	if (SphereVisualAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(SphereVisualAsset.Object);
		StaticMeshComponent->SetWorldScale3D(FVector(0.2f));
	}

	MovementComponent = CreateDefaultSubobject<UOrbitMovementComponent>(TEXT("OrbitMovement"));
	MovementComponent->UpdatedComponent = StaticMeshComponent;
}

// Called when the game starts or when spawned
void ASateliteActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASateliteActor::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();
}

// Called every frame
void ASateliteActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

