// Fill out your copyright notice in the Description page of Project Settings.


#include "Lock.h"

// Sets default values
ALock::ALock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(RootComp);

	TriggerComp = CreateDefaultSubobject<UTriggerComponent>(TEXT("Trigger Comp"));
	TriggerComp->SetupAttachment(RootComp);

	KeyItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key Item Mesh"));
	KeyItemMesh->SetupAttachment(RootComp);

	Tags.Add("Lock");
}

// Called when the game starts or when spawned
void ALock::BeginPlay()
{
	Super::BeginPlay();
	//	Œ®‚ªŠ|‚©‚Á‚Ä‚È‚¢Ý’è
	SetIsKeyPlaced(false);
}

void ALock::SetIsKeyPlaced(bool NewIsKeyPlaced)
{
	//	Žh‚³‚Á‚Ä‚¢‚é‚©XV
	IsKeyPlaced = NewIsKeyPlaced;

	TriggerComp->Trigger(NewIsKeyPlaced);	//	Trigger‚ð‹N“®
	KeyItemMesh->SetVisibility(NewIsKeyPlaced);	//	Œ©‚½–Ú‚ð•\Ž¦
}

bool ALock::GetIsKeyPlaced()
{
	return IsKeyPlaced;
}

