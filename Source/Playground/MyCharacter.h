// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Queue.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UGhostPlayerWidget;

USTRUCT()
struct FMovementOrder
{
	GENERATED_BODY()

	UPROPERTY()
	float MoveForwardValue;

	UPROPERTY()
	float MoveRightValue;

	UPROPERTY()
	FRotator Rotation;

	UPROPERTY()
	bool Jump = false;
};

UCLASS()
class PLAYGROUND_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AMyCharacter();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGhost> GhostClass;

	void SetPlayerWidget(UGhostPlayerWidget* widgetIn) { PlayerWidget = widgetIn; }
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	void StartRecording();
	void RemoveGhosts();

	void MoveForward(float value);
	void MoveRight(float value);
	void RotateCamera(float value);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void FellOutOfWorld(const class UDamageType & dmgType) override;

private:
	// ** Functions ** //
	void StopRecording();

	void IncrementNumberOfGhosts();

	void DecrementNumberOfGhosts();

	void ResetGhostsQueue();


	// ** Variables ** //

	TQueue<AGhost*> Ghosts;
	// Keeps track of the current amount of ghosts. Can be changed outside if the player class
	int GhostsQueueSize = 0;

	TArray<FMovementOrder> RecordedInputs;
	FTimerHandle TH_RecordingTimer;

	FVector StartLocation;
	FRotator StartRotation;

	FTransform RecordingStartTransform;
	bool bIsFirstRecordedFrame = true;

	float MovementSpeed = 2;
	float MaxRecordedTime = 10.f;
	int MaxNumOfGhosts = 3;

	bool bIsRecording = false;
	UGhostPlayerWidget* PlayerWidget = nullptr;
};
