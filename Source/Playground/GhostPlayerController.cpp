// Fill out your copyright notice in the Description page of Project Settings.

#include "GhostPlayerController.h"
#include "GhostPlayerWidget.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"

AGhostPlayerController::AGhostPlayerController() {}

void AGhostPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PlayerWidget = CreateWidget<UGhostPlayerWidget>(this, PlayerWidgetType);

	PlayerWidget->AddToViewport();

	AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (player)
	{
		player->SetPlayerWidget(PlayerWidget);
	}
	
	SetInputMode(FInputModeGameOnly());
}
