#include "InGameScene.h"
#include "../../Objects/Player/Player.h"
#include "../../Objects/Enemy/EnemyBase.h"
#include "../../Objects/Enemy/Kuriboo.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"
#include <fstream>

#define START_POINT		(3350.0f)
#define END_POINT		(-2700.0f)

InGameScene::InGameScene()
	: player(nullptr)
	, enemy(nullptr)
	, back_ground_image(NULL)
	, back_ground_sound(NULL)
	, e_count(0)
	, pause_flag(false)
	, location(0.0f, 0.0f)
{

}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	//screen_offest�͕`�悾����ς��Ă��邩����ۂ�location�͕ς��Ȃ��͂�
	player = CreateObject<Player>(Vector2D(60.0f, 60.0f));

	CreateObject<Kuriboo>(Vector2D(0.0f + 200.f, 60.0f));

	stage_end = 3376;	//�Q�[���摜�̏����l

	//// �w�i�摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::CreateInstance();
	back_ground_image = rm->GetImages("Resource/Images/�z�u�f��/NES---Super-Mario-Bros---World-1-1�i�C���Łj.png")[0];

	//�Q�[��BGM�̓ǂݍ���
	back_ground_sound = rm->GetSounds("Resource/Sounds/BGM_MarioGround.wav");

	PlaySoundMem(back_ground_sound, DX_PLAYTYPE_BACK);
}

//���͏���
eSceneType InGameScene::Update(const float& delta_second)
{
	//���͏��̎擾
	InputManager* input = InputManager::CreateInstance();

	//PAUSE��ʂւ̑J��
	if (input->GetKeyDown(KEY_INPUT_P) || input->GetButtonDown(XINPUT_BUTTON_START))
	{
		pause_flag = !pause_flag;
	}

	//PAUSE��ʂł͂Ȃ����
	if (!pause_flag)
	{
		// �e�N���X�̍X�V�������Ăяo��
		__super::Update(delta_second);
	}

	//�}���I����ʂ̔����ɂ���ƃX�N���[��������
	if (player->GetLocation().x > 640 / 2 && player->velocity.x != 0)
	{
		stage_end -= 1;
	}
	if(stage_end < -2700)
	{
		stage_end = -2700;
		player->SetScroll();
	}

	////�X�N���[�X��������x���W�ʒu�ݒ�
	//generate_location.x = generate_location.x - camera->Get_Offset().x;

	////�J�����E�[�̍��W
	//float Dx = camera->Get_CameraLocation().x + D_WIN_MAX_X / 2;

	// �V�[������ԋp����
	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	stage_end;


	DrawRotaGraphF(stage_end, 480, 2.0, 0.0, back_ground_image, FALSE, FALSE);

	DrawFormatString(0, 90, GetColor(255, 255, 255), "%f", this->location.x);

	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

	// UI�n�̕`�揈��
	if (pause_flag)
	{
		DrawString(10, 10, " P A U S E ", GetColor(255, 255, 255), TRUE);
	}
}

void InGameScene::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::in_game;
}

/// <summary>
/// �����蔻��m�F����
/// </summary>
/// <param name="target">1�ڂ̃Q�[���I�u�W�F�N�g</param>
/// <param name="partner">2�ڂ̃Q�[���I�u�W�F�N�g</param>
void InGameScene::HitCheckObject(GameObject* target, GameObject* partner)
{
	// �k���|�`�F�b�N
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	// �����蔻������擾
	Collision tc = target->GetCollision();
	Collision pc = partner->GetCollision();

	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{

		// �����̎n�_�ƏI�_��ݒ肷��
		tc.box_location[0] = target->GetLocation();
		pc.box_location[0] = partner->GetLocation();

		// �J�v�Z�����m�̓����蔻��
		if (IsCheckCollision(tc, pc))
		{
			//��̃I�u�W�F�N�g�̋������擾
			Vector2D lc_diff = target->GetLocation() - partner->GetLocation();

			//��̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
			Vector2D box_size = target->GetBoxsize() + partner->GetBoxsize() / 2.0f;

			//�������傫�����傫���ꍇ�Ahit����Ƃ���
			if ((fabsf(lc_diff.x) < box_size.x) && (fabs(lc_diff.y) < box_size.y))
			{
				//IsHitCheck(b1, b2);

				//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
				return;
			}

			return;

			tc.hitCheck = IsHitCheck(tc, pc);
			pc.hitCheck = IsHitCheck(pc, tc);

			target->SetCollision(tc.hitCheck.H_top, tc.hitCheck.H_bottom, tc.hitCheck.H_left, tc.hitCheck.H_right);
			partner->SetCollision(pc.hitCheck.H_top, pc.hitCheck.H_bottom, pc.hitCheck.H_left, pc.hitCheck.H_right);

			// �������Ă��邱�Ƃ�ʒm����
			target->OnHitCollision(partner);
			partner->OnHitCollision(target);
		}

	}

}