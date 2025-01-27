#pragma once

#include "IdleState.h"
#include "Factory/StateFactory.h"

class IdleState : public PlayerStateBase
{
private:


public:
	//�R���X�g���N�^	p = �v���C���[���
	IdleState(class Player* p);

	//�f�X�g���N�^
	virtual ~IdleState();

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
