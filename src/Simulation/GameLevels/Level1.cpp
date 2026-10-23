#include "Level1.h"

#include "Application/AppPartGetter.h"
#include "Application/Config/ConfigGeneral.h"
#include "Simulation/Features/Player/EPlayer.h"
#include "Simulation/ECS/ECS.h"
#include "Simulation/ECS/Features/LifetimeControl/SDespawner.h"
#include "Simulation/ECS/Features/Movable/ECollisions.h"
#include "Simulation/ECS/Features/Visual/SViewport.h"
#include "Simulation/Features/Abilities/Moving/SFall.h"
#include "Simulation/Features/Abilities/Moving/SJump.h"
#include "Simulation/Features/Abilities/Moving/SSpeedBoosterHalfScreen.h"
#include "Simulation/Features/Abilities/Moving/SWallTransfer.h"
#include "Simulation/Features/Background/EBackground.h"
#include "Simulation/Features/Background/SBackground.h"
#include "Simulation/Features/Enemies/SEnemyManager.h"
#include "Simulation/Features/Platforms/EPlatformsStorage.h"
#include "Simulation/Features/Platforms/SPlatformsManager.h"
#include "Simulation/Features/Player/SGameOverTracker.h"
#include "Simulation/Features/Player/SInputMove.h"
#include "Simulation/Features/Timer/ETimer.h"
#include "Simulation/Features/Timer/STimer.h"

Level1::Level1(LevelUPtr&& prevLevel)
{
    AddSeveral<LevelDataStorage::ChangeLevelPolicy::LOCAL>()
    // ECS related
    .Add<SViewport>()

    .Add<ETimer>()
    .Add<STimer>()
    ;

    AddSeveral<LevelDataStorage::ChangeLevelPolicy::TRANSIT>()
    // ECS related
    .Add<EDebugText>()
    .Add<SDebugInfo>()

    .Add<ELevelState>()
    .Add<SLevelStateObserver>()

    .Add<EInputContainer>()
    .Add<SInputInjector>()
    .Add<SInputCleaner>()

    .Add<ECollisions>()
    .Add<SEntityMover>()
    .Add<SCollisionDetector>()

    .Add<SEntityPainter>()
    .Add<SSpriteAnimator>()

    .Add<ESpawnHolder>()
    .Add<SSpawner>()
    .Add<SDespawner>()

    // Game-related
    .Add<EBackground>()
    .Add<SBackground>()

    .Add<EPlayer>()
    .Add<SInputMove>()

    .Add<EPlatformsStorage>()
    .Add<SPlatformsManager>()

    .Add<SFall>()
    .Add<SJump>()
    .Add<SWallTransfer>()

    .Add<SEnemyManager>()

    .Add<SSpeedBoosterHalfScreen>()
    .Add<SGameOverTracker>()


    ;


}
