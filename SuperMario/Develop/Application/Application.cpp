/*#include "Application.h"
#include "DxLib.h"


Application::Application()
{

}

Application::~Application()
{
	// 解放忘れ防止
	Shutdown();
}

/// <summary>
/// 初期化処理
/// </summary>
void Application::WakeUp()
{
	// ウィンドウモードで起動する
	ChangeWindowMode(TRUE);

	// ウィンドウサイズの設定
	SetGraphMode(D_WIN_MAX_X, D_WIN_MAX_Y, D_COLOR_BIT);

	// ウィンドウタイトルの設定
	SetWindowText("Game Development Pac-Man 2024");

	// 垂直同期を行わない
	SetWaitVSyncFlag(FALSE);

	// Log.txtファイルの生成制御（Debugモードのみ生成する）
#if _DEBUG
	SetOutApplicationLogValidFlag(TRUE);
#else
	SetOutApplicationLogValidFlag(FALSE);
#endif // _DEBUG

	// Dxライブラリの初期化
	if (DxLib_Init() == D_FAILURE)
	{
		throw std::string("Dxライブラリの初期化に失敗しました！\n");
	}

	// 描画先を表画面に反映する
	SetDrawScreen(DX_SCREEN_BACK);

	// 最初のシーンをタイトル画面にする
	ChangeScene(eSceneType::title);

	// 非アクティブ状態でも動作させる
	SetAlwaysRunFlag(TRUE);
}

/// <summary>
///  実行処理
/// </summary>
void Application::Run()
{
	// 入力情報を取得する
	InputManager* input = InputManager::GetInstance();

	// メインループ
	while (ProcessMessage() == D_SUCCESS)
	{
		// 入力情報の更新
		input->Update();


		// フレームレートの制御
		FreamControl();

		// シーンの更新
		eSceneType next_scene_type = current_scene->Update(GetDeltaSecond());

		// 描画処理
		Graph();

		// ゲームを終了するか確認する
		if ((next_scene_type == eSceneType::exit) ||
			(input->GetButtonUp(XINPUT_BUTTON_BACK)) ||
			(input->GetKeyUp(KEY_INPUT_ESCAPE)))
		{
			break;
		}

		// 現在のシーンタイプが次のシーンタイプと違っているか？
		if (current_scene->GetNowSceneType() != next_scene_type)
		{
			// シーン切り替え処理
			ChangeScene(next_scene_type);
		}
	}
}

/// <summary>
/// 終了時処理
/// </summary>
void Application::Shutdown()
{
	// シーン情報が生成されていれば、削除する
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}

	// Singletonのインスタンスを解放する
	InputManager::DeleteInstance();
	ResourceManager::DeleteInstance();

	// Dxライブラリの使用を終了する
	DxLib_End();
}

/// <summary>
/// 描画処理
/// </summary>
void Application::Graph() const
{
	// 画面の初期化
	ClearDrawScreen();

	// シーンの描画処理
	current_scene->Draw();

	// 裏画面の内容を表画面に反映する
	ScreenFlip();
}*/

