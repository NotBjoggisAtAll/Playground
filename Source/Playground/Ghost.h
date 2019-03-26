// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "MyCharacter.h"
#include "Ghost.generated.h"


class AMyCharacter;

UCLASS()
class PLAYGROUND_API AGhost : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGhost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//void SetTransformsToFollow(TArray<FTransform> inTransforms) { TransformsToFollow = inTransforms; }
	void SetInitialTransform(FTransform inTransforms) { InitialTransform = inTransforms; }
	void SetInputsToFollow(TArray<FMovementOrder> inInputs) { RecordedInputs = inInputs; }

private:
	virtual void Destroyed() override;
	int MovementSpeed = 2;
	int CurrentTransform = 0;
	FTransform InitialTransform;
	//TArray<FTransform> TransformsToFollow;
	TArray<FMovementOrder> RecordedInputs;
	AMyCharacter* Player;

};
