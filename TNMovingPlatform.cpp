#include "TNMovingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

ATNMovingPlatform::ATNMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = StaticMesh;
}

void ATNMovingPlatform::StartMoving()
{
	bIsMoving = true;
}

void ATNMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsMoving)
	{

		FVector Direction = SavedWayPoints[WayPointIndex] - GetActorLocation();
		Direction.Normalize();
		float SpeedB = FMath::Min(Speed, FVector::Distance(SavedWayPoints[WayPointIndex], GetActorLocation()));

		SetActorLocation(GetActorLocation() + Direction * SpeedB);

		if (FVector::PointsAreNear(SavedWayPoints[WayPointIndex], GetActorLocation(),1.f))
		{   

			if (!bInvert) 
			{
				if (WayPointIndex < SavedWayPoints.Num() - 1)
				{
					WayPointIndex++;
				}
				else 
				{
						bInvert = !bInvert;
						bIsMoving = false;
						if (bLoop)
						{
							GetWorldTimerManager().SetTimer(WaitTimer, this, &ATNMovingPlatform::StartMoving, HoldTime, false);
						}

				}
			
			}
			else
			{
				if (WayPointIndex > 0)
				{
					WayPointIndex--;
				}
				else
				{
					bInvert = !bInvert;
						bIsMoving = false;
					if (bLoop)
					{
						GetWorldTimerManager().SetTimer(WaitTimer,this, &ATNMovingPlatform::StartMoving, HoldTime, false);
					}

				}
			}

		} 
	}
}

void ATNMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	SavedWayPoints.Add(GetActorLocation());

	for (auto wp : WayPoints)
	{
		SavedWayPoints.Add(GetActorLocation() + wp);

	}
	WayPoints.Empty();

	if(bAutoStart)
		StartMoving();
	


}
