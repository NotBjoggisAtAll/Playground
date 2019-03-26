// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Ghost.h"
#include "GhostPlayerWidget.h"

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

	StartLocation = GetActorLocation();
	StartRotation = GetActorRotation();
	
}

void AMyCharacter::FellOutOfWorld(const UDamageType & dmgType)
{
	SetActorLocationAndRotation(StartLocation, StartRotation); //TODO Finne ut hvorfor rotation ikke funker.
	StopRecording();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Jump();
	if (bIsRecording)
	{
		if (bIsFirstRecordedFrame)
		{
			RecordingStartTransform = GetTransform();
			bIsFirstRecordedFrame = false;
		}
		//RecordedTransforms.Add(GetTransform());
		float UsedTime = GetWorld()->GetTimerManager().GetTimerElapsed(TH_RecordingTimer);
		if (PlayerWidget)
		{
			PlayerWidget->SetProgressBarPercentage(UsedTime / MaxRecordedTime);
		}
		RecordedInputs.Add(FMovementOrder{UGameplayStatics::GetPlayerController(GetWorld(), 0)->InputComponent->GetAxisValue("MoveForward"), GetActorRotation(),GetMovementComponent()->IsFalling()});

	}
}

void AMyCharacter::StartRecording()
{
	if (!bIsRecording)
	{
		UE_LOG(LogTemp, Warning, TEXT("[MyCharacter] start Recording: Recording starts!"));

		bIsRecording = true;
		GetWorld()->GetTimerManager().SetTimer(TH_RecordingTimer, this, &AMyCharacter::StopRecording, MaxRecordedTime, false);
	}
	else
	{
		StopRecording();
		GetWorld()->GetTimerManager().ClearTimer(TH_RecordingTimer);
	}
}

void AMyCharacter::StopRecording()
{
	if (bIsRecording)
	{
		bIsFirstRecordedFrame = true;
		bIsRecording = false;
		UE_LOG(LogTemp, Warning, TEXT("[MyCharacter] Stop Recording: Recording stops!"));
		if (NewestGhost)
		{
			if (OldestGhost)
				OldestGhost->Destroy();

			OldestGhost = NewestGhost;
		}

		NewestGhost = GetWorld()->SpawnActor<AGhost>(GhostClass);
		NewestGhost->SetInitialTransform(RecordingStartTransform);

		//NewestGhost->SetTransformsToFollow(RecordedTransforms);
		NewestGhost->SetInputsToFollow(RecordedInputs);

		//RecordedTransforms.Empty();
		RecordedInputs.Empty();

		if (PlayerWidget)
			PlayerWidget->SetProgressBarPercentage(0);

		SetActorTransform(RecordingStartTransform);
	}
}

void AMyCharacter::DecrementTotalGhosts()
{
	UE_LOG(LogTemp, Warning, TEXT("[AMyCharacter] DecrementTotalGhosts: Fjerner 1"));

	auto CurrentNumberOfGhosts = PlayerWidget->GetNumberOfGhosts();
	PlayerWidget->SetNumberOfGhosts(CurrentNumberOfGhosts - 1);
}

void AMyCharacter::IncrementTotalGhosts()
{
	UE_LOG(LogTemp, Warning, TEXT("[AMyCharacter] IncrementTotalGhosts: Legger til 1"));
	int CurrentNumberOfGhosts = PlayerWidget->GetNumberOfGhosts();
	PlayerWidget->SetNumberOfGhosts(CurrentNumberOfGhosts + 1);
}

void AMyCharacter::RemoveGhosts()
{
	StopRecording();
	if (OldestGhost)
	{
		OldestGhost->Destroy();
		OldestGhost = nullptr;
	}
	if (NewestGhost)
	{
		NewestGhost->Destroy();
		NewestGhost = nullptr;
	}
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
