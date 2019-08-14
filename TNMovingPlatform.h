#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TNMovingPlatform.generated.h"

class UStaticMeshComponent;

UCLASS()
class TN_API ATNMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:
	ATNMovingPlatform();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (MakeEditWidget = true))
	TArray<FVector> WayPoints;

	UFUNCTION(BlueprintCallable)
	void StartMoving();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAutoStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bLoop;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bInvert;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HoldTime = 1.f;


protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	
	FTimerHandle WaitTimer;

	//Där vi är i arrayen
	int WayPointIndex;

	bool bIsMoving;

	TArray<FVector> SavedWayPoints;

};
