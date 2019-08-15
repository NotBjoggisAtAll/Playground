// Fill out your copyright notice in the Description page of Project Settings.

#include "GhostPlayerController.h"
#include "GhostPlayerWidget.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

AGhostPlayerController::AGhostPlayerController() {}

void AGhostPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PlayerWidget = CreateWidget<UGhostPlayerWidget>(this, PlayerWidgetType);
	PlayerWidget->AddToViewport();

	ReferenceToPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (ReferenceToPlayer)
	{
		ReferenceToPlayer->SetPlayerWidget(PlayerWidget);
	}
	
	SetInputMode(FInputModeGameOnly());
}

void AGhostPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UE_LOG(LogTemp, Warning, TEXT("[AGhostPlayerController] SetupInputComponent: Setting up input!"));

	InputComponent->BindAxis("MoveForward", this, &AGhostPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AGhostPlayerController::MoveRight);
	InputComponent->BindAxis("RotateCamera", this, &AGhostPlayerController::RotateCamera);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AGhostPlayerController::Jump);
	InputComponent->BindAction("StartRecording", IE_Pressed, this, &AGhostPlayerController::StartRecording);
	InputComponent->BindAction("RemoveGhosts", IE_Pressed, this, &AGhostPlayerController::RemoveGhosts);

}

void AGhostPlayerController::MoveRight(float value)
{
	ReferenceToPlayer->MoveRight(value);
}

void AGhostPlayerController::RotateCamera(float value)
{
	ReferenceToPlayer->RotateCamera(value);
}

void AGhostPlayerController::RemoveGhosts()
{
	ReferenceToPlayer->RemoveGhosts();
}

void AGhostPlayerController::MoveForward(float value)
{
	ReferenceToPlayer->MoveForward(value);
}
void AGhostPlayerController::Jump()
{
	ReferenceToPlayer->Jump();
}

void AGhostPlayerController::StartRecording()
{
	ReferenceToPlayer->StartRecording();
}