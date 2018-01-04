// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	OutterSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("OutterSphereComp"));
	OutterSphereComp->SetSphereRadius(3000.0f);
	OutterSphereComp->SetupAttachment(MeshComp);

	InnerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	InnerSphereComp->SetSphereRadius(100.0f);
	InnerSphereComp->SetupAttachment(MeshComp); 

	// When component overlap -> OverlapInnerSphere called
	InnerSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapInnerSphere);
	UE_LOG(LogTemp, Warning, TEXT("LOL"))

}

void ABlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("LOL2"))
		if (OtherActor)
			OtherActor->Destroy();
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OutterSphereComp->GetOverlappingComponents(NearbyObject);

	for (int32 i = 0; i < NearbyObject.Num(); i++)
	{
		UPrimitiveComponent* PrimComp = NearbyObject[i];
		if (!PrimComp) { return; }
		auto bIsSimulating = PrimComp->IsSimulatingPhysics();
		if (bIsSimulating)
		{
			const float SphereRadius = OutterSphereComp->GetScaledSphereRadius();
			const float Strength = -2000; // To pull back

			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, Strength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}


