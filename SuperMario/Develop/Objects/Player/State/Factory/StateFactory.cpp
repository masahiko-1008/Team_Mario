#include "StateFactory.h"
#include "../IdleState.h"
#include "../JumpState.h"
#include "../WalkState.h"
#include "../../Player.h"

StateFactory* StateFactory::instance = nullptr;

void StateFactory::Initialize(class Player& player)
{
	idle = new IdleState(&player);
	jump = new JumpState(&player);
	walk = new WalkState(&player);
}

void StateFactory::Finalize()
{
	instance->idle->Finalize();
	instance->jump->Finalize();
	instance->walk->Finalize();

	delete instance->idle;
	delete instance->jump;
	delete instance->walk;
}

PlayerStateBase* StateFactory::Get(Player& player, ePlayerState state)
{
	if (instance == nullptr)
	{
		instance = new StateFactory();
		instance->Initialize(player);
	}

	PlayerStateBase* ret = nullptr;
	switch (state)
	{
	case ePlayerState::eIDLE:
		instance->idle->Initialize();
		ret = instance->idle;
		break;
	case ePlayerState::eJUMP:
		instance->jump->Initialize();
		ret = instance->jump;
		break;
	case ePlayerState::eWALK:
		instance->walk->Initialize();
		ret = instance->walk;
	case ePlayerState::eNONE:
	default:
		break;
	}

	return ret;
}