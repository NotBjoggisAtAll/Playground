// Fill out your copyright notice in the Description page of Project Settings.

#include "GhostPlayerWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

bool UGhostPlayerWidget::Initialize()
{
	bool Success = Super::Initialize();
	RecordingProgress->SetPercent(0.0);
	SetNumberOfGhosts(0);
	return Success;
}

void UGhostPlayerWidget::SetProgressBarPercentage(float Value)
{
	RecordingProgress->SetPercent(Value);
}

void UGhostPlayerWidget::SetNumberOfGhosts(int Value)
{
	GhostCounterText->SetText(FText::FromString("Number of ghosts: " + FString::FormatAsNumber(Value) + "/2"));
}
