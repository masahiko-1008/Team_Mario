#include "Collision.h"
#include <math.h>

///// <summary>
///// 適用オブジェクトか確認する処理
///// </summary>
///// <param name="hit_object">相手のオブジェクトタイプ</param>
///// <returns>適用するオブジェクトなら、true</returns>
bool Collision::IsCheckHitTarget(eObjectType hit_object) const
{
	// 適用するオブジェクトタイプなら、true
	for (eObjectType type : hit_object_type)
	{
		if (type == hit_object)
		{
			return true;
		}
	}

	return false;
}

//
///// <summary>
///// 矩形と矩形の当たり判定確認処理
///// </summary>
///// <param name="c1">矩形の情報1</param>
///// <param name="c2">矩形の情報2</param>
///// <returns>当たっているなら、true</returns>
bool IsCheckCollision(Collision& b1, Collision& b2)
{
	//二つのオブジェクトの距離を取得
	Vector2D diff = b1.box_location[0] - b2.box_location[0];

	//二つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (b1.box_size + b2.box_size) / 2.0f;

	//距離より大きさが大きい場合、hit判定とする
	if ((fabsf(diff.x) < box_size.x) && (fabs(diff.y) < box_size.y))
	{
		//当たったことをオブジェクトに通知する
		return true;
	}

	return false;
}

//各辺が接触しているかどうかの確認
HitCheck IsHitCheck(Collision& b1, Collision& b2)
{
	//b1の上側か下側にいるのか判定
	if (abs(b1.box_location[0].y + (b1.box_size.y / 2)) < abs(b2.box_location[0].y + (b2.box_size.y / 2)))
	{
		if (b1.box_location[0].y < b2.box_location[0].y + b2.box_size.y)
		{
			b1.hitCheck.H_top = true;
			//b2.H_bottom = true;
		}

		b1.hitCheck.H_bottom = false;
		//b2.H_top = false;

	}
	else
	{
		if (b1.box_location[0].y < b2.box_location[0].y + b2.box_size.y)
		{
			b1.hitCheck.H_bottom = true;
			//b2.H_top = true;
		}

		b1.hitCheck.H_top = false;
		//b2.H_bottom = false;

	}

	//b1の右側か左側にいるのか判定
	if (abs(b1.box_location[0].x + (b1.box_size.x / 2)) < abs(b2.box_location[0].x + (b2.box_size.x / 2)))
	{
		if (b1.box_location[0].x < b2.box_location[0].x + b2.box_size.x)
		{
			b1.hitCheck.H_left = true;
			//b2.H_right = true;
		}

		b1.hitCheck.H_right = false;
		//b2.H_right = false;
	}
	else
	{
		if (b1.box_location[0].x + b1.box_size.x > b2.box_location[0].x)
		{
			b1.hitCheck.H_right = true;
			//b2.H_left = true;
		}

		b1.hitCheck.H_left = false;
		//b2.H_left = false;
	}

	//オブジェクトに各辺の当たり判定を渡す処理
	return b1.hitCheck;
	//o2.SetCollision(b1.H_top, b1.H_bottom, b1.H_left, b1.H_right);
}
