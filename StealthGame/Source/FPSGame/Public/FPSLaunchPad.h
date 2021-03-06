// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UParticleSystem;

UCLASS()
class FPSGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchPad();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* LaunchBase = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapComp = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "LaunchPad")
	UParticleSystem* ActiveLaunchPadFX;
	/*
	* Total impulse added to the character on the overlap
	* EditInstanceOnly to allow in-level editing
	*/
	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float LaunchStrength;
	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float LaunchPitchAngle;

	UFUNCTION()
	void OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
	
};
