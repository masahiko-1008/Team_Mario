#include "WalkState.h"
#include "DxLib.h"
#include "../../../Utility/InputManager.h"
#include "../../../Utility/ResourceManager.h"
#include "../Player.h"

#define D_MAX_SPEED		(100.0f)

//�R���X�g���N�^	p=�v���C���[���
WalkState::WalkState(class Player* p)
	: PlayerStateBase(p)
	, direction(Vector2D(0.0f))
	, player_dash(false)
{

}

//�f�X�g���N�^
WalkState::~WalkState()
{

}

//����������
void WalkState::Initialize()
{
	//�A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::CreateInstance();
	move_animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);

}

//�I������
void WalkState::Finalize()
{
	// ���I�z��̉��
	move_animation.clear();
}

//�X�V����
void WalkState::Update(float delta_second)
{
	//���͏��̎擾
	InputManager* input = InputManager::CreateInstance();

	//�L�[��������Ă�����
	if (input->GetKey(KEY_INPUT_A) == true)
	{
		player->velocity.x += -0.1f;

		//���V�t�g�������Ă�����_�b�V�����
		if (input->GetKey(KEY_INPUT_LSHIFT) == true)
		{
			player_dash = true;
		}

		player->SetFli_flg(TRUE);
	}

	if (input->GetKey(KEY_INPUT_D) == true)
	{
		player->velocity.x += 0.1f;

		//���V�t�g�������Ă�����_�b�V�����
		if (input->GetKey(KEY_INPUT_LSHIFT) == true)
		{
			player_dash = true;
		}

		player->SetFli_flg(FALSE);
	}

	//�X�s�[�h�̏���𒴂��Ȃ��悤�ɂ���
	if (player_dash == false)
	{
		if (player->velocity.x <= -(D_MAX_SPEED))
		{
			player->velocity.x = -(D_MAX_SPEED);
		}
		else if (player->velocity.x >= D_MAX_SPEED)
		{
			player->velocity.x = D_MAX_SPEED;
		}
	}
	else			//�_�b�V�����Ȃ�
	{
		if (player->velocity.x <= -(D_MAX_SPEED) * 2.0f)
		{
			player->velocity.x = -(D_MAX_SPEED) * 2.0f;
		}
		else if (player->velocity.x >= D_MAX_SPEED * 2.0f)
		{
			player->velocity.x = D_MAX_SPEED * 2.0f;
		}
	}

	//�W�����v��ԂɑJ��
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		player->SetNextState(ePlayerState::eJUMP);
	}

	//�ړ��L�[�����Ă�����
	if ((input->GetKey(KEY_INPUT_A) == false) && (input->GetKey(KEY_INPUT_D) == false))
	{
		player_dash = false;

		//�i�s�����Ƌt�̕����ɖ��C��������
		if (player->velocity.x < 0)
		{
			player->velocity.x += (D_DYNAMIC_FRICTION * (D_MASS + D_GRAVITY)) * delta_second;

			// 0���Z�̍l��
			if (player->velocity.x > -D_STATIC_FRICTION)
			{
				player->SetNextState(ePlayerState::eIDLE);
			}
		}
		else if (player->velocity.x > 0)
		{
			player->velocity.x -= (D_DYNAMIC_FRICTION * (D_MASS + D_GRAVITY)) * delta_second;

			// 0���Z�̍l��
			if (player->velocity.x < D_STATIC_FRICTION)
			{
				player->SetNextState(ePlayerState::eIDLE);
			}
		}
	}
}

//�`�揈��
void WalkState::Draw() const
{

}

//���݂̃X�e�[�g�����擾����@return=���݂̃X�e�[�g���
ePlayerState WalkState::GetState() const
{
	return ePlayerState::eWALK;
}