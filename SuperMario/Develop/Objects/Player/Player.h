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
	class PlayerStateBase* state = nullptr;			//���݂̏��
	ePlayerState next_state = ePlayerState::eNONE;	//���̏��
	ePlayerState now_state = ePlayerState::eIDLE;	//���݂̃X�e�[�g���

	std::vector<int> move_animation;

	ePlayerState player_state;				//�v���C���[�̏��
	float star_time;						//���G����
	bool is_power;							//�p���[�A�b�v��Ԃ�
	bool is_star;							//���G���Ԓ���
	bool scroll_end;						//�X�N���[���G���h
	int Jump_sound;							//�W�����v���ʉ�
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

	void OnHitCollision(GameObject*) override;		//�R���W����
	void SetNextState(ePlayerState next_state);		//����State��ݒ�

	void SetScroll();								//�X�N���[�����f

	void Set_SlideFlag(bool flag);

private:
	void ChengeMode();
	void AnimationControl(float delta_second) override;
	void Movement(float delta_second);
};
