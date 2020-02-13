// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AmmoQuickProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h" 
#include "Particles/ParticleSystemComponent.h" 
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"

AAmmoQuickProjectile::AAmmoQuickProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AAmmoQuickProjectile::OnHit);		// set up a notification for when this component hits something blocking
	//CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AAmmoQuickProjectile::OnTrigger);

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	// Set the Explosion Particles
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionParticleObj(TEXT("/Game/StarterContent/Particles/P_Explosion"));
	if (ExplosionParticleObj.Succeeded())
	{
		ExplosionParticles = ExplosionParticleObj.Object;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("No Particles")));
	}

	// Set the Explosion Sound
	static ConstructorHelpers::FObjectFinder<USoundCue> ExplosionSoundObj(TEXT("/Game/StarterContent/Audio/Explosion_Cue"));
	if (ExplosionSoundObj.Succeeded())
	{
		ExplosionSound = ExplosionSoundObj.Object;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("No Sound")));
	}
}

void AAmmoQuickProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//void AAmmoQuickProjectile::OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		UWorld* world = GetWorld();

		if (ExplosionParticles)
		{
			UParticleSystemComponent* Explosion = UGameplayStatics::SpawnEmitterAtLocation(world, ExplosionParticles, GetActorTransform());
			Explosion->SetRelativeScale3D(FVector(4.f, 4.f, 4.f));
		}

		if (ExplosionSound)
		{
			UGameplayStatics::PlaySoundAtLocation(world, ExplosionSound, GetActorLocation());
		}

		TArray<FHitResult> HitActors;

		FVector StartTrace = GetActorLocation();
		FVector EndTrace = StartTrace;
		EndTrace.Z += 300.f;

		FCollisionShape CollisionShape;
		CollisionShape.ShapeType = ECollisionShape::Sphere;
		CollisionShape.SetSphere(Radius);

		if (GetWorld()->SweepMultiByChannel(HitActors, StartTrace, EndTrace, FQuat::FQuat(), ECC_WorldStatic, CollisionShape))
		{
			for (auto Actors = HitActors.CreateIterator(); Actors; Actors++)
			{
				UStaticMeshComponent* SM = Cast<UStaticMeshComponent>((*Actors).Actor->GetRootComponent());

				if (SM)
				{
					SM->AddRadialImpulse(GetActorLocation(), 1000.f, 5000.f, ERadialImpulseFalloff::RIF_Linear, true);
				}
			}
		}

		Destroy();
	}
}