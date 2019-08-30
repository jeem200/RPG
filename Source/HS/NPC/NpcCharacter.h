// SillikOne.

#pragma once

#include "CoreMinimal.h"
#include "HSCharacter.h"
#include "Perception/AIPerceptionTypes.h"
#include "NpcCharacter.generated.h"

/**
 * 
 */
UCLASS()
class HS_API ANpcCharacter : public AHSCharacter
{
	GENERATED_BODY()

	ANpcCharacter();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	class UBehaviorTree* BehaviorTree;

protected:
	virtual void BeginPlay()override;

};