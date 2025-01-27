#include "Player.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../Player/State/Factory/StateFactory.h"
#include "../../Utility/Singleton.h"
#include "DxLib.h"

Player::Player()
{

}

Player::~Player()
{

}

/// <summary>
/// ����������
/// </summary>
void Player::Initialize()
{
	state = StateFactory::Get((*this), ePlayerState::eIDLE);
	next_state = ePlayerState::eNONE;

	//�A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::CreateInstance();
	move_animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);

	//�W�����v���ʉ�BGM�̓ǂݍ���
	Jump_sound = rm->GetSounds("Resource/Sounds/SE_MiniJump.wav");

	//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::ePlayer;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.box_size = (32.0f, 32.0f);

	// ���C���[�̐ݒ�
	z_layer = 5;

	//HP�̐ݒ�
	hit_point = 1;

	// �����̐ݒ�
	mobility = eMobilityType::Movable;

	//�X�N���[���G���h
	scroll_end = false;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Player::Update(float delta_second)
{
	InputManager* input = InputManager::CreateInstance();

	//state�̕ύX����
	if (next_state != ePlayerState::eNONE)
	{
		state = StateFactory::Get((*this), next_state);
		next_state = ePlayerState::eNONE;
		now_state = state->GetState();
	}

	//�d�͑��x�̌v�Z
	g_velocity += D_GRAVITY / 444.0f;
	velocity.y += g_velocity;

	//�}���I����ʂ̊O�ɂ����Ȃ��悤�ɂ���
	if (location.x <= 17)
	{
		location.x = 17;
	}

	if (scroll_end == false)
	{
		if (location.x >= 640 / 2)
		{
			location.x = 640 / 2;
		}
	}
	else
	{
		if (location.x >= 623)
		{
			location.x = 623;
		}
	}

	//��ԕʂ̍X�V�������s��
	state->Update(delta_second);

	//�ړ��̎��s
	location += velocity * delta_second;
	collision.location = this->location;

	//400.0f�n�_��n�ʂƉ���
	if (400.0f < location.y)
	{
		location.y = 400.0f;
		g_velocity = 0.0f;
		velocity.y = 0.0f;
	}

	AnimationControl(delta_second);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset">�I�t�Z�b�g�l</param>
void Player::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%f", this->location.y);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "%f", this->velocity.x);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "player_x:%f", this->GetLocation().x);
}

/// <summary>
/// �I��������
/// </summary>
void Player::Finalize()
{
	StateFactory::Finalize();

	// ���I�z��̉��
	move_animation.clear();
}

void Player::OnHitCollision(GameObject*)
{
	//�v���C���[�̉E�����I�u�W�F�N�g�ƐڐG���Ă���ꍇ
	if (collision.hitCheck.H_right)
	{
		//�E�����ɐi�s�ł��Ȃ�����
		if (this->velocity.x > 0)
		{
			velocity.x = 0.0f;

			//�߂荞�񂾕���߂�����
			float diff;
		}
	}
	else if (collision.hitCheck.H_left)
	{
		//�������ɐi�s�ł��Ȃ�����
		if (this->velocity.x < 0)
		{
			velocity.x = 0.0f;
		}
	}
}

void Player::AnimationControl(float delta_second)
{
	switch (now_state)
	{
	case eIDLE:
		image = move_animation[0];
		break;
	case eWALK:
		// �ړ����̃A�j���[�V����
		animation_time += delta_second;
		if (animation_time >= (1.0f / 10.0f))
		{
			animation_time = 0.0f;
			animation_count++;
			if (animation_count >= 2)
			{
				animation_count = 0;
			}

			image = move_animation[animation_count + 1];
		}

		break;
	case eJUMP:
		image = move_animation[5];
		PlaySoundMem(Jump_sound, DX_PLAYTYPE_BACK);
		break;
	case eATTACK:
		break;
	case eDAMAGE:
		break;
	case eGOAL:
		break;
	case eDIE:
		break;
	case eNONE:
		break;
	default:
		break;
	}
}

//����State��ݒ�
void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}

//��ʒ[�ɂȂ�����X�N���[�����I��点��
void Player::SetScroll()
{
	scroll_end = true;
}