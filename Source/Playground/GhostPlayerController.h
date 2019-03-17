// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GhostPlayerController.generated.h"

/**
 * 
 */

class UGhostPlayerWidget;

UCLASS()
class PLAYGROUND_API AGhostPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGhostPlayerController();

	virtual void BeginPlay() override;

	UGhostPlayerWidget* PlayerWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGhostPlayerWidget> PlayerWidgetType;

};
