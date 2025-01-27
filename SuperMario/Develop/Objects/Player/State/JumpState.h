#pragma once

#include "JumpState.h"
#include "Factory/StateFactory.h"

class JumpState : public PlayerStateBase
{
private:
	//前フレームの座標情報
	Vector2D old_location;
	int hold_count;
	bool jump_flg;

public:
	//コンストラクタ	p=プレイヤー情報
	JumpState(class Player* p);

	//デストラクタ
	virtual ~JumpState();

public:
	//初期化処理
	void Initialize();

	//終了処理
	void Finalize();

	//更新処理
	void Update(float delta_second);

	//描画処理
	void Draw() const;

	//現在のステート情報を取得する
	ePlayerState GetState() const override;
};
