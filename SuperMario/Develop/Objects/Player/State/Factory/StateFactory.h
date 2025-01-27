#pragma once

#include "../PlayerStateBase.h"

class StateFactory
{
private:
	static StateFactory* instance;

private:
	StateFactory() = default;
	StateFactory(const StateFactory&) = default;
	StateFactory& operator=(const StateFactory&) = default;

private:
	class IdleState* idle;
	class JumpState* jump;
	class WalkState* walk;

private:
	void Initialize(class Player& player);

public:
	static PlayerStateBase* Get(class Player& player, ePlayerState state);
	static void Finalize();
};
