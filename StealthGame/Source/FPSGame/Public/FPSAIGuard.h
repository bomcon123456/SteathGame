// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;
// If it has blueprinttype, it's must be uint8
UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,
	Suspicious,
	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;
	FRotator OriginalRotation;
	FTimerHandle TimeHandle_ResetOrientation;

	UPROPERTY(ReplicatedUsing=OnRep_GuardState)
	EAIState GuardState;

	/** This'll get called only on clients. */
	UFUNCTION()
	void OnRep_GuardState();
	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);
	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);
	UFUNCTION()
	void ResetOrientation();
	/*
	* Instead of directly change the GuardState variable, using a function
	* So that we can respond to this is BP
	*/
	void SetGuardState(EAIState NewState);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStatedChanged(EAIState NewState);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
};
