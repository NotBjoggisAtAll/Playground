// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "MyCharacter.h"
#include "Ghost.generated.h"

UCLASS()
class PLAYGROUND_API AGhost : public ACharacter
{
	GENERATED_BODY()
	
public:	
	AGhost();

	void SetInitialTransform(FTransform inTransforms) { InitialTransform = inTransforms; }
	void SetInputsToFollow(TArray<FMovementOrder> inInputs) { RecordedInputs = inInputs; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	AMyCharacter* ReferenceToMyCharacter = nullptr;

private:
	int MovementSpeed = 2;
	int CurrentTransform = 0;
	FTransform InitialTransform;
	TArray<FMovementOrder> RecordedInputs;
};
