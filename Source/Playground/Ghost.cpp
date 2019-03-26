// Fill out your copyright notice in the Description page of Project Settings.

#include "Ghost.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "MyCharacter.h"
// Sets default values
AGhost::AGhost()
{
	PrimaryActorTick.bCanEverTick = true;
	//SpawnDefaultController();
	//GetCharacterMovementComponent()->bRunPhysicsWithNoController = true;
}

// Called when the game starts or when spawned
void AGhost::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	
	if (Player)
		Player->IncrementTotalGhosts();
}
	


// Called every frame
void AGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentTransform == 0)
	{ 
		//UE_LOG(LogTemp, Warning, TEXT("[AGhost] Tick: Setting initial Transform"));
		SetActorTransform(InitialTransform);
	}
	if (CurrentTransform < RecordedInputs.Num() - 1)
	{
		//UE_LOG(LogTemp, Warning, TEXT("[AGhost] Tick: Setting input! %f"), RecordedInputs[CurrentTransform].MoveForwardValue);
		//SetActorTransform(TransformsToFollow[CurrentTransform]);
		//UE_LOG(LogTemp, Warning, TEXT("[AGhost] Tick: Adding input"));
		if (RecordedInputs[CurrentTransform].Jump)
			Jump();
		AddMovementInput(GetActorForwardVector(), MovementSpeed * RecordedInputs[CurrentTransform].MoveForwardValue);
		SetActorRotation(RecordedInputs[CurrentTransform].Rotation);
		CurrentTransform++;
	}
	else
		CurrentTransform = 0;
	//UE_LOG(LogTemp, Warning, TEXT("[AGhost] Tick: input length" %f), );


}

void AGhost::Destroyed()
{
	if (Player)
		Player->DecrementTotalGhosts();
}
