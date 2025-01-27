#pragma once

#include "EnemyBase.h"

class Kuriboo : public EnemyBase
{

public:
	Kuriboo();
	~Kuriboo();

	void virtual Initialize() override;

	void virtual Finalize() override;

	void virtual Update(float delta_second) override;

	//void virtual Draw(const Vector2D& screen_offset) const override;

private:
	void virtual AnimationControl(float delta_second) override;

public:
	//void virtual OnHitCollision(float delta_second) override;

};