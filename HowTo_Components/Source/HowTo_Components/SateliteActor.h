// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SateliteActor.generated.h"

UCLASS()
class HOWTO_COMPONENTS_API ASateliteActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASateliteActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostRegisterAllComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UOrbitMovementComponent* MovementComponent;
	class UStaticMeshComponent* StaticMeshComponent;
	class UChildActorComponent* ChildActorComponent;
};
