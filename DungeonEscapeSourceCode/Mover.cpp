// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}
// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetOwner()->GetActorLocation();	//	初期位置を保管
	SetShouldMove(false);	//	動かない状態
}
// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector CurrentLocation = GetOwner()->GetActorLocation();	//	現在のアクターの位置を取得
	ReachedTarget = CurrentLocation.Equals(TargetLocation);		//	目的地に到達したかどうかをチェック

	//	開始位置から目標位置まで、毎フレーム少しずつ一定速度で近づいていく
	if (!ReachedTarget)
	{
		float Speed = MoveOffset.Length() / MoveTime;

		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

		GetOwner()->SetActorLocation(NewLocation);
	}
}
//	動作チェック
bool UMover::GetShouldMove()
{
	return ShouldMove;
}
void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
	//	動く状態
	if (ShouldMove)
	{
		TargetLocation = StartLocation + MoveOffset;
	}
	else //	動かない状態
	{
		TargetLocation = StartLocation;
	}
}

