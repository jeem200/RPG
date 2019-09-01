// SillikOne.


#include "BTService_UpdateChasing.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Npc_AIController.h"


UBTService_UpdateChasing::UBTService_UpdateChasing(const FObjectInitializer& ObjectInitializer)
{
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = false;
}

void UBTService_UpdateChasing::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get Blackboard
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComponent){return;}

	if (!CurrentPlayerPositionKey.IsSet())
	{
		// Retrieve Player Position and updateBlackboard
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerClass, FoundActors);
		if (FoundActors[0])
		{
			FVector PlayerLocation = FoundActors[0]->GetActorLocation();
			BlackboardComponent->SetValueAsVector(CurrentPlayerPositionKey.SelectedKeyName, PlayerLocation);
		}
	}
}

void UBTService_UpdateChasing::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Check BB and AIController
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!BlackboardComp || !AIController){	return;	}

	ANpc_AIController* ChasingController = Cast<ANpc_AIController>(AIController);
	if (!ChasingController)	{return;}

	BlackboardComp->SetValueAsBool(CanSeePlayerKey.SelectedKeyName, ChasingController->bCanSeePlayer);
	// update last known position of the player
	if (ChasingController->bCanSeePlayer != bLastCanSeePlayer)
	{
		BlackboardComp->SetValueAsVector(LastKnownPositionKey.SelectedKeyName, ChasingController->LastKnownPlayerPosition);
	}

	// update last can see Player
	bLastCanSeePlayer = ChasingController->bCanSeePlayer;

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
