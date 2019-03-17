// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GhostPlayerWidget.generated.h"


/**
 * 
 */
UCLASS()
class PLAYGROUND_API UGhostPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	void SetProgressBarPercentage(float Value);
	void SetNumberOfGhosts(int Value);
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* RecordingProgress;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GhostCounterText;
private:

};
