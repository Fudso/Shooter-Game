// Fill out your copyright notice in the Description page of Project Settings.


#include "SGGameModeBase.h"

#include "Player/SGBaseCharacter.h"
#include "Player/SGPlayerController.h"
#include "UI/SGGameHUD.h"
#include "AI/STUAIController.h"
#include "Player/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameModeBase, All, All);

ASGGameModeBase::ASGGameModeBase()
{
	DefaultPawnClass = ASGBaseCharacter::StaticClass();
	PlayerControllerClass = ASGPlayerController::StaticClass();
	HUDClass = ASGGameHUD::StaticClass();
	PlayerStateClass = ASTUPlayerState::StaticClass();
}

void ASGGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	CreateTeamsInfo();

	CurrentRound = 1;
	StartRound();
}

UClass* ASGGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASGGameModeBase::SpawnBots()
{
	if (!GetWorld())
		return;

	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto STUAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(STUAIController);
	}
}

void ASGGameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASGGameModeBase::GameTimerUpdate, 1.0f, true);
}

void ASGGameModeBase::GameTimerUpdate()
{
	UE_LOG(LogSTUGameModeBase, Display, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum);

	if (--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			UE_LOG(LogSTUGameModeBase, Display, TEXT("======== GAME OVER ========"));
			LogPlayerInfo();
		}
	}
}

void ASGGameModeBase::ResetPlayers()
{
	if (!GetWorld())
		return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void ASGGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void ASGGameModeBase::CreateTeamsInfo()
{
	if (!GetWorld())
		return;

	int32 TeamID = 1;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller)
			continue;

		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (!PlayerState)
			continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		SetPlayerColor(Controller);

		TeamID = TeamID == 1 ? 2 : 1;
	}
}

FLinearColor ASGGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
	if (TeamID - 1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID - 1];
	}
	UE_LOG(LogSTUGameModeBase, Warning, TEXT("No color for team id: %i, set to default: %s"), TeamID,
		*GameData.DefaultTeamColor.ToString());
	return GameData.DefaultTeamColor;
}

void ASGGameModeBase::SetPlayerColor(AController* Controller)
{
	if (!Controller)
		return;

	const auto Character = Cast<ASGBaseCharacter>(Controller->GetPawn());
	if (!Character)
		return;

	const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
	if (!PlayerState)
		return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ASGGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
	const auto KillerPlayerState = KillerController ? Cast<ASTUPlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState = VictimController ? Cast<ASTUPlayerState>(VictimController->PlayerState) : nullptr;

	if (KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}

	if (VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}
}

void ASGGameModeBase::LogPlayerInfo()
{
	if (!GetWorld())
		return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller)
			continue;

		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (!PlayerState)
			continue;

		PlayerState->LogInfo();
	}
}