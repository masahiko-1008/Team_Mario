#include "EnemyBase.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "../../Utility/ResourceManager.h"
#include "../Player/Player.h"
#include "DxLib.h"

#define D_ENEMY_SPEED	(40.0f)

EnemyBase::EnemyBase() : now_mode()
{
}

EnemyBase::~EnemyBase()
{
}

//����������
void EnemyBase::Initialize()
{
	//now_mode;				//���݂̏��
	//move_animation;		//�S�[�X�g�摜
	//eye_animation;		//�ڂ̉摜
	//direction;			//�i�s����
	//e_velocity;			//�ړ����x
	//start_point;			//�����n�_�̍��W

	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	mobility = eMobilityType::Movable;

}

//�X�V����
void EnemyBase::Update(float delta_second)
{
	//�ړ�����
	Movement(delta_second);

	//�A�j���[�V��������
	AnimationControl(delta_second);
}

//�`�揈��
void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);

}

//�I��������
void EnemyBase::Finalize()
{
	//move_animation.clear();		//�S�[�X�g�摜
}

//�ړ�����
void EnemyBase::Movement(float delta_second)
{
	// �ړ��� * ���� * ���� �ňړ�������肷��
	location += velocity * D_ENEMY_SPEED * delta_second;
}

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void EnemyBase::AnimationControl(float delta_second)
{
	// �ړ����̃A�j���[�V����
	//animation_time += delta_second;
	//if (animation_time >= (1.0f / 16.0f))
	//{
	//	animation_time = 0.0f;
	//	animation_count++;

	//	if (animation_count >= 4)
	//	{
	//		image = animation_num[(enemy_type * 2) + 1];

	//		animation_count = 0;
	//	}

	//	image = animation_num[(enemy_type * 2)];

	//	// �摜�̐ݒ�
	//	int dir_num = (int)direction;
	//	if (0 <= dir_num && dir_num < 4)
	//	{
	//		eye_image = eye_animation[dir_num];
	//	}

	//}
}