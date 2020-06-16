// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderMovement.h"

void UColliderMovement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//check things are valid
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	//get and clear vector from collider
	FVector DesireMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.f;

	if (!DesireMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesireMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		//if bump into something, slide
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesireMovementThisFrame, 1.f-Hit.Time,Hit.Normal,Hit);
		}
	}

}

