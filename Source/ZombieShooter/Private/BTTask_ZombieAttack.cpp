


#include "BTTask_ZombieAttack.h"


UBTTask_ZombieAttack::UBTTask_ZombieAttack()
{
	bNotifyTick = false;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;
	NodeName = TEXT("Zombie Attack Task");
}

EBTNodeResult::Type UBTTask_ZombieAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!UKismetSystemLibrary::IsServer(GetWorld()))
		return EBTNodeResult::Aborted;

	AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());
	if (AZombiePawn* ZombieOwner = Cast<AZombiePawn>(AIController->GetPawn())) {
		ZombieOwner->MC_OnZombieAttack();
		return EBTNodeResult::Succeeded;
	}
	else {
		return EBTNodeResult::Failed;
	}
}




