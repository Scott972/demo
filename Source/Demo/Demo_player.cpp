// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "Demo_player.h"


// Sets default values
ADemo_player::ADemo_player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0; 
	/* I DONT KNOW WHY I AM DOING THIS! Apparenntly this creates a camera and a visible object. Learn C++ AND Unreal's SDK wrapper :/ */
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurVisibleComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
}

// Called when the game starts or when spawned
void ADemo_player::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADemo_player::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	{
		float CurrentScale = OurVisibleComponent->GetComponentScale().X;
		if (bGrowing)
		{
			CurrentScale += DeltaTime;
		}
		else
		{
			CurrentScale -= (DeltaTime * 0.5f);
		}
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
		OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));
	}

	{
		if (!CurrentVelocity.IsZero())
		{
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
			SetActorLocation(NewLocation);
		}
	}

}

// Called to bind functionality to input
void ADemo_player::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("Grow", IE_Pressed, this, &ADemo_player::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &ADemo_player::StopGrowing);

	InputComponent->BindAxis("MoveX", this, &ADemo_player::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &ADemo_player::Move_YAxis);

}

void ADemo_player::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void ADemo_player::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void ADemo_player::StartGrowing()
{
	bGrowing = true;
}

void ADemo_player::StopGrowing()
{
	bGrowing = false;
}

