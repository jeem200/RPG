// SillikOne.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AI/Dialogues/DialogueComponent.h"
#include "GossipZone.generated.h"

UCLASS()
class HS_API AGossipZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGossipZone();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogues")
	struct FDialogues_Struct DialogueInfo;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogues")
		class USphereComponent* SphereComponent;

	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void OnOverlapDialogueBegin(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult);
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void OnOverlapDialogueEnd(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
