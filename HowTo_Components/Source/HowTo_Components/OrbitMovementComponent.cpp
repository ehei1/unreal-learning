// Fill out your copyright notice in the Description page of Project Settings.

#include "OrbitMovementComponent.h"


void UOrbitMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	auto Radian = FMath::DegreesToRadians(Angle);
	auto X = FMath::Sin(Radian) * Radius;
	auto Y = FMath::Cos(Radian) * Radius;

	UpdatedComponent->SetRelativeLocation({ X, Y,{} });

	Angle += DeltaTime * Speed;
}