





#include "Systems/TimeRewind/TimeRewind.hpp"
#include "Entities/Entity.hpp"
#include "Components/StateComponents/ActiveBasedStateComponent.hpp"
#include "Components/AttributeComponents/AsteroidAttributeComponent.hpp"
#include "Components/IndefiniteRepeatableAnimationComponent.hpp"
#include "Components/CollisionComponents/AsteroidCollisionComponent.hpp"
#include "Components/CollisionComponents/BulletCollisionComponent.hpp"
#include "Components/CollisionComponents/PlayerCollisionComponent.hpp"
#include "Components/RayMovementComponent.hpp"
#include "Components/MovementComponents/UserInputBasedMovementComponent.hpp"
#include "Components/OnceRepeatableAnimationComponent.hpp"
#include "Systems/InputSystem.hpp"
#include "Systems/CallbacksTimer.hpp"



namespace Asteroid
{

	TimeRewind::TimeRewind()
		:m_startIndex(0U)
		,m_endIndex(m_startIndex)
	{
		m_pastFrame.resize(m_totalNumPastFramesToRecord);
		

		for (auto& l_frame : m_pastFrame) {
			
			l_frame.m_allEntitysMetaDataInThisFrame[0].m_collisionMetaData.m_alreadyRegisteredCollisionEntityIDs.reserve(128U);
			l_frame.m_delayedCallbacks.reserve(1024U);
		}

	}


