// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "OrbitMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class HOWTO_COMPONENTS_API UOrbitMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float Angle = {};

	UPROPERTY(EditAnywhere)
		float Radius = 100.f;

	UPROPERTY(EditAnywhere)
		float Speed = 50.f;
};
