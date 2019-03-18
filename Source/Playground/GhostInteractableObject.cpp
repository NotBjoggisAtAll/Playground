// Fill out your copyright notice in the Description page of Project Settings.

#include "GhostInteractableObject.h"
#include "GhostButton.h"

// Sets default values
AGhostInteractableObject::AGhostInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGhostInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = GetActorLocation();
}

// Called every frame
void AGhostInteractableObject::Tick(float DeltaTime)
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

void AGhostInteractableObject::UpdateObjectPosition(FVector NewPosition)
{
	FVector NewVector = StartPosition + NewPosition;
	SetActorLocation(NewVector);
}

