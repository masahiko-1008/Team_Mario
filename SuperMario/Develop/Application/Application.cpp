/*#include "Application.h"
#include "DxLib.h"


Application::Application()
{

}

Application::~Application()
{
	// ����Y��h�~
	Shutdown();
}

/// <summary>
/// ����������
/// </summary>
void Application::WakeUp()
{
	// �E�B���h�E���[�h�ŋN������
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y�̐ݒ�
	SetGraphMode(D_WIN_MAX_X, D_WIN_MAX_Y, D_COLOR_BIT);

	// �E�B���h�E�^�C�g���̐ݒ�
	SetWindowText("Game Development Pac-Man 2024");

	// �����������s��Ȃ�
	SetWaitVSyncFlag(FALSE);

	// Log.txt�t�@�C���̐�������iDebug���[�h�̂ݐ�������j
#if _DEBUG
	SetOutApplicationLogValidFlag(TRUE);
#else
	SetOutApplicationLogValidFlag(FALSE);
#endif // _DEBUG

	// Dx���C�u�����̏�����
	if (DxLib_Init() == D_FAILURE)
	{
		throw std::string("Dx���C�u�����̏������Ɏ��s���܂����I\n");
	}

	// �`����\��ʂɔ��f����
	SetDrawScreen(DX_SCREEN_BACK);

	// �ŏ��̃V�[�����^�C�g����ʂɂ���
	ChangeScene(eSceneType::title);

	// ��A�N�e�B�u��Ԃł����삳����
	SetAlwaysRunFlag(TRUE);
}

/// <summary>
///  ���s����
/// </summary>
void Application::Run()
{
	// ���͏����擾����
	InputManager* input = InputManager::GetInstance();

	// ���C�����[�v
	while (ProcessMessage() == D_SUCCESS)
	{
		// ���͏��̍X�V
		input->Update();


		// �t���[�����[�g�̐���
		FreamControl();

		// �V�[���̍X�V
		eSceneType next_scene_type = current_scene->Update(GetDeltaSecond());

		// �`�揈��
		Graph();

		// �Q�[�����I�����邩�m�F����
		if ((next_scene_type == eSceneType::exit) ||
			(input->GetButtonUp(XINPUT_BUTTON_BACK)) ||
			(input->GetKeyUp(KEY_INPUT_ESCAPE)))
		{
			break;
		}

		// ���݂̃V�[���^�C�v�����̃V�[���^�C�v�ƈ���Ă��邩�H
		if (current_scene->GetNowSceneType() != next_scene_type)
		{
			// �V�[���؂�ւ�����
			ChangeScene(next_scene_type);
		}
	}
}

/// <summary>
/// �I��������
/// </summary>
void Application::Shutdown()
{
	// �V�[����񂪐�������Ă���΁A�폜����
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}

	// Singleton�̃C���X�^���X���������
	InputManager::DeleteInstance();
	ResourceManager::DeleteInstance();

	// Dx���C�u�����̎g�p���I������
	DxLib_End();
}

/// <summary>
/// �`�揈��
/// </summary>
void Application::Graph() const
{
	// ��ʂ̏�����
	ClearDrawScreen();

	// �V�[���̕`�揈��
	current_scene->Draw();

	// ����ʂ̓��e��\��ʂɔ��f����
	ScreenFlip();
}*/

