#include "WalkState.h"
#include "DxLib.h"
#include "../../../Utility/InputManager.h"
#include "../../../Utility/ResourceManager.h"
#include "../Player.h"

#define D_MAX_SPEED		(200.0f)

//コンストラクタ	p=プレイヤー情報
WalkState::WalkState(class Player* p)
	: PlayerStateBase(p)
	, direction(Vector2D(0.0f))
	, player_dash(false)
	, speed(0)
{

}

//デストラクタ
WalkState::~WalkState()
{

}

//初期化処理
void WalkState::Initialize()
{
	//アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::CreateInstance();
	move_animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);

}

//終了処理
void WalkState::Finalize()
{
	// 動的配列の解放
	move_animation.clear();
}

//更新処理
void WalkState::Update(float delta_second)
{
	//入力情報の取得
	InputManager* input = InputManager::CreateInstance();

	//キーが押されていたら
	if (input->GetKey(KEY_INPUT_A) == true)
	{
		player->velocity.x += -0.1f;

		//左シフトを押していたらダッシュ状態
		if (input->GetKey(KEY_INPUT_LSHIFT) == true)
		{
			player_dash = true;
		}

		if (speed > -100)
		{
			speed += (float)4 / 60 * -1;
		}

		player->Set_Velocity(Vector2D(speed, player->Get_Velocity().y));

		if (speed >= 0)
			{
				player->Set_SlideFlag(TRUE);
			}
			else
			{
				player->SetFlip_flag(TRUE);
			}

	}

	if (input->GetKey(KEY_INPUT_D) == true)
	{
		player->velocity.x += 0.1f;

		//左シフトを押していたらダッシュ状態
		if (input->GetKey(KEY_INPUT_LSHIFT) == true)
		{
			player_dash = true;
		}

		if (speed < 100)
		{
			speed += (float)4 / 60;
		}
		player->Set_Velocity(Vector2D(speed, player->Get_Velocity().y));

		if (speed <= 0)
		{
			player->Set_SlideFlag(TRUE);
		}
		else
		{
			player->SetFlip_flag(FALSE);
		}


	}

	//スピードの上限を超えないようにする
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
	else			//ダッシュ中なら
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

	//ジャンプ状態に遷移
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		player->SetNextState(ePlayerState::eJUMP);
	}

	//移動キー離していたら
	if ((input->GetKey(KEY_INPUT_A) == false) && (input->GetKey(KEY_INPUT_D) == false))
	{
		player_dash = false;

		//進行方向と逆の方向に摩擦をかける
		if (player->velocity.x < 0)
		{
			player->velocity.x += (D_DYNAMIC_FRICTION * (D_MASS + D_GRAVITY)) * delta_second;

			// 0除算の考慮
			if (player->velocity.x > -D_STATIC_FRICTION)
			{
				player->SetNextState(ePlayerState::eIDLE);
			}
		}
		else if (player->velocity.x > 0)
		{
			player->velocity.x -= (D_DYNAMIC_FRICTION * (D_MASS + D_GRAVITY)) * delta_second;

			// 0除算の考慮
			if (player->velocity.x < D_STATIC_FRICTION)
			{
				player->SetNextState(ePlayerState::eIDLE);
			}
		}
	}
}

//描画処理
void WalkState::Draw() const
{

}

//現在のステート情報を取得する　return=現在のステート情報
ePlayerState WalkState::GetState() const
{
	return ePlayerState::eWALK;
}