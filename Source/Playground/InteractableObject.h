// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "InteractableObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpen);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClosed);


UCLASS()
class PLAYGROUND_API AInteractableObject : public AActor
{
	GENERATED_BODY()

public:
	AInteractableObject();

	UPROPERTY(VisibleAnywhere)
		USceneComponent* SceneComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = Moveable)
		UStaticMeshComponent* MoveableMesh;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Test")
		FOnOpen OnOpenDelegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Test")
		FOnClosed OnClosedDelegate;
	
	UFUNCTION(BlueprintImplementableEvent)
		void OnButtonsPressed();

	UFUNCTION(BlueprintImplementableEvent)
		void OnButtonsReleased();

	UFUNCTION()
		void Open();

	UFUNCTION()
		void Closed();


	UFUNCTION(BlueprintCallable)
		void UpdateMoveableObjectLocation(float Alpha);

	UFUNCTION(BlueprintCallable)
		void TimelineFinished(ETimelineDirection::Type Direction);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Settings)
		TArray<class AGhostButton*> Buttons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, Meta = (MakeEditWidget = true))
		FVector EndLocation;

	UPROPERTY(BlueprintReadWrite, Category = Settings)
		FVector PrivateStartLocation;

	UPROPERTY(BlueprintReadWrite, Category = Settings)
		FVector PrivateEndLocation;


private:

	bool bOpen = false;
	bool bClose = true;
};
