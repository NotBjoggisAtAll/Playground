// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.generated.h"

UCLASS()
class PLAYGROUND_API AInteractableObject : public AActor
{
	GENERATED_BODY()

public:
	AInteractableObject();

	UPROPERTY(VisibleAnywhere)
		USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, Category = Moveable)
		UStaticMeshComponent* MoveableMesh;

	UFUNCTION(BlueprintImplementableEvent)
		void OnButtonsPressed();
	UFUNCTION(BlueprintImplementableEvent)
		void OnButtonsReleased();

	UFUNCTION(BlueprintCallable)
		void UpdateMoveableObjectLocation(float Alpha);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TArray<class AGhostButton*> Buttons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Moveable, Meta = (MakeEditWidget = true))
		FVector EndLocation;

	UPROPERTY(BlueprintReadWrite, Category = Moveable)
		FVector PrivateStartLocation;

	UPROPERTY(BlueprintReadWrite, Category = Moveable)
		FVector PrivateEndLocation;

};
