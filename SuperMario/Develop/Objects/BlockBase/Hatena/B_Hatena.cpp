#include "B_Hatena.h"
#include "../../../Utility/ResourceManager.h"
#include "DxLib.h"

void Hatena::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	block_image = rm->GetImagesResource("Resource/Images/Block/hatena.png", 4, 4, 1, 32, 32);
	kara_block = LoadGraph("Resource/Images/Block/kara_block.png");
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eItem);

	collision.box_size = Vector2D(32, 32);

	is_mobility = false;

	image = block_image[0];

	animation_time = 0.0f;

	animation_count = 0;

	up_count = 0;

	down_count = 0;

	hit_flag = false;

}

void Hatena::Update(float delta_seconde)
{
	if (hit_flag == true)
	{
		if (up_count < 8)
		{
			this->location.y += -1;
			up_count++;
		}
		else if (down_count < 8)
		{
			this->location.y += 1;
			down_count++;
		}
	}
	AnimationControl(delta_seconde);
}

void Hatena::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Hatena::Finalize()
{

}

void Hatena::OnHitCollision(GameObject* hit_object)
{
	Vector2D diff = 0.0f;
	Vector2D target_boxsize, this_boxsize;
	Vector2D target_location = hit_object->GetLocation();

	//2“_ŠÔ‚Ì‹——£‚ð‹‚ß‚é
	diff = this->location - target_location;


	if (diff.y < 0)
	{
		if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
		{
			image = kara_block;
			hit_flag = true;
		}
	}


}
const Vector2D& Hatena::GetLocation() const
{
	return location;
}

const Collision& Hatena::GetCollision() const
{
	return collision;
}

const unsigned char Hatena::GetZLayer() const
{
	return z_layer;
}

const bool Hatena::GetMobility() const
{
	return is_mobility;
}

void Hatena::AnimationControl(float delta_seconde)
{
	animation_time += delta_seconde;

	if (animation_time >= 0.2)
	{
		animation_time = 0.0f;

		animation_count++;

		if (animation_count >= 4)
		{
			animation_count = 0;
		}

		if (hit_flag == false)
		{
			image = block_image[animation_count];
		}
		else
		{
			image = kara_block;
		}

	}
}