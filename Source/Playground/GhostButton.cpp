// Fill out your copyright notice in the Description page of Project Settings.

#include "GhostButton.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Engine.h"


#define PrintFloat(x) { FString TheFloatStr = FString::SanitizeFloat(x); GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Red, *TheFloatStr);; }

// Sets default values
AGhostButton::AGhostButton()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));

	RootComponent = TriggerSphere;
	TriggerSphere->SetSphereRadius(45);

	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AGhostButton::OnOverlapBegin);
	TriggerSphere->OnComponentEndOverlap.AddDynamic(this, &AGhostButton::OnOverlapEnd);

	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	Button->SetupAttachment(TriggerSphere);
	Button->SetRelativeScale3D(FVector(1, 1, 0.2f));

}

void AGhostButton::BeginPlay()
{
	Super::BeginPlay();

	Material = Button->CreateDynamicMaterialInstance(0);

	StartPosition = GetActorLocation();

}

void AGhostButton::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	PlayTimeline();
}

void AGhostButton::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	TSet<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	if (OverlappingActors.Num() != 0)
		return;

	ReverseTimeline();
}

// Tick is disabled. You can turn it on in the constructor if needed. 
void AGhostButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGhostButton::UpdateButtonPosition(FVector NewPosition)
{
	FVector NewVector = StartPosition + NewPosition;
	SetActorLocation(NewVector);
	LerpColor(NewPosition.Z);
}

void AGhostButton::LerpColor(float value)
{
	if (Material)
	{
		ColorLerp = (value - (0)) / (-19.f - 0); // TODO Finne en bedre løsning der -19 ikke er hardkodet
		Material->SetScalarParameterValue(FName("ButtonPushed"), ColorLerp);
	}
}

