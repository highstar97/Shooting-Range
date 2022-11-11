#pragma once

#include "SRWeapon.h"
#include "KA47_X.generated.h"

UCLASS()
class SHOOTING_RANGE_API AKA47_X : public ASRWeapon
{
	GENERATED_BODY()

public:
	AKA47_X();

	virtual UTexture2D* GetImage() override;
	virtual FString GetName() override;
	virtual FString GetAbility() override;
	virtual USkeletalMeshComponent* GetMesh() override;
	virtual UParticleSystem* GetMuzzleParticle() override;
	virtual USoundWave* GetAttackSound() override;

	virtual ASRBullet* ShootBullet(UWorld* World, FVector MuzzleLocation, FRotator MuzzleRotation, FActorSpawnParameters SpawnParams) override;
	virtual ASREmptyBullet* ShootEmptyBullet(UWorld* World, FVector ShellEjectLocation, FRotator ShellEjectRotation, FActorSpawnParameters SpawnParams) override;
};
