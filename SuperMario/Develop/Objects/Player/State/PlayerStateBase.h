#pragma once
#include "../Player.h"

//�v���C���[��ԊǗ��p�̃x�[�X�N���X
class PlayerStateBase
{
protected:

	class Player* player;				//�v���C���[���
	int animation_count;				//�A�j���[�V�����J�E���g
	std::vector<int> move_animation;	//�A�j���[�V�����摜


public:
	//�R���X�g���N�^	p = �v���C���[���
	PlayerStateBase(class Player* p) : player(p), move_animation(NULL)
	{

	}

	//�f�X�g���N�^
	virtual ~PlayerStateBase() = default;

public:
	//�����������֐�
	virtual void Initialize() = 0;

	//�I�������֐�
	virtual void Finalize() = 0;

	//�X�V����
	virtual void Update(float deleta_second) = 0;

	//�`�揈��
	virtual void Draw() const = 0;

	//��Ԃ̎擾
	virtual ePlayerState GetState() const = 0;
};
