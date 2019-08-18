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

	OnOpenDelegate.AddDynamic(this, &AInteractableObject::Open);
	OnClosedDelegate.AddDynamic(this, &AInteractableObject::Closed);
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
	else if (!AllButtonsPressed)
		OnButtonsReleased();
}

void AInteractableObject::Open()
{
	UE_LOG(LogTemp, Warning, TEXT("IS OPEN"));
}

void AInteractableObject::Closed()
{
	UE_LOG(LogTemp, Warning, TEXT("IS CLOSE"));
}

void AInteractableObject::UpdateMoveableObjectLocation(float Alpha)
{
	auto NewLocation = FMath::Lerp(PrivateStartLocation, PrivateEndLocation, FMath::Clamp<float>(Alpha, 0, 1));

	MoveableMesh->SetWorldLocation(NewLocation);
}

void AInteractableObject::TimelineFinished(ETimelineDirection::Type Direction)
{
	switch (Direction)
	{
	case ETimelineDirection::Forward:
		if (!bOpen)
		{
			bOpen = true;
			OnOpenDelegate.Broadcast();

			bClose = false;
		}
		break;
	case ETimelineDirection::Backward:
		if (!bClose)
		{
			bClose = true;
			OnClosedDelegate.Broadcast();
			bOpen = false;
		}
		break;
	}
}
