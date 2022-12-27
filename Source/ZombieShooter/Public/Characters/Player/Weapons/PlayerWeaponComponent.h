#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

#include "WeaponObject.h"

#include "PlayerWeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReloadEvent);

class APlayerPawn;

UCLASS(Blueprintable, ClassGroup = "Weapon System", meta = (BlueprintSpawnableComponent))
class ZOMBIESHOOTER_API UPlayerWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerWeaponComponent();

protected:
	//StartingWeapons
	UPROPERTY(Category = "Weapons|Equipped Weapons ", EditAnywhere, BlueprintReadWrite)
		TArray<UWeaponData*> StartingWeapons;

	//Equipped Weapon Data
	UPROPERTY(Replicated, Category = "Weapons|Equipped Weapons", EditInstanceOnly, BlueprintReadOnly)
		TArray<AWeaponObject*> EquippedWeapons;

	//Equipped Weapon Data
	UPROPERTY(ReplicatedUsing = OnRep_ActiveWeapon, Category = "Weapons|Equipped Weapons", EditInstanceOnly, BlueprintReadOnly)
		AWeaponObject* ActiveWeapon;

	FTimerHandle AutomaticFireTimer;

public:
	bool bIsFiring;

	UPROPERTY(BlueprintAssignable)
		FOnFireEvent OnFireEvent;
	UPROPERTY(BlueprintAssignable)
		FOnReloadEvent OnReloadEvent;

	void SpawnStartWeapons();
	AWeaponObject* SpawnWeaponObject(UWeaponData* WeaponData);

	//UFUNCTION(Client, Reliable)
	//void OnReplicatedStartWeapons();
	//void OnReplicatedStartWeapons_Implementation();

	UFUNCTION(Server, Reliable)
		void SetEquippedWeapon_Request(uint8 Index);
		void SetEquippedWeapon_Request_Implementation(uint8 Index);

	UFUNCTION()
	void OnRep_ActiveWeapon();

	UFUNCTION(Server, Reliable)
	void UpdateEquippedWeapons();
	void UpdateEquippedWeapons_Implementation();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Equip Primary Weapon"), Category = "WeaponFunctions")
		void EquipPrimaryWeapon();
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Equip Secondary Weapon"), Category = "WeaponFunctions")
		void EquipSecondaryWeapon();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Fire Weapon"), Category = "WeaponFunctions")
		void OnFire();
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Fire Weapon"), Category = "WeaponFunctions")
		void OnFireEnd();
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Reload Weapon"), Category = "WeaponFunctions")
		void OnReloadWeapon();

	void SingleFire();

	//Weapon Functionality
	UFUNCTION(Server, reliable)
		void ServerFireWeapon();
		void ServerFireWeapon_Implementation();

	UFUNCTION(Server, reliable)
		void ServerReloadWeapon();
		void ServerReloadWeapon_Implementation();

	UFUNCTION(Server, Reliable)
		void DropFirstWeaponFromInventory();
		void DropFirstWeaponFromInventory_Implementation();

	/** Returns Equipped WeaponObjects**/
	TArray<AWeaponObject*> GetEquippedWeapons() const { return EquippedWeapons;}

	/** Returns Active WeaponObject**/
	AWeaponObject* GetActiveWeapon() const { return ActiveWeapon; }

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
};


