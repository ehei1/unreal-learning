// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Array.h"
#include "CameraDirector.generated.h"


USTRUCT(BlueprintType)
struct FCameraData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		AActor* Camera;

	UPROPERTY(EditAnywhere)
		float SmoothBlendTime;

	UPROPERTY(EditAnywhere)
		float TimeBetweenCameraChanges;
};

UCLASS()
class HOWTO_AUTOCAMERA_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TArray<FCameraData> CameraDatas;

	int32 CurrentCameraIndex{};
	float TimeToNextCameraChange;
};
