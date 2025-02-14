#pragma once

#include "../Character.h"

enum ePlayerState : unsigned char
{
	eIDLE,
	eWALK,
	eJUMP,
	eATTACK,
	eDAMAGE,
	eGOAL,
	eDIE,
	eNONE
};

class Player : public Character
{
private:
	class PlayerStateBase* state = nullptr;			//現在の状態
	ePlayerState next_state = ePlayerState::eNONE;	//次の状態
	ePlayerState now_state = ePlayerState::eIDLE;	//現在のステート状態

	std::vector<int> move_animation;

	ePlayerState player_state;				//プレイヤーの状態
	float star_time;						//無敵時間
	bool is_power;							//パワーアップ状態か
	bool is_star;							//無敵時間中か
	bool scroll_end;						//スクロールエンド
	int Jump_sound;							//ジャンプ効果音
	int animation_num[3] = { 1, 2, 3 };


public:
	void SetFlip_flag(bool flag);
	bool GetFlip_flag();
	Vector2D Get_Velocity();
	void Set_Velocity(Vector2D velocity_x);
	bool slide_flag;

public:
	Player();
	~Player();

	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;

	void OnHitCollision(GameObject*) override;		//コリジョン
	void SetNextState(ePlayerState next_state);		//次のStateを設定

	void SetScroll();								//スクロール判断

	void Set_SlideFlag(bool flag);

private:
	void ChengeMode();
	void AnimationControl(float delta_second) override;
	void Movement(float delta_second);
};
