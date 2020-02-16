// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AmmoQuickCharacter.h"
#include "FuelPickup.h"
#include "UObject/ConstructorHelpers.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFuelPickup::AFuelPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	TBox->SetGenerateOverlapEvents(true);
	TBox->SetRelativeScale3D(FVector(1.f, 1.5f, 2.f));
	TBox->OnComponentBeginOverlap.AddDynamic(this, &AFuelPickup::TriggerEnter);
	RootComponent = TBox;

	SM_TBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
	SM_TBox->SetRelativeLocation(FVector(6.29847f, 1.248687f, -31.998362f));
	SM_TBox->SetRelativeScale3D(FVector(1.f, 1.f, .6f));
	SM_TBox->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	static ConstructorHelpers::FObjectFinder<USoundCue> PickupSoundObj(TEXT("/Game/FirstPerson/Audio/FuelPickup_Cue"));
	if (PickupSoundObj.Succeeded())
	{
		TriggerSound = PickupSoundObj.Object;
	}
}

void AFuelPickup::TriggerEnter(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	MyPlayerCharacter = Cast<AAmmoQuickCharacter>(OtherActor);

	if (MyPlayerCharacter)
	{
		if (MyPlayerCharacter->PickupFuel(Capacity))
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
void AFuelPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFuelPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

