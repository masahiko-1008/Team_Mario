#include "Collision.h"
#include <math.h>

///// <summary>
///// �K�p�I�u�W�F�N�g���m�F���鏈��
///// </summary>
///// <param name="hit_object">����̃I�u�W�F�N�g�^�C�v</param>
///// <returns>�K�p����I�u�W�F�N�g�Ȃ�Atrue</returns>
bool Collision::IsCheckHitTarget(eObjectType hit_object) const
{
	// �K�p����I�u�W�F�N�g�^�C�v�Ȃ�Atrue
	for (eObjectType type : hit_object_type)
	{
		if (type == hit_object)
		{
			return true;
		}
	}

	return false;
}

//
///// <summary>
///// ��`�Ƌ�`�̓����蔻��m�F����
///// </summary>
///// <param name="c1">��`�̏��1</param>
///// <param name="c2">��`�̏��2</param>
///// <returns>�������Ă���Ȃ�Atrue</returns>
bool IsCheckCollision(Collision& b1, Collision& b2)
{
	//��̃I�u�W�F�N�g�̋������擾
	Vector2D diff = b1.box_location[0] - b2.box_location[0];

	//��̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (b1.box_size + b2.box_size) / 2.0f;

	//�������傫�����傫���ꍇ�Ahit����Ƃ���
	if ((fabsf(diff.x) < box_size.x) && (fabs(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		return true;
	}

	return false;
}

//�e�ӂ��ڐG���Ă��邩�ǂ����̊m�F
HitCheck IsHitCheck(Collision& b1, Collision& b2)
{
	//b1�̏㑤�������ɂ���̂�����
	if (abs(b1.box_location[0].y + (b1.box_size.y / 2)) < abs(b2.box_location[0].y + (b2.box_size.y / 2)))
	{
		if (b1.box_location[0].y < b2.box_location[0].y + b2.box_size.y)
		{
			b1.hitCheck.H_top = true;
			//b2.H_bottom = true;
		}

		b1.hitCheck.H_bottom = false;
		//b2.H_top = false;

	}
	else
	{
		if (b1.box_location[0].y < b2.box_location[0].y + b2.box_size.y)
		{
			b1.hitCheck.H_bottom = true;
			//b2.H_top = true;
		}

		b1.hitCheck.H_top = false;
		//b2.H_bottom = false;

	}

	//b1�̉E���������ɂ���̂�����
	if (abs(b1.box_location[0].x + (b1.box_size.x / 2)) < abs(b2.box_location[0].x + (b2.box_size.x / 2)))
	{
		if (b1.box_location[0].x < b2.box_location[0].x + b2.box_size.x)
		{
			b1.hitCheck.H_left = true;
			//b2.H_right = true;
		}

		b1.hitCheck.H_right = false;
		//b2.H_right = false;
	}
	else
	{
		if (b1.box_location[0].x + b1.box_size.x > b2.box_location[0].x)
		{
			b1.hitCheck.H_right = true;
			//b2.H_left = true;
		}

		b1.hitCheck.H_left = false;
		//b2.H_left = false;
	}

	//�I�u�W�F�N�g�Ɋe�ӂ̓����蔻���n������
	return b1.hitCheck;
	//o2.SetCollision(b1.H_top, b1.H_bottom, b1.H_left, b1.H_right);
}
