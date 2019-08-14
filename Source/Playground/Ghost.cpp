// Fill out your copyright notice in the Description page of Project Settings.

#include "Ghost.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AGhost::AGhost()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGhost::BeginPlay()
{
	Super::BeginPlay();
	ReferenceToMyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void AGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentTransform == 0)
	{
		SetActorTransform(InitialTransform);
	}
	if (CurrentTransform < RecordedInputs.Num() - 1)
	{
		if (RecordedInputs[CurrentTransform].Jump)
			Jump();
		AddMovementInput(GetActorForwardVector(), MovementSpeed * RecordedInputs[CurrentTransform].MoveForwardValue);
		AddMovementInput(GetActorRightVector(), MovementSpeed * RecordedInputs[CurrentTransform].MoveRightValue);
		SetActorRotation(RecordedInputs[CurrentTransform].Rotation);
		CurrentTransform++;
	}
	else
		CurrentTransform = 0;
}