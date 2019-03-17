// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class PLAYGROUND_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
public:
	APlayerHUD();
	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;
};
