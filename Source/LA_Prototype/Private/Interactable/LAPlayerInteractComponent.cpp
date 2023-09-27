// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/LAPlayerInteractComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interactable/LAInteractableInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ULAPlayerInteractComponent::ULAPlayerInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	InitBoxExtent(FVector(50.f, 100.f, 100.f));
	SetWorldLocation(FVector(50.f,0.f,0.f));
}

void ULAPlayerInteractComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OnComponentBeginOverlap.AddDynamic(this, &ULAPlayerInteractComponent::OnBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &ULAPlayerInteractComponent::OnEndOverlap);
}

void ULAPlayerInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetClosestOverlappingActor(OverlappingActorsMap);
	ALAInteractableVisualizer* const ClosestActorVisualizer = OverlappingActorsMap.FindRef(ClosestOverlappingActor);
	if(ClosestActorVisualizer)
	{
		if (!ClosestActorVisualizer->bHighlighted)
		{
			ClosestActorVisualizer->OnHighlighted(GetOwner());
		}
	}

	for (const auto &Key : OverlappingActorsMap)
	{
		if (Key.Value && Key.Value != ClosestActorVisualizer && Key.Value->bHighlighted)
		{
			Key.Value->OnUnHighlighted(GetOwner());
		}
	}
}

void ULAPlayerInteractComponent::InteractWithActor()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("InteractFunction called"));

	if (ClosestOverlappingActor)
	{
		ILAInteractableInterface::Execute_Interact(ClosestOverlappingActor);
		ClosestOverlappingActor = nullptr;
	}
}

void ULAPlayerInteractComponent::GetClosestOverlappingActor(TMap<AActor*, ALAInteractableVisualizer*> ActorsMap)
{
	if (ActorsMap.Num() > 0)
	{
		float InitialDistanceToOverlappingActor = 0;
		
		for (const TTuple<AActor*, ALAInteractableVisualizer*> OverlappingActor : OverlappingActorsMap)
		{
			const float OverlappingActorDotProduct = FVector::DotProduct(
				UKismetMathLibrary::GetForwardVector(GetOwner()->FindComponentByClass<UCameraComponent>()->GetComponentRotation()),
				OverlappingActor.Key->GetActorLocation() - GetOwner()->FindComponentByClass<UCameraComponent>()->GetComponentLocation());
			
			if (OverlappingActorDotProduct > InitialDistanceToOverlappingActor)
			{
				ClosestOverlappingActor = OverlappingActor.Key;
				InitialDistanceToOverlappingActor = OverlappingActorDotProduct;
			}
		}
	}
}

void ULAPlayerInteractComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->GetClass()->ImplementsInterface(ULAInteractableInterface::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("Implements interface"));
		auto const Visualizer = GetWorld()->SpawnActor<ALAInteractableVisualizer>(
			InteractableVisualizerClass,
		 	OtherActor->GetActorLocation(),
		 	OtherActor->GetActorRotation()
		 	);

		OverlappingActorsMap.Add(OtherActor, Visualizer);
	}
}

void ULAPlayerInteractComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (auto const Actor = OverlappingActorsMap.FindRef(OtherActor))
	{
		OverlappingActorsMap.Remove(OtherActor);
		Actor->Destroy();
	}
}
