

#include "CustomComponents/SGWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"

USGWeaponComponent::USGWeaponComponent()
{

	PrimaryComponentTick.bCanEverTick = false;


}

void USGWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void USGWeaponComponent::SpawnWeapon()
{
	if (!GetWorld())
		return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	CurrentWeapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
	if (!CurrentWeapon)
		return;

	FAttachmentTransformRules AttachmentRule(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRule, WeaponAttachPointName);
	CurrentWeapon->SetOwner(Character);
}


void USGWeaponComponent::StartFire()
{
	if (!CurrentWeapon)
		return;
	CurrentWeapon->StartFire();
}

void USGWeaponComponent::StopFire()
{
	if (!CurrentWeapon)
		return;
	CurrentWeapon->StopFire();
}