// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "FirstActor.generated.h"


UCLASS()
class FIRSTGAME_API AFirstActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFirstActor();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Learning about Specifies")
	float ActorLifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Learning About Specifies")
	int32 ActorLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Learning About Components")

	class UStaticMeshComponent* FirstActorMesh;

	UFUNCTION(BlueprintCallable)
	void CheckLifetime();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	
	void PrintLevel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
