// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (CameraDatas.Num()) {
        auto CameraIndex = CurrentCameraIndex % CameraDatas.Num();
        auto& CameraData = CameraDatas[CameraIndex];

        TimeToNextCameraChange -= DeltaTime;

        if (TimeToNextCameraChange <= 0.0f) {
            TimeToNextCameraChange = CameraData.TimeBetweenCameraChanges;

            if (APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0)) {
                if ((OurPlayerController->GetViewTarget() != CameraData.Camera) && CameraData.Camera != nullptr) {
                    OurPlayerController->SetViewTargetWithBlend(CameraData.Camera, CameraData.SmoothBlendTime);

                    ++CurrentCameraIndex;
                }
            }
        }
    }
}

