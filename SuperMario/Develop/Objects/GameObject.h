#pragma once

#include "../Utility/Vector2D.h"
#include <vector>
#include <string>

#include "../Utility/Collision.h"

#define D_OBJECT_SIZE	(24.0f)			// �ǂ̃T�C�Y

#define D_MASS				(8.0f)	//���ʁikg)
#define D_GRAVITY	(9.807f)	//�d�͉����x(m/ss)
#define D_STATIC_FRICTION	(5.0f)	//�Î~���C�W��
#define D_DYNAMIC_FRICTION	(0.3f)	//�����C�W��

/// <summary>
/// �����̎��
/// </summary>
enum eMobilityType
{
	Stationary,		// �Œ�
	Movable,		// ��
};

// �Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	class SceneBase* owner_scene;	// ���L����V�[�����
	std::vector<int> move_animation;		//�A�j���[�V�����摜
	int animation_count;					//�A�j���[�V�����J�E���g
	float animation_time;					// �A�j���[�V��������

	Vector2D			location;	// �ʒu���W
	Collision			collision;		//��`�̑傫��
	int					image;			// �摜���
	int					z_layer;		// ���C���[���
	eMobilityType		mobility;		// ����
	float				g_velocity;		//�d�͑��x
	int					flip_flg;		//�摜�̔��]�t���O


public:
	GameObject();
	virtual ~GameObject();

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize();
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	virtual void Update(float delta_second);
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="screen_offset">�I�t�Z�b�g�l</param>
	virtual void Draw(const Vector2D& screen_offset) const;
	/// <summary>
	/// �I��������
	/// </summary>
	virtual void Finalize();

public:
	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(GameObject* hit_object);

public:
	/// <summary>
	/// ���L�V�[�����̐ݒ�
	/// </summary>
	/// <param name="scene">���L�V�[�����</param>
	void SetOwnerScene(class SceneBase* scene);

	/// <summary>
	/// �ʒu���W�擾����
	/// </summary>
	/// <returns>�ʒu���W���</returns>
	const Vector2D& GetLocation() const;

	/// <summary>
	/// �ʒu���ύX����
	/// </summary>
	/// <param name="location">�ύX�������ʒu���</param>
	void SetLocation(const Vector2D& location);

	/// <summary>
	/// �����蔻��擾����
	/// </summary>
	/// <returns>�����蔻��̑傫�����擾</returns>
	Collision GetCollision() const;

	//�e�ӂ̓����蔻����
	void SetCollision(bool t, bool b, bool l, bool r);

	//�R���W�����T�C�Y�擾����
	Vector2D GetBoxsize() const;

	/// <summary>
	/// �y���C���[���擾����
	/// </summary>
	/// <returns>�y���C���[���</returns>
	const int GetZLayer() const;

	/// <summary>
	/// �������̎擾����
	/// </summary>
	/// <returns>�������</returns>
	const eMobilityType GetMobility() const;

	///	���]�t���O�̐؂�ւ�
	///	TRUE��FALSE�̐��l��Ԃ�
	void SetFli_flg(int flip_flg);

	//�A�j���[�V��������
	virtual void AnimationControl(float delta_scond);
};
