// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UGhostPlayerWidget;

UCLASS()
class PLAYGROUND_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void FellOutOfWorld(const class UDamageType & dmgType) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGhost> GhostClass;
	
	void SetPlayerWidget(UGhostPlayerWidget* widgetIn) { PlayerWidget = widgetIn; }
private:
	// ** Functions ** //

	void StartRecording();
	void StopRecording();
	void RemoveGhosts();

	void MoveForward(float value);
	void MoveRight(float value);
	void RotateCamera(float value); 

	class AGhost* NewestGhost = nullptr;
	class AGhost* OldestGhost = nullptr;
	TArray<FTransform> RecordedTransforms;
	FTimerHandle TH_RecordingTimer;


	// ** Variables ** //

	FVector StartLocation;
	FRotator StartRotation;

	float MovementSpeed = 2;
	float MaxRecordedTime = 10.f;
	int MaxNumOfGhosts = 3;

	bool bIsRecording = false;
	UGhostPlayerWidget* PlayerWidget;



};
