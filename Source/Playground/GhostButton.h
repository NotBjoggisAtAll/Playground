// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GhostButton.generated.h"

UCLASS()
class PLAYGROUND_API AGhostButton : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGhostButton();

	UPROPERTY(VisibleAnywhere, Category = "Trigger")
		class USphereComponent* TriggerSphere;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Button;

	UFUNCTION(BlueprintImplementableEvent)
		void PlayTimeline();

	UFUNCTION(BlueprintImplementableEvent)
		void ReverseTimeline();

	UFUNCTION(BlueprintCallable)
		void UpdateButtonPosition(FVector NewPosition);

	bool IsPressed() const { return bIsPushedDown; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void Tick(float DeltaTime) override;

	void LerpColor(float value);

	UMaterialInstanceDynamic* Material;


	// ** Variables ** //

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "C++")
		FVector StartPosition;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "C++")
		bool bIsPushedDown = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "C++")
		float ColorLerp = 0;
};
