// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"


// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);
	OriginalRotation = GetActorRotation();

	GuardState = EAIState::Idle;
}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (!SeenPawn) { return; }
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Green, false, 10.0f);
	AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());	// Only work for single player.
	if (GM)
	{
		GM->CompleteMission(SeenPawn, false);
	}
	SetGuardState(EAIState::Alerted);
}

/*
 * Only call this when OnPawnSeen can't find the player.
 */
void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	if (GuardState == EAIState::Alerted) { return; }
	UE_LOG(LogTemp, Warning, TEXT("I hear you bietch"))
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Red, false, 10.0f);

	/*
	* Direction Vector which is an unit vector, because we only need the direction
	*/
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();
	
	/* Build a Rotation that only have X-axis available, the other two will still be remained, not be used and be orthonormal
	* MakeFromX(X).Rotator is equivalent to FindLookAtRotation in BP.
	* When the Guard rotate, we only want him to rotate from Z-axis (which is the yaw), so we set the other two zero.
	*/
	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;
	SetActorRotation(NewLookAt);

	/*
	* Set a timer to call the ResetOrientation function at a set interval (3.0f here)
	* Not loop because the loop variable is set to false default
	* If we create the FTimerHandle here, when there're 2 noises happen accordingly, it still return after 3s since the first noise.
	* Instead, each time we hear a new noise, we clean the old timer and reset it.
	*/
	GetWorldTimerManager().ClearTimer(TimeHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimeHandle_ResetOrientation, this, &AFPSAIGuard::ResetOrientation, 3.0f);

	SetGuardState(EAIState::Suspicious);
}

void AFPSAIGuard::ResetOrientation()
{
	if (GuardState == EAIState::Alerted) { return; }
	SetActorRotation(OriginalRotation);
	SetGuardState(EAIState::Idle);
}

void AFPSAIGuard::SetGuardState(EAIState NewState)
{
	if (GuardState == NewState)
	{
		return;
	}
	GuardState = NewState;

	OnStatedChanged(GuardState);
}


// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSAIGuard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

