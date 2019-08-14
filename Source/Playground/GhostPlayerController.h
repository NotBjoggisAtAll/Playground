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
	virtual void SetupInputComponent() override;

private:

	// ** Functions ** //
	void MoveRight(float value);

	void RotateCamera(float value);

	void RemoveGhosts();

	void MoveForward(float value);

	void Jump();

	void StartRecording();

	// ** Variables ** //

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGhostPlayerWidget> PlayerWidgetType;


	class AMyCharacter* player = nullptr;

protected:

	UPROPERTY(BlueprintReadWrite)
	UGhostPlayerWidget* PlayerWidget = nullptr;
};
