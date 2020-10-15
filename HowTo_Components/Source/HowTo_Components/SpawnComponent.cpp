// Fill out your copyright notice in the Description page of Project Settings.
#include <String>
#include <Engine\ObjectLibrary.h>
#include "SpawnComponent.h"

// Sets default values for this component's properties
USpawnComponent::USpawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	ElaspedTime += DeltaTime;

	if (ElaspedTime > SpawningTime) {
		ElaspedTime = {};

		if (SpawnedComponents.Num() == SpawningCount) {
			for (auto i = 0; i < SpawnedComponents.Num(); ++i) {
				auto Component = SpawnedComponents[i];

				Component->UnregisterComponent();
				Component->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			}

			SpawnedComponents.Empty();
		}
		else {
			auto Count = std::to_wstring(SpawnedComponents.Num());
			TCHAR buffer[128] = {};
			_sntprintf_s(buffer, _countof(buffer), TEXT("Child %s"), Count.c_str());
			FName ChildName = buffer;

			// https://answers.unrealengine.com/questions/469784/when-is-valid-time-to-create-subobjectscomponents.html
			auto ChildComponent = NewObject<UStaticMeshComponent>(this);
			ChildComponent->RegisterComponent();
			ChildComponent->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);

			SpawnedComponents.Add(ChildComponent);

			// https://mnlt.tistory.com/144
			{
				UStaticMesh* StaticMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere")));

				if (StaticMesh) {
					auto Radius = StaticMesh->GetBounds().SphereRadius;

					ChildComponent->SetStaticMesh(StaticMesh);
					ChildComponent->SetWorldScale3D({ 0.5f, 0.5f, 0.5f });
					ChildComponent->SetWorldLocation({ 0.f, 0.f, 0.f });
				}
			}
		}
	}
}

