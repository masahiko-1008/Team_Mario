#pragma once
#include "../GameObject.h"

class Character : public GameObject
{
public:
	Vector2D velocity = Vector2D(0.0f);		//���x

protected:
	int hit_point;							//�c��c�@
	std::vector<int> damage_animation;		//�A�j���[�V�����摜
	bool on_ground;							//�n�ʂɐG��Ă��邩�ǂ���

protected:
	Character() :
		velocity(0.0f)
		, hit_point(0)
		, on_ground(true)
	{

	}
	virtual ~Character()
	{
		this->Finalize();
	}

	/*/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize();
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	virtual void Update(float delta_second);
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="screen_offset">�I�t�Z�b�g�l</param>
	virtual void Draw(const Vector2D& screen_offset) const;*/
	/// <summary>
	/// �I��������
	/// </summary>
	virtual void Finalize()
	{
		move_animation.clear();
	}


public:
	//virtual void OnHitCollision(GameObject*) override;
};