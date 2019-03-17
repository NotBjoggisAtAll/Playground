// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ghost.generated.h"

UCLASS()
class PLAYGROUND_API AGhost : public AActor
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
	void SetTransform(TArray<FTransform> inTransforms) { TransformsToFollow = inTransforms; }

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* Capsule = nullptr;
private:
	int CurrentTransform = 0;
	TArray<FTransform> TransformsToFollow;

};
