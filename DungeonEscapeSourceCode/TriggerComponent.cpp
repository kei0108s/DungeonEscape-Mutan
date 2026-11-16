// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

}
void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (MoverActor)
    {
        //  MoverActorからコンポーネントを探す
        Mover = MoverActor->FindComponentByClass<UMover>();
        if (Mover){
            //  見つけたらログを出す
            UE_LOG(LogTemp, Display, TEXT("Succesfully found the mover component!"));
        }
        else{
            //  見つからなかったらログを出す
            UE_LOG(LogTemp, Display, TEXT("Failed to find mover component!"));
        }
    }
    else{
        UE_LOG(LogTemp, Display, TEXT("MoverActor is nullptr"));
    }
    if (IsPressurePlate){
        //  他のアクターが重なった時のイベント
        OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
        //  他のアクターが離れた時のイベント
        OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);
    }
}
void UTriggerComponent::Trigger(bool NewTriggerValue)
{
    IsTriggered = NewTriggerValue;
    //  Moverが存在すれば呼び出す
    if (Mover){
        Mover->SetShouldMove(IsTriggered);
    }
    else{
        UE_LOG(LogTemp, Display, TEXT("%s doesn't have a mover to trigger!"), *GetOwner()->GetActorNameOrLabel());
    }
}
void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    //  踏んだアクターがプレイヤーや特定のオブジェクトかどうか
    if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator")){
        ActiovatorCount++;  //  重なってる対象のカウント

        if (!IsTriggered){
            Trigger(true);
        }
    }
}
void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    //  踏んだアクターがプレイヤーや特定のオブジェクトかどうか
    if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator"))
    {
        ActiovatorCount--;  //  重なってる対象のカウント

        if (IsTriggered && (ActiovatorCount == 0))
        {
            Trigger(false);
        }
    }
}
