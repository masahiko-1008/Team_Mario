#include "IdleState.h"

#include "DxLib.h"
#include "../../../Utility/InputManager.h"
#include "../Player.h"

//�R���X�g���N�^	p = �v���C���[���
IdleState::IdleState(class Player* p)
	: PlayerStateBase(p)
{

}

//�f�X�g���N�^
IdleState::~IdleState()
{

}

//����������
void IdleState::Initialize()
{
	//���x���O�ɂ���
	player->velocity = 0.0f;
}

//�I������
void IdleState::Finalize()
{

}

//�X�V����
void IdleState::Update(float delta_second)
{
	InputManager* input = InputManager::CreateInstance();

	//�W�����v��ԂɑJ��
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		player->SetNextState(ePlayerState::eJUMP);
	}

	//�ǉ�����chord
//�ړ���ԂɑJ��
	if ((input->GetKey(KEY_INPUT_A) == true) || (input->GetKey(KEY_INPUT_D) == true))
	{
		player->SetNextState(ePlayerState::eWALK);
	}
}

//�`�揈��
void IdleState::Draw() const
{

}

//���݂̃X�e�[�g�����擾����@return = ���݂̃X�e�[�g���
ePlayerState IdleState::GetState() const
{
	return ePlayerState::eIDLE;
}