	void TimeRewind::Update(const std::vector<Entity>& l_entities, const InputSystem& l_inputSystem,const float l_time, const uint32_t l_totalNumBulletsHitAsteroid, const std::vector<DelayedSetStateCallback>& l_delayedCallbacks)
	{
		auto& lv_frame = m_pastFrame[m_endIndex];
		lv_frame.m_time = l_time;
		lv_frame.m_totalNumBulletsHitAsteroid = l_totalNumBulletsHitAsteroid;

		lv_frame.m_mousePos = l_inputSystem.GetMousePosRelativeToWindow();
		lv_frame.m_isMouseHidden = l_inputSystem.IsMouseHidden();
		lv_frame.m_delayedCallbacks = l_delayedCallbacks;

		for (size_t i = 0; i < l_entities.size(); ++i) {

			auto& lv_entity = lv_frame.m_allEntitysMetaDataInThisFrame[i];

			const auto lv_entityType = l_entities[i].GetType();

			const auto* lv_activeComp = (ActiveBasedStateComponent*)l_entities[i].GetComponent(ComponentTypes::ACTIVE_BASED_STATE);

			if (nullptr != lv_activeComp) {
				lv_entity.m_activeMetaData.m_delayedActivateCallbackAlreadySet = lv_activeComp->IsDelayedCallbackAlreadySet();
			}


			lv_entity.m_entityMetaData.m_id = l_entities[i].GetID();
			lv_entity.m_entityMetaData.m_isActive = l_entities[i].GetActiveState();
			lv_entity.m_entityMetaData.m_pos = l_entities[i].GetCurrentPos();
			lv_entity.m_entityMetaData.m_type = lv_entityType;


			const auto* lv_indefiniteRepeatAnimComponent = (IndefiniteRepeatableAnimationComponent*)l_entities[i].GetComponent(ComponentTypes::INDEFINITE_ENTITY_ANIMATION);
			lv_entity.m_indefRepAnimMetaData.m_currentOffset = lv_indefiniteRepeatAnimComponent->GetCurrentOffset();
			lv_entity.m_indefRepAnimMetaData.m_isInWindowBounds = lv_indefiniteRepeatAnimComponent->IsInWindowBounds();
			lv_entity.m_indefRepAnimMetaData.m_isVisible = lv_indefiniteRepeatAnimComponent->GetVisibility();


			const AsteroidAttributeComponent* lv_asteroidAttribComponent{};
			const AsteroidCollisionComponent* lv_asteroidCollisionComp{};
			const RayMovementComponent* lv_asteroidMovComponent{};
			const OnceRepeatableAnimationComponent* lv_explosionAnim{};
			const OnceRepeatableAnimationComponent* lv_warpAnim{};
			const BulletCollisionComponent* lv_bulletCollisionComp{};
			const RayMovementComponent* lv_bulletMovComponent{};
			AttributeComponent* lv_playerAttribComponent{};
			const UserInputBasedMovementComponent* lv_playerMovComponent{};
			const PlayerCollisionComponent* lv_playerCollisionComp{};


			switch (lv_entityType) {

			case EntityType::ASTEROID:

				lv_asteroidAttribComponent = (AsteroidAttributeComponent*)l_entities[i].GetComponent(ComponentTypes::ATTRIBUTE);
				lv_entity.m_attribMetaData.m_hp = lv_asteroidAttribComponent->GetHp();
				lv_entity.m_attribMetaData.m_asteroidStates = lv_asteroidAttribComponent->GetState();


				lv_asteroidCollisionComp = (AsteroidCollisionComponent*)l_entities[i].GetComponent(ComponentTypes::COLLISION);
				lv_entity.m_collisionMetaData.m_firstCollision = lv_asteroidCollisionComp->IsFirstCollision();
				lv_entity.m_collisionMetaData.m_hitBullet = lv_asteroidCollisionComp->IsHitByBullet();
				lv_entity.m_collisionMetaData.m_isCollisionActive = lv_asteroidCollisionComp->GetCollisionState();
				lv_entity.m_collisionMetaData.m_resetCollision = lv_asteroidCollisionComp->IsCollisionReset();

				lv_asteroidMovComponent = (RayMovementComponent*)l_entities[i].GetComponent(ComponentTypes::MOVEMENT);
				lv_entity.m_movementMetaData.m_speed = lv_asteroidMovComponent->GetSpeed();
				lv_entity.m_movementMetaData.m_thetaDegrees = lv_asteroidMovComponent->GetCurrentAngleOfRotation();
				lv_entity.m_movementMetaData.m_pauseMovement = lv_asteroidMovComponent->GetPauseState();
				lv_entity.m_movementMetaData.m_rayDirection = lv_asteroidMovComponent->GetRayDirection();
				lv_entity.m_movementMetaData.m_initialT = lv_asteroidMovComponent->GetInitalT();
				lv_entity.m_movementMetaData.m_initialPos = lv_asteroidMovComponent->GetInitialPos();


				lv_explosionAnim = (OnceRepeatableAnimationComponent*)l_entities[i].GetComponent(ComponentTypes::EXPLOSION_FIRE_ASTEROID_ANIMATION);
				lv_warpAnim = (OnceRepeatableAnimationComponent*)l_entities[i].GetComponent(ComponentTypes::WARP_ASTEROID_ANIMATION);

				lv_entity.m_onceRepAnimMetaData[0].m_currentOffset = lv_explosionAnim->GetCurrentOffset();
				lv_entity.m_onceRepAnimMetaData[0].m_initialPos = lv_explosionAnim->GetInitialAnimationPos();
				lv_entity.m_onceRepAnimMetaData[0].m_startAnimation = lv_explosionAnim->AnimationHasStarted();


				lv_entity.m_onceRepAnimMetaData[1].m_currentOffset = lv_warpAnim->GetCurrentOffset();
				lv_entity.m_onceRepAnimMetaData[1].m_initialPos = lv_warpAnim->GetInitialAnimationPos();
				lv_entity.m_onceRepAnimMetaData[1].m_startAnimation = lv_warpAnim->AnimationHasStarted();

				break;

			case EntityType::BULLET:

				lv_bulletCollisionComp = (BulletCollisionComponent*)l_entities[i].GetComponent(ComponentTypes::COLLISION);
				lv_entity.m_collisionMetaData.m_isCollisionActive = lv_bulletCollisionComp->GetCollisionState();
				lv_entity.m_collisionMetaData.m_firstCollision = lv_bulletCollisionComp->IsFirstCollision();
				lv_entity.m_collisionMetaData.m_resetCollision = lv_bulletCollisionComp->IsCollisionReset();
				


				lv_bulletMovComponent = (RayMovementComponent*)l_entities[i].GetComponent(ComponentTypes::MOVEMENT);
				lv_entity.m_movementMetaData.m_speed = lv_bulletMovComponent->GetSpeed();
				lv_entity.m_movementMetaData.m_thetaDegrees = lv_bulletMovComponent->GetCurrentAngleOfRotation();
				lv_entity.m_movementMetaData.m_pauseMovement = lv_bulletMovComponent->GetPauseState();
				lv_entity.m_movementMetaData.m_rayDirection = lv_bulletMovComponent->GetRayDirection();
				lv_entity.m_movementMetaData.m_initialT = lv_bulletMovComponent->GetInitalT();
				lv_entity.m_movementMetaData.m_initialPos = lv_bulletMovComponent->GetInitialPos();


				break;

			case EntityType::PLAYER:

				lv_playerAttribComponent = (AttributeComponent*)l_entities[i].GetComponent(ComponentTypes::ATTRIBUTE);
				lv_entity.m_attribMetaData.m_hp = lv_playerAttribComponent->GetHp();


				lv_playerMovComponent = (UserInputBasedMovementComponent*)l_entities[i].GetComponent(ComponentTypes::MOVEMENT);
				lv_entity.m_movementMetaData.m_speed = lv_playerMovComponent->GetSpeed();
				lv_entity.m_movementMetaData.m_thetaDegrees = lv_playerMovComponent->GetCurrentAngleOfRotation();
				lv_entity.m_movementMetaData.m_pauseMovement = lv_playerMovComponent->GetPauseState();
				

				lv_playerCollisionComp = (PlayerCollisionComponent*)l_entities[i].GetComponent(ComponentTypes::COLLISION);
				lv_entity.m_collisionMetaData.m_firstCollision = lv_playerCollisionComp->IsFirstCollision();
				lv_entity.m_collisionMetaData.m_isCollisionActive = lv_playerCollisionComp->GetCollisionState();
				lv_entity.m_collisionMetaData.m_resetCollision = lv_playerCollisionComp->IsCollisionReset();
				lv_entity.m_collisionMetaData.m_alreadyRegisteredCollisionEntityIDs = lv_playerCollisionComp->GetAlreadyRegisteredCollisionIDs();
				break;


			}

		}


		++m_endIndex;
		m_endIndex %= m_totalNumPastFramesToRecord;

		if (m_endIndex == m_startIndex) {
			++m_startIndex;
			m_startIndex %= m_totalNumPastFramesToRecord;
		}


	}


