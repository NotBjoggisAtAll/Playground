// Fill out your copyright notice in the Description page of Project Settings.

#include "GhostPlayerWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Engine/Engine.h"
#define PrintFloat(x) { FString TheFloatStr = FString::SanitizeFloat(x); GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Red, *TheFloatStr); } 


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
	NumberOfGhosts = Value;
	PrintFloat(Value);
	GhostCounterText->SetText(FText::FromString("Number of ghosts: " + FString::FormatAsNumber(NumberOfGhosts) + "/2"));
}
