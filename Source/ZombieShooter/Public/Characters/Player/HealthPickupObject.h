// Project 'Zombie Shooter' -Tim Peeters 2022/23

#pragma once

#include "CoreMinimal.h"
#include "Interaction/GenericInteractionActor.h"
#include "HealthPickupObject.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESHOOTER_API AHealthPickupObject : public AGenericInteractionActor
{
	GENERATED_BODY()

private:
	AHealthPickupObject();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Visuals", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float HealthToAdd = 50;

	/** Returns Current StaticMesh **/
	class UStaticMeshComponent* GetMesh() { return Mesh; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AmmoPoint")
		void AddHealthToActor(AActor* ActorToAdd);
	void AddHealthToActor_Implementation(AActor* ActorToAdd);

	virtual void OnStartInteract_BP_Implementation(AActor* InstigatingActor) override;

	virtual void StartHover_BP_Implementation(AActor* InstigatingActor) override;
	virtual void StopHover_BP_Implementation(AActor* InstigatingActor) override;

};