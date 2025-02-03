#include "Block.h"
#include "DxLib.h"

void Block::Initialize()
{
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eItem);

	image = LoadGraph("Resource/Images/Block/block.png");

	is_mobility = false;

}

void Block::Update(float delta_seconde)
{

}

void Block::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Block::Finalize()
{

}

void Block::OnHitCollision(GameObject* hit_object)
{

}

const Vector2D& Block::GetLocation() const
{
	return location;
}

const Collision& Block::GetCollision() const
{
	return collision;
}

const unsigned char Block::GetZLayer() const
{
	return z_layer;
}

const bool Block::GetMobility() const
{
	return is_mobility;
}
