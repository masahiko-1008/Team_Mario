#include "Kuriboo.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

Kuriboo::Kuriboo()
{

}

Kuriboo::~Kuriboo()
{

}

void Kuriboo::Initialize()
{

	//アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::CreateInstance();
	move_animation = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.box_size = (32.0f, 32.0f);

	//体力の設定
	hit_point = 1;

	//初期画像の設定
	image = move_animation[0];
}

void Kuriboo::Finalize()
{

}

void Kuriboo::Update(float delta_second)
{
	////重力速度の計算
	g_velocity += D_GRAVITY / 444.0f;
	velocity.y += g_velocity;

	//移動の実行
	location += velocity * delta_second;

	//400.0f地点を地面と仮定
	if (400.0f < location.y)
	{
		location.y = 400.0f;
		g_velocity = 0.0f;
		velocity.y = 0.0f;
	}

	AnimationControl(delta_second);
}

//void Kuriboo::Draw(const Vector2D& screen_offset) const
//{
//	DrawFormatString(10, 120, GetColor(255, 255, 255), "エネミー座標:%f", this->location.x);
//}

void Kuriboo::AnimationControl(float delta_second)
{

}