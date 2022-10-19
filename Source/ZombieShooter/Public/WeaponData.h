#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MetasoundSource.h"

#include "WeaponData.generated.h"


UENUM(BlueprintType)
enum class WeaponType : uint8 {
	MELEE = 0 UMETA(DisplayName = "Melee"),
	SHOTGUN = 1  UMETA(DisplayName = "Shotgun"),
	SINGLEFIRE = 2     UMETA(DisplayName = "SingleFire"),
	BURSTFIRE = 3   UMETA(DisplayName = "BurstFire"),
	AUTOFIRE = 4     UMETA(DisplayName = "AutomaticFire")
};

/**
 *
 */
UCLASS(BlueprintType)
class UWeaponData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* WeaponModel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform FP_Model_Transform;

	UPROPERTY(Category = "Ammo", EditAnywhere, BlueprintReadWrite)
		uint8 Weapon_Default_MagazineSize;

	UPROPERTY(Category = "Ammo", EditAnywhere, BlueprintReadWrite)
		uint8 Weapon_Default_MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		WeaponType WeaponBehaviour;

	UPROPERTY(Category = "Visuals|VFX", EditAnywhere, BlueprintReadWrite)
		UStaticMesh* MuzzleFlash_VFX;
	UPROPERTY(Category = "Visuals|Audio", EditAnywhere, BlueprintReadWrite)
		UMetaSoundSource* ShotAudio;
	UPROPERTY(Category = "Visuals|Audio", EditAnywhere, BlueprintReadWrite)
		UMetaSoundSource* ReloadAudio;
};