	void TimeRewind::RewindTimeByOneFrame(std::vector<Entity>& l_entities, InputSystem& l_inputSystem,float& l_time, uint32_t& l_totalNumBulletsHitAsteroid, CallbacksTimer& l_callbackTimer)
	{
		uint32_t lv_index{};

		if (m_endIndex == m_startIndex) {
			lv_index = m_startIndex;
		}
		else if (0U == m_endIndex) {
			m_endIndex = m_totalNumPastFramesToRecord - 1U;
			lv_index = m_endIndex;
		}
		else {
			--m_endIndex;
			lv_index = m_endIndex;
		}

		auto& lv_frame = m_pastFrame[lv_index];

		l_time = lv_frame.m_time;
		l_totalNumBulletsHitAsteroid = lv_frame.m_totalNumBulletsHitAsteroid;
		l_inputSystem.SetHiddenStateOfMouse(lv_frame.m_isMouseHidden);
		l_inputSystem.SetMousePos(lv_frame.m_mousePos);
		l_callbackTimer.SetDelayedCallbacks(lv_frame.m_delayedCallbacks);

		for (size_t i = 0; i < l_entities.size(); ++i) {

			auto& lv_entity = lv_frame.m_allEntitysMetaDataInThisFrame[i];


			auto* lv_activeComp = (ActiveBasedStateComponent*)l_entities[i].GetComponent(ComponentTypes::ACTIVE_BASED_STATE);

			if (nullptr != lv_activeComp) {
				lv_activeComp->SetDelayedActivationCallbackFlag(lv_entity.m_activeMetaData.m_delayedActivateCallbackAlreadySet);
			}

			l_entities[i].SetActiveState(lv_entity.m_entityMetaData.m_isActive);
			l_entities[i].SetCurrentPos(lv_entity.m_entityMetaData.m_pos);

			auto* lv_indefiniteRepeatAnimComponent = (IndefiniteRepeatableAnimationComponent*)l_entities[i].GetComponent(ComponentTypes::INDEFINITE_ENTITY_ANIMATION);
			lv_indefiniteRepeatAnimComponent->SetCurrentOffset(lv_entity.m_indefRepAnimMetaData.m_currentOffset);
			lv_indefiniteRepeatAnimComponent->SetVisibleState(lv_entity.m_indefRepAnimMetaData.m_isVisible);
			lv_indefiniteRepeatAnimComponent->SetWindowsBound(lv_entity.m_indefRepAnimMetaData.m_isInWindowBounds);



			AsteroidAttributeComponent* lv_asteroidAttribComponent{};
			AsteroidCollisionComponent* lv_asteroidCollisionComp{};
			RayMovementComponent* lv_asteroidMovComponent{};
			OnceRepeatableAnimationComponent* lv_explosionAnim{};
			OnceRepeatableAnimationComponent* lv_warpAnim{};
			BulletCollisionComponent* lv_bulletCollisionComp{};
			RayMovementComponent* lv_bulletMovComponent{};
			AttributeComponent* lv_playerAttribComponent{};
			UserInputBasedMovementComponent* lv_playerMovComponent{};
			PlayerCollisionComponent* lv_playerCollisionComp{};




			switch (lv_entity.m_entityMetaData.m_type) {

			case EntityType::ASTEROID:

				lv_asteroidAttribComponent = (AsteroidAttributeComponent*)l_entities[i].GetComponent(ComponentTypes::ATTRIBUTE);
				lv_asteroidAttribComponent->SetHP(lv_entity.m_attribMetaData.m_hp);
				lv_asteroidAttribComponent->SetState(lv_entity.m_attribMetaData.m_asteroidStates);


				lv_asteroidCollisionComp = (AsteroidCollisionComponent*)l_entities[i].GetComponent(ComponentTypes::COLLISION);				
				lv_asteroidCollisionComp->SetCollisionFirstFlag(lv_entity.m_collisionMetaData.m_firstCollision);
				lv_asteroidCollisionComp->SetCollisionState(lv_entity.m_collisionMetaData.m_isCollisionActive);
				lv_asteroidCollisionComp->SetCollisionResetFlag(lv_entity.m_collisionMetaData.m_resetCollision);
				lv_asteroidCollisionComp->SetBulletHitFlag(lv_entity.m_collisionMetaData.m_hitBullet);

				lv_asteroidMovComponent = (RayMovementComponent*)l_entities[i].GetComponent(ComponentTypes::MOVEMENT);
				lv_asteroidMovComponent->SetAngleOfRotation(lv_entity.m_movementMetaData.m_thetaDegrees);
				lv_asteroidMovComponent->SetSpeed(lv_entity.m_movementMetaData.m_speed);
				lv_asteroidMovComponent->SetInitialPos(lv_entity.m_movementMetaData.m_initialPos);
				lv_asteroidMovComponent->SetInitialT(lv_entity.m_movementMetaData.m_initialT);
				lv_asteroidMovComponent->SetPauseState(lv_entity.m_movementMetaData.m_pauseMovement);
				lv_asteroidMovComponent->SetRayDirection(lv_entity.m_movementMetaData.m_rayDirection);


				lv_explosionAnim = (OnceRepeatableAnimationComponent*)l_entities[i].GetComponent(ComponentTypes::EXPLOSION_FIRE_ASTEROID_ANIMATION);
				lv_warpAnim = (OnceRepeatableAnimationComponent*)l_entities[i].GetComponent(ComponentTypes::WARP_ASTEROID_ANIMATION);

				lv_explosionAnim->SetAnimationStartState(lv_entity.m_onceRepAnimMetaData[0].m_startAnimation);
				lv_explosionAnim->SetCurrentOffset(lv_entity.m_onceRepAnimMetaData[0].m_currentOffset);
				lv_explosionAnim->SetInitialAnimationPos(lv_entity.m_onceRepAnimMetaData[0].m_initialPos);

				lv_warpAnim->SetAnimationStartState(lv_entity.m_onceRepAnimMetaData[1].m_startAnimation);
				lv_warpAnim->SetCurrentOffset(lv_entity.m_onceRepAnimMetaData[1].m_currentOffset);
				lv_warpAnim->SetInitialAnimationPos(lv_entity.m_onceRepAnimMetaData[1].m_initialPos);

				break;

			case EntityType::BULLET:

				lv_bulletCollisionComp = (BulletCollisionComponent*)l_entities[i].GetComponent(ComponentTypes::COLLISION);
				lv_bulletCollisionComp->SetCollisionFirstFlag(lv_entity.m_collisionMetaData.m_firstCollision);
				lv_bulletCollisionComp->SetCollisionResetFlag(lv_entity.m_collisionMetaData.m_resetCollision);
				lv_bulletCollisionComp->SetCollisionState(lv_entity.m_collisionMetaData.m_isCollisionActive);


				lv_bulletMovComponent = (RayMovementComponent*)l_entities[i].GetComponent(ComponentTypes::MOVEMENT);
				lv_bulletMovComponent->SetAngleOfRotation(lv_entity.m_movementMetaData.m_thetaDegrees);
				lv_bulletMovComponent->SetSpeed(lv_entity.m_movementMetaData.m_speed);
				lv_bulletMovComponent->SetInitialPos(lv_entity.m_movementMetaData.m_initialPos);
				lv_bulletMovComponent->SetInitialT(lv_entity.m_movementMetaData.m_initialT);
				lv_bulletMovComponent->SetPauseState(lv_entity.m_movementMetaData.m_pauseMovement);
				lv_bulletMovComponent->SetRayDirection(lv_entity.m_movementMetaData.m_rayDirection);

				break;

			case EntityType::PLAYER:

				lv_playerAttribComponent = (AttributeComponent*)l_entities[i].GetComponent(ComponentTypes::ATTRIBUTE);
				lv_playerAttribComponent->SetHP(lv_entity.m_attribMetaData.m_hp);


				lv_playerMovComponent = (UserInputBasedMovementComponent*)l_entities[i].GetComponent(ComponentTypes::MOVEMENT);
				lv_playerMovComponent->SetAngleOfRotation(lv_entity.m_movementMetaData.m_thetaDegrees);
				lv_playerMovComponent->SetPauseState(lv_entity.m_movementMetaData.m_pauseMovement);
				lv_playerMovComponent->SetSpeed(lv_entity.m_movementMetaData.m_speed);


				lv_playerCollisionComp = (PlayerCollisionComponent*)l_entities[i].GetComponent(ComponentTypes::COLLISION);
				lv_playerCollisionComp->SetAlreadyRegisteredCollisionIDs(lv_entity.m_collisionMetaData.m_alreadyRegisteredCollisionEntityIDs);
				lv_playerCollisionComp->SetCollisionFirstFlag(lv_entity.m_collisionMetaData.m_firstCollision);
				lv_playerCollisionComp->SetCollisionResetFlag(lv_entity.m_collisionMetaData.m_resetCollision);
				lv_playerCollisionComp->SetCollisionState(lv_entity.m_collisionMetaData.m_isCollisionActive);
				break;


			}

		}




	}


