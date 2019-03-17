// Fill out your copyright notice in the Description page of Project Settings.

#include "Ghost.h"
#include "Components/CapsuleComponent.h"
// Sets default values
AGhost::AGhost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	SetRootComponent(Capsule);
}

// Called when the game starts or when spawned
void AGhost::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentTransform < TransformsToFollow.Num() - 1)
	{
		SetActorTransform(TransformsToFollow[CurrentTransform]);
		CurrentTransform++;
	}
	else
		CurrentTransform = 0;

}

