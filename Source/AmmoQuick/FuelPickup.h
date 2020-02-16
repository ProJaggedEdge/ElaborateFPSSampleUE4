// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FuelPickup.generated.h"

UCLASS()
class AMMOQUICK_API AFuelPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuelPickup();

	class UShapeComponent* TBox;

	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* SM_TBox;

	class AAmmoQuickCharacter* MyPlayerCharacter;

	UPROPERTY(EditAnywhere)
	float Capacity;

	UFUNCTION()
	void TriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
