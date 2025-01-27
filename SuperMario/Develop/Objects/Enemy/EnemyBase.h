#pragma once

#include "../GameObject.h"
#include "../Character.h"

//���݃��[�h
enum eNowMode
{
	NONE,
	WALK,
	SHELL,
	DIE
};

//�G�l�~�[�̃^�C�v
enum eEnemyType
{
	KURIBO = 0,
	NOKONOKO,
};

class EnemyBase : public Character
{
protected:
	eNowMode now_mode;					//���݂̏��
	eEnemyType enemy_type;				//�G�̎��

public:
	EnemyBase();			//�R���X�g���N�^
	virtual ~EnemyBase();		//�f�X�g���N�^

	virtual void Initialize() override;								//����������
	void Finalize() override;									//�I��������
	void Draw(const Vector2D& screen_offset) const override;		//�`�揈��
	void Update(float delta_second) override;					//�X�V����

	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	//virtual void OnHitCollision(GameObjectBase* hit_object) override;

protected:

	virtual void  AnimationControl(float delta_second);		//�A�j���[�V��������

private:
	void Movement(float delta_second);			//�ړ�����

};