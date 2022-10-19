// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWeapon.h"
#include "Components\BoxComponent.h"
#include "MyCharacter.h"

// Sets default values
AMyWeapon::AMyWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

		static ConstructorHelpers::FObjectFinder<UStaticMesh> sw(TEXT("StaticMesh'/Game/ParagonGreystone/FX/Meshes/Heroes/Greystone/SM_Greystone_Blade_01.SM_Greystone_Blade_01'"));
	if (sw.Succeeded())
	{
		Weapon->SetStaticMesh(sw.Object);
	}

	Weapon -> SetupAttachment(RootComponent);

	Trigger -> SetupAttachment(Weapon);


	Weapon->SetCollisionProfileName(TEXT("MyCollectible"));
	Trigger->SetCollisionProfileName(TEXT("MyCollectible"));
	Trigger->SetBoxExtent(FVector(30.f,30.f,30.f));

}

// Called when the game starts or when spawned
void AMyWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void AMyWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger -> OnComponentBeginOverlap.AddDynamic(this, &AMyWeapon::OnCharacterBeginoverlap);
}

void AMyWeapon::OnCharacterBeginoverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Log,TEXT("Overlapped"));

	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);

	if (MyCharacter)
	{
		FName WeaponSocket(TEXT("hand_L_Socket"));
		AttachToComponent(MyCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
	}
}
