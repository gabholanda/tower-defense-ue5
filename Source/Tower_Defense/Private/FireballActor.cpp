#include "FireballActor.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "HealthComponent.h"

AFireballActor::AFireballActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));
	RootComponent = CollisionComponent;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->InitialSpeed = 500.0f;
	MovementComponent->MaxSpeed = 2500.0f;

	CollisionComponent->OnComponentHit.AddDynamic(this, &AFireballActor::OnHit);
}

void AFireballActor::BeginPlay()
{
	Super::BeginPlay();
}

void AFireballActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFireballActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		UHealthComponent* HealthComponent = OtherActor->GetComponentByClass<UHealthComponent>();
		if (HealthComponent)
		{
			HealthComponent->ReceiveDamage(Damage);
		}
		Destroy();
	}
}
