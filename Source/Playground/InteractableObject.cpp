// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GhostButton.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComponent;
	MoveableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Moveable Object"));
	MoveableMesh->SetupAttachment(SceneComponent);
}

void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();

	PrivateStartLocation = MoveableMesh->GetComponentLocation();

	PrivateEndLocation = PrivateStartLocation + EndLocation;
}

void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool AllButtonsPressed = true;
	for (auto& b : Buttons)
	{
		if (!b->IsPressed())
		{
			AllButtonsPressed = false;
		}
	}
	if (AllButtonsPressed)
		OnButtonsPressed();
	else
		OnButtonsReleased();
}

void AInteractableObject::UpdateMoveableObjectLocation(float Alpha)
{
	auto NewLocation = FMath::Lerp(PrivateStartLocation, PrivateEndLocation, FMath::Clamp<float>(Alpha, 0,1));

	MoveableMesh->SetWorldLocation(NewLocation);
}