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
/// 初期化処理
/// </summary>
void Player::Initialize()
{
	state = StateFactory::Get((*this), ePlayerState::eIDLE);
	next_state = ePlayerState::eNONE;

	//アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::CreateInstance();
	move_animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);

	//ジャンプ効果音BGMの読み込み
	Jump_sound = rm->GetSounds("Resource/Sounds/SE_MiniJump.wav");

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::ePlayer;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.box_size = (32.0f, 32.0f);

	// レイヤーの設定
	z_layer = 5;

	//HPの設定
	hit_point = 1;

	// 可動性の設定
	mobility = eMobilityType::Movable;

	//スクロールエンド
	scroll_end = false;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Player::Update(float delta_second)
{
	InputManager* input = InputManager::CreateInstance();

	//stateの変更処理
	if (next_state != ePlayerState::eNONE)
	{
		state = StateFactory::Get((*this), next_state);
		next_state = ePlayerState::eNONE;
		now_state = state->GetState();
	}

	//重力速度の計算
	g_velocity += D_GRAVITY / 444.0f;
	velocity.y += g_velocity;

	//マリオが画面の外にいかないようにする
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

	//状態別の更新処理を行う
	state->Update(delta_second);

	//移動の実行
	location += velocity * delta_second;
	collision.location = this->location;

	//400.0f地点を地面と仮定
	if (400.0f < location.y)
	{
		location.y = 400.0f;
		g_velocity = 0.0f;
		velocity.y = 0.0f;
	}

	AnimationControl(delta_second);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset">オフセット値</param>
void Player::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%f", this->location.y);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "%f", this->velocity.x);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "player_x:%f", this->GetLocation().x);
}

/// <summary>
/// 終了時処理
/// </summary>
void Player::Finalize()
{
	StateFactory::Finalize();

	// 動的配列の解放
	move_animation.clear();
}

void Player::OnHitCollision(GameObject*)
{
	//プレイヤーの右側がオブジェクトと接触している場合
	if (collision.hitCheck.H_right)
	{
		//右方向に進行できなくする
		if (this->velocity.x > 0)
		{
			velocity.x = 0.0f;

			//めり込んだ分を戻す処理
			float diff;
		}
	}
	else if (collision.hitCheck.H_left)
	{
		//左方向に進行できなくする
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
		// 移動中のアニメーション
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

//次のStateを設定
void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}

//画面端になったらスクロールを終わらせる
void Player::SetScroll()
{
	scroll_end = true;
}