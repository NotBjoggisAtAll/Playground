// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GhostInteractableObject.generated.h"

UCLASS()
class PLAYGROUND_API AGhostInteractableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGhostInteractableObject();

	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonsPressed();
	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonsReleased();

	UFUNCTION(BlueprintCallable)
	void UpdateObjectPosition(FVector NewPosition);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ** Variables ** //

	UPROPERTY(EditAnywhere)
	TArray<class AGhostButton*> Buttons;

private:
	FVector StartPosition;

};
