#include "SRPlayerController.h"
#include "Shooting_RangeGameModeBase.h"
#include "SRPlayerState.h"
#include "HUDWidget.h"
#include "SRGamePlayWidget.h"
#include "SRCheckRankWidget.h"
#include "SRRankingWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

ASRPlayerController::ASRPlayerController()
{
	static ConstructorHelpers::FClassFinder<UHUDWidget> UI_HUD_C(TEXT("/Game/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}
	
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUDDY_C(TEXT("/Game/Blueprints/Huddy_BP.Huddy_BP_C"));
	if (UI_HUDDY_C.Succeeded())
	{
		HuddyWidgetClass = UI_HUDDY_C.Class;
	}

	static ConstructorHelpers::FClassFinder<USRGamePlayWidget> UI_PAUSE_C(TEXT("/Game/UI/UI_Pause.UI_Pause_C"));
	if (UI_PAUSE_C.Succeeded())
	{
		MenuWidgetClass = UI_PAUSE_C.Class;
	}
	
	static ConstructorHelpers::FClassFinder<USRCheckRankWidget> UI_CHECKRANK_C(TEXT("/Game/UI/UI_CheckRank.UI_CheckRank_C"));
	if (UI_CHECKRANK_C.Succeeded())
	{
		CheckRankWidgetClass = UI_CHECKRANK_C.Class;
	}

	static ConstructorHelpers::FClassFinder<USRRankingWidget> UI_RANKING_C(TEXT("/Game/UI/UI_RANKING.UI_RANKING_C"));
	if (UI_RANKING_C.Succeeded())
	{
		RankingWidgetClass = UI_RANKING_C.Class;
	}
}

void ASRPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(LogTemp, Warning, TEXT("Player Controller PostInitializeComponents"));
}

void ASRPlayerController::OnPossess(APawn* aPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Player Controller OnPossess"));
	Super::OnPossess(aPawn);
}

void ASRPlayerController::ChangeInputMode(bool bGameMode)
{
	if (bGameMode)
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(UIInputMode);
		bShowMouseCursor = true;
	}
}

void ASRPlayerController::AddGameScore(int EarnedScore)
{
	SRPlayerState->AddGameScore(EarnedScore);
}

void ASRPlayerController::SubtractCurrentBullet()
{
	SRPlayerState->SetCurrentBullets(SRPlayerState->GetCurrentBullets() - 1);
}

void ASRPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ChangeInputMode(true);

	PlayerCameraManager->ViewPitchMin = -45.0f;
	PlayerCameraManager->ViewPitchMax = 45.0f;

	HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
	HUDWidget->AddToViewport();

	HuddyWidget = CreateWidget<UUserWidget>(this, HuddyWidgetClass);
	HuddyWidget->AddToViewport();

	SRPlayerState = Cast<ASRPlayerState>(PlayerState);
	if (nullptr != SRPlayerState)
	{
		SRPlayerState->BindPlayerController(this);
		HUDWidget->BindPlayerState(SRPlayerState);
		SRPlayerState->SetTotalBullets(Cast<AShooting_RangeGameModeBase>(GetWorld()->GetAuthGameMode())->GetTotalBullets());
		SRPlayerState->SetCurrentBullets(SRPlayerState->GetTotalBullets());
		SRPlayerState->OnPlayerStateChanged.Broadcast();
	}
}

void ASRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &ASRPlayerController::OnGamePause);
}

void ASRPlayerController::OnGamePause()
{
	MenuWidget = CreateWidget<USRGamePlayWidget>(this, MenuWidgetClass);
	ensure(nullptr != MenuWidget);
	MenuWidget->AddToViewport(3);

	SetPause(true);
	ChangeInputMode(false);
}

void ASRPlayerController::OnGameEnd()
{
	CheckRankWidget = CreateWidget<USRCheckRankWidget>(this, CheckRankWidgetClass);
	ensure(nullptr != CheckRankWidget);
	CheckRankWidget->AddToViewport();
	CheckRankWidget->UpdateWidget();

	SetPause(true);
	ChangeInputMode(false);
}

void ASRPlayerController::ShowRankingWidget()
{
	RankingWidget = CreateWidget<USRRankingWidget>(this, RankingWidgetClass);
	ensure(nullptr != RankingWidget);
	RankingWidget->AddToViewport();
	RankingWidget->UpdateWidget();

	SetPause(true);
	ChangeInputMode(false);
}