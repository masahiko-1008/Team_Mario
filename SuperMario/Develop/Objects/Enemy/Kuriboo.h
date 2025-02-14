#pragma once

#include "EnemyBase.h"

#include "../Character.h"


class Kuriboo : public EnemyBase
{
private:
	std::vector<int> move_animation;
	int animation_count;
	float animation_time;

public:
	Kuriboo();
	~Kuriboo();

	void virtual Initialize() override;

	void virtual Finalize() override;

	void virtual Update(float delta_second) override;

	void virtual Draw(const Vector2D& screen_offset) const override;


private:
	void virtual AnimationControl(float delta_second) override;

public:
	//void virtual OnHitCollision(float delta_second) override;

};