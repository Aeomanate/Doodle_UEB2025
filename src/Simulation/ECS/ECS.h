#ifndef ECS_H
#define ECS_H

#include "Features/Movable/CPosition.h"
#include "Features/Movable/CPhysics.h"
#include "Features/Movable/SEntityMover.h"

#include "Features/Movable/SCollisionDetector.h"

#include "Features/Visual/CSceneElement.h"
#include "Features/Visual/SSpriteAnimator.h"
#include "Features/Visual/SEntityPainter.h"

#include "Features/LifetimeControl/ESpawnHolder.h"
#include "Features/LifetimeControl/SSpawner.h"

#include "Features/Input/CTagPlayerControllable.h"
#include "Features/Input/CInputMousePositions.h"
#include "Features/Input/CInputMouseClicks.h"
#include "Features/Input/CInputKeyHoldingEvent.h"
#include "Features/Input/EInputContainer.h"
#include "Features/Input/SInputInjector.h"
#include "Features/Input/SInputCleaner.h"

#include "Features/Levels/ELevelState.h"
#include "Features/Levels/CLevelState.h"
#include "Features/Levels/SLevelStateObserver.h"

#include "Features/Info/CText.h"
#include "Features/Info/EDebugText.h"
#include "Features/Info/SDebugInfo.h"

#endif //ECS_H
