// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AmmoQuickCharacter.h"
#include "Pickup.h"
#include "UObject/ConstructorHelpers.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	TBox->SetGenerateOverlapEvents(true);
	TBox->SetRelativeScale3D(FVector(.75f, .75f, .2f));
	TBox->OnComponentBeginOverlap.AddDynamic(this, &APickup::TriggerEnter);
	RootComponent = TBox;

	SM_TBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
	SM_TBox->SetRelativeLocation(FVector(-19.029924f, -23.391632f, -30.001059f));
	SM_TBox->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	static ConstructorHelpers::FObjectFinder<USoundCue> PickupSoundObj(TEXT("/Game/FirstPerson/Audio/AmmoPickup_Cue"));
	if (PickupSoundObj.Succeeded())
	{
		TriggerSound = PickupSoundObj.Object;
	}
}

void APickup::TriggerEnter(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	MyPlayerCharacter = Cast<AAmmoQuickCharacter>(OtherActor);

	if (MyPlayerCharacter)
	{
		if (MyPlayerCharacter->PickupAmmo(Capacity))
		{
			if (TriggerSound)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), TriggerSound, GetActorLocation());
			}
			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

