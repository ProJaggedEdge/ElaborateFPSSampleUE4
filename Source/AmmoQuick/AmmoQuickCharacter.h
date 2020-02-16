// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AmmoQuickCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class AAmmoQuickCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, just the actual gun) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* VR_Gun;

	/** Location on VR gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* VR_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* L_MotionController;

public:
	AAmmoQuickCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AAmmoQuickProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint32 bUsingMotionControllers : 1;


	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	int32 ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	int32 maxAmmo;

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	int32 clip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	int32 clipSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	float recoilRate;

	UFUNCTION()
	int32 PickupAmmo(int32 Capacity);


	UFUNCTION()
	void AutoFire();
	
	UFUNCTION()
	void StopAutoFire();

	UPROPERTY()
	float FireRate;

	UPROPERTY()
	FTimerHandle AutoFireHandle;


	UFUNCTION()
	void DoubleJump();

	UPROPERTY()
	int DoubleJumpCounter;
	// Initialised to 0 by default

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpHeight;


	UFUNCTION()
	void Warp();

	UFUNCTION()
	void StopWarp();

	UFUNCTION()
	void ResetWarp();

	UPROPERTY(EditAnywhere)
	float WarpDistance;

	UPROPERTY(EditAnywhere)
	float WarpCooldown;

	UPROPERTY()
	bool bCanWarp;

	UPROPERTY(EditAnywhere)
	float WarpStop;

	UPROPERTY()
	FTimerHandle WarpHandle;


	UFUNCTION()
	void Sprint();

	UFUNCTION()
	void Walk();

	UFUNCTION()
	bool IsPlayerMovingForward();

	UPROPERTY(EditAnywhere)
	float SprintSpeed;

	UPROPERTY(EditAnywhere)
	float WalkSpeed;

	
	UPROPERTY(EditAnywhere)
	float MaxStamina;

	UPROPERTY()
	float Stamina;

	UPROPERTY()
	bool bSprinting;

	UPROPERTY()
	float SprintStaminaRate;

	UPROPERTY(EditAnywhere)
	float SprintStaminaUsage;

	UPROPERTY()
	float StaminaRecoveryRate;

	UPROPERTY(EditAnywhere)
	float StaminaRecoveryMagnitude;

	UFUNCTION()
	void SprintingStamina();

	UFUNCTION()
	void RecoveringStamina();

	UPROPERTY()
	FTimerHandle SprintHandle;


	UPROPERTY(EditAnywhere)
	float MaxFuel;

	UPROPERTY()
	float Fuel;

	UPROPERTY(EditAnywhere)
	float WarpFuelConsumption;

	UPROPERTY(EditAnywhere)
	float DoubleJumpFuelConsumption;

protected:
	
	/** Fires a projectile. */
	void OnFire();

	/** Reloads the Gun */
	void ReloadClip();

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
	
	UFUNCTION()
	virtual void Landed(const FHitResult& Hit) override;

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	
	/** Returns Current Stamina Progress **/
	UFUNCTION(BlueprintCallable)
	float GetStaminaProgress();

	/** Returns Current Fuel Progress **/
	UFUNCTION(BlueprintCallable)
	float GetFuelProgress();

	UFUNCTION(BlueprintCallable)
	FString GetAmmoString();
};

