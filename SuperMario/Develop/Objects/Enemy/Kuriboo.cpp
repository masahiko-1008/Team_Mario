#include "Kuriboo.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

#define SPEED (30)

Kuriboo::Kuriboo()
{

}

Kuriboo::~Kuriboo()
{

}

void Kuriboo::Initialize()
{

	//�A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::CreateInstance();
	move_animation = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);

	//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.box_size = Vector2D(32, 32);

	//���C���[�ݒ�
	z_layer = 4;

	//�����̐ݒ�
	//is_mobility = true;

	image = move_animation[0];

	velocity.x = -1.0f;

	animation_count = 0;

	animation_time = 0;

	//die_time = 0;

	//�̗͂̐ݒ�
	hit_point = 1;

	//�����摜�̐ݒ�
	image = move_animation[0];
}

void Kuriboo::Finalize()
{

}

void Kuriboo::Update(float delta_second)
{
	////�d�͑��x�̌v�Z
	g_velocity += D_GRAVITY / 444.0f;
	velocity.y += g_velocity;

	//�ړ��̎��s
	location += velocity * delta_second;

	//400.0f�n�_��n�ʂƉ���
	if (400.0f < location.y)
	{
		location.y = 400.0f;
		g_velocity = 0.0f;
		velocity.y = 0.0f;
	}

	AnimationControl(delta_second);
}

void Kuriboo::Draw(const Vector2D& screen_offset) const
{
	//�e�N���X�̏������Ăяo��
	__super::Draw(screen_offset);

	Vector2D ul = location - (collision.box_size / 2);
	Vector2D br = location + (collision.box_size / 2);

	//DrawFormatString(10, 120, GetColor(255, 255, 255), "�G�l�~�[���W:%f", this->location.x);
}

void Kuriboo::AnimationControl(float delta_second)
{
	animation_time += delta_second;

	if (animation_time >= 0.5)
	{
		animation_time = 0.0f;

		image = move_animation[animation_count];

		animation_count++;

		if (animation_count > 1)
		{
			animation_count = 0;
		}

	}
}