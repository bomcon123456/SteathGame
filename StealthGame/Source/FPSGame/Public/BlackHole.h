// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHole.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class FPSGAME_API ABlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackHole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp = nullptr;

	// This one to pull components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* OutterSphereComp = nullptr;
	// This one to destroy it
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* InnerSphereComp = nullptr;
	TArray<UPrimitiveComponent*> NearbyObject;


	UFUNCTION()	// You must have this to be called!
	void OverlapInnerSphere(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
