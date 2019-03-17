// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHUD.h"
#include "Engine/Canvas.h"

APlayerHUD::APlayerHUD()
{

}

void APlayerHUD::DrawHUD()
{
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	Super::DrawHUD();
}