	void TimeRewind::Flush()
	{
		m_startIndex = 0U;
		m_endIndex = m_startIndex;
		
		for (auto& l_frame : m_pastFrame) {
			l_frame.m_time = 0.f;
			l_frame.m_mousePos = glm::vec2(0.f);
			l_frame.m_totalNumBulletsHitAsteroid = 0U;
			l_frame.m_isMouseHidden = false;
			
			for (auto& l_entityData : l_frame.m_allEntitysMetaDataInThisFrame) {
				l_entityData.m_activeMetaData.m_delayedActivateCallbackAlreadySet = false;
				l_entityData.m_attribMetaData.m_asteroidStates = AsteroidStates::AGGRESIVE;
				l_entityData.m_attribMetaData.m_hp = 10;
				l_entityData.m_collisionMetaData.m_alreadyRegisteredCollisionEntityIDs.clear();
				l_entityData.m_collisionMetaData.m_firstCollision = true;
				l_entityData.m_collisionMetaData.m_hitBullet = 0U;
				l_entityData.m_collisionMetaData.m_isCollisionActive = true;
				l_entityData.m_collisionMetaData.m_resetCollision = true;
				
				memset(&l_entityData.m_indefRepAnimMetaData, 0, sizeof(l_entityData.m_indefRepAnimMetaData));
				memset(&l_entityData.m_movementMetaData, 0, sizeof(l_entityData.m_movementMetaData));
				memset(l_entityData.m_onceRepAnimMetaData.data(), 0, sizeof(OnceRepeatAnimationMetaData)*l_entityData.m_onceRepAnimMetaData.size());
			}
		}
	}

}