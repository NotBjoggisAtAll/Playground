// Fill out your copyright notice in the Description page of Project Settings.

#include "GhostInteractableObject.h"
#include "GhostButton.h"
#include "Components/StaticMeshComponent.h"

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


}

void AGhostInteractableObject::UpdateObjectPosition(UStaticMeshComponent* Mesh, FVector NewPosition)
{
	if (!Mesh) { return; }
	FVector NewVector = StartPosition + NewPosition;
	Mesh->SetWorldLocation(NewPosition);
}

