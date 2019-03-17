// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"

#include "Ghost.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsRecording)
		RecordedTransforms.Add(GetTransform());
	//else if (RecordedTransforms.Num() > 0)
	//	SetActorTransform(RecordedTransforms[0]);
	//else
	//{ }
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("RotateCamera", this, &AMyCharacter::RotateCamera);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction("StartRecording", IE_Pressed, this, &AMyCharacter::StartRecording);
}

void AMyCharacter::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), MovementSpeed * value);
}

void AMyCharacter::MoveRight(float value)
{
	
	AddControllerYawInput(value);
}

void AMyCharacter::RotateCamera(float value)
{
	SpringArm->AddRelativeRotation(FRotator(0, value, 0));
}

void AMyCharacter::StartRecording()
{
	if (!bIsRecording)
	{
		bIsRecording = true;
		GetWorld()->GetTimerManager().SetTimer(TH_RecordingTimer, this, &AMyCharacter::StopRecording, MaxRecordedTime, false);
		UE_LOG(LogTemp, Warning, TEXT("[MyCharacter] Start Recording: Recording starts!"));
	}
	else
	{
		StopRecording();
	}
}

void AMyCharacter::StopRecording()
{
	if (bIsRecording)
	{
		bIsRecording = false;
		UE_LOG(LogTemp, Warning, TEXT("[MyCharacter] Stop Recording: Recording stops!"));
		AGhost* NewGhost = GetWorld()->SpawnActor<AGhost>(GhostClass);
		NewGhost->SetTransform(RecordedTransforms);
		RecordedTransforms.Empty();
	}
}

