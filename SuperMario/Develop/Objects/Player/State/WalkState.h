#pragma once

#include "Factory/StateFactory.h"

class WalkState : public PlayerStateBase
{
private:
	//�v���C���[�̈ړ���
	Vector2D direction;

	//�_�b�V�������ǂ���
	bool player_dash;

public:
	//�R���X�g���N�^	p = �v���C���[���
	WalkState(class Player* p);

	//�f�X�g���N�^
	virtual ~WalkState();

public:
	//����������
	void Initialize();

	//�I������
	void Finalize();

	//�X�V����
	void Update(float delta_second);

	//�`�揈��
	void Draw() const;

	//�A�j���[�V��������
	void AnimationControl(float delta_second);

	//���݂̃X�e�[�g�����擾����
	ePlayerState GetState() const override;
};
