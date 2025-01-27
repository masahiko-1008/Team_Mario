#pragma once

#include "JumpState.h"
#include "Factory/StateFactory.h"

class JumpState : public PlayerStateBase
{
private:
	//�O�t���[���̍��W���
	Vector2D old_location;
	int hold_count;
	bool jump_flg;

public:
	//�R���X�g���N�^	p=�v���C���[���
	JumpState(class Player* p);

	//�f�X�g���N�^
	virtual ~JumpState();

public:
	//����������
	void Initialize();

	//�I������
	void Finalize();

	//�X�V����
	void Update(float delta_second);

	//�`�揈��
	void Draw() const;

	//���݂̃X�e�[�g�����擾����
	ePlayerState GetState() const override;
};
