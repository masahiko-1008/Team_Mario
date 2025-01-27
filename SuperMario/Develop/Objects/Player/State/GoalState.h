#pragma once

#include "GoalState.h"
#include "Factory/StateFactory.h"

class GoalState : public PlayerStateBase
{
private:


public:
	//�R���X�g���N�^	p = �v���C���[���
	GoalState(class Player* p);

	//�f�X�g���N�^
	virtual ~GoalState();

public:
	//����������
	void Initialize();

	//�I������
	void Finalize();

	//�X�V����
	void Update();

	//�`�揈��
	void Draw() const;

	//���݂̃X�e�[�g�����擾����
	ePlayerState GetState() const override;
};
