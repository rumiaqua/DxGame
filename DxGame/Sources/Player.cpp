# include "Player.hpp"

# include <algorithm>

namespace
{
	const float PlayAnimationSpeed = 250.0f;

	const float MoveSpeed = 30.0f;

	const float AnimationBlendSpeed = 0.1f;

	const float AngleSpeed = 0.2f;

	const float JumpPower = 100.0f;

	const float FallUpPower = 20.0f;

	const float Gravity = 3.0f;

	const int MaxHitCollisions = 2048;

	const float EnumDefaultSize = 800.0f;

	const float HitWidth = 200.0f;

	const float HitHeight = 700.0f;

	const int HitTryNum = 16;

	const float HitSlideLength = 5.0f;

	const float ShadowSize = 200.0f;

	const float ShadowHeight = 700.0f;
}

Player::Player()
{
	Initialize();
}

void Player::Initialize()
{
	m_position = VGet(0.0f, 0.0f, 0.0f);

	m_angle = 0.0f;

	m_jumpPower = 0.0f;

	m_modelHandle = MV1LoadModel(L"DxChara.x");

	m_shadowHandle = LoadGraph(L"Shadow.tga");

	m_state = PlayerState::Stop;

	m_direction = VGet(1.0f, 0.0f, 0.0f);

	m_animationBlendRate = 1.0f;

	m_playAnimation1 = Animation::Empty;

	m_playAnimation2 = Animation::Empty;

	PlayAnimation(Animation::Stand);
}

void Player::Update()
{

}

void Player::Render() const
{
}

void Player::Finalize()
{
	MV1DeleteModel(m_modelHandle);
	DeleteGraph(m_shadowHandle);
}

void Player::Move(VECTOR moveVector)
{
	VECTOR oldPosition = m_position;

	VECTOR nowPosition = VAdd(m_position, moveVector);

	MV1_COLL_RESULT_POLY_DIM hitDimensions =
		MV1CollCheck_Sphere(
			-1,
			-1,
			m_position,
			EnumDefaultSize + VSize(moveVector));

	bool moveFlag =
		fabs(moveVector.x) > 0.01f ||
		fabs(moveVector.y) > 0.01f;

	std::vector<MV1_COLL_RESULT_POLY*> walls;
	std::vector<MV1_COLL_RESULT_POLY*> planes;

	// �ǂƏ��𕪂���
	for (int i = 0; i < hitDimensions.HitNum; ++i)
	{
		MV1_COLL_RESULT_POLY& dim = hitDimensions.Dim[i];

		// Y����������Ȃ�0�ɋ߂���Ε�
		if (fabs(dim.Normal.y) < 0.000001f)
		{
			// �ǂ̏ꍇ
			// �v���C���[�̍��W + 1.0f �܂ň���
			const float Threshold = m_position.y + 1.0f;
			if (
				dim.Position[0].y > Threshold ||
				dim.Position[1].y > Threshold ||
				dim.Position[2].y > Threshold)
			{
				if (walls.size() < MaxHitCollisions)
				{
					walls.emplace_back(&dim);
				}
			}
		}

		// �ǂłȂ��ꍇ��
		if (planes.size() < MaxHitCollisions)
		{
			planes.emplace_back(&dim);
		}
	}

	bool hitFlag = false;
	if (moveFlag)
	{
		// �ǂƂ̏Փ˔���
		for (auto&& wall : walls)
		{
			// �|���S���ƃv���C���[���������Ă��Ȃ���Γǂݔ�΂�
			if (!HitCheck_Capsule_Triangle(
				nowPosition,
				VAdd(nowPosition, VGet(0.0f, HitHeight, 0.0f)),
				HitWidth,
				wall->Position[0],
				wall->Position[1],
				wall->Position[2]))
			{
				continue;
			}

			hitFlag = true;

			// �ǂ���x�N�g�������߂�
			VECTOR slideVector = VCross(moveVector, wall->Normal);
			slideVector = VCross(wall->Normal, slideVector);

			nowPosition = VAdd(oldPosition, slideVector);

			// �V���ȍ��W�ŕǂƏՓ˂��Ă��邩�𔻒�
			bool isCollide = std::any_of(walls.begin(), walls.end(),
				[&] (const MV1_COLL_RESULT_POLY* poly)
			{
				return HitCheck_Capsule_Triangle(
					nowPosition,
					VAdd(nowPosition, VGet(0.0f, HitHeight, 0.0f)),
					HitWidth,
					poly->Position[0],
					poly->Position[1],
					poly->Position[2]);
			});

			// �Փ˂��Ă��Ȃ���΃��[�v�𔲂���
			if (!isCollide)
			{
				hitFlag = false;
				break;
			}
		}
	}
	// �ړ����łȂ���Ίȗ�����������
	else
	{
		for (auto&& wall : walls)
		{
			if (HitCheck_Capsule_Triangle(
				nowPosition,
				VAdd(nowPosition, VGet(0.0f, HitHeight, 0.0f)),
				HitWidth,
				wall->Position[0],
				wall->Position[1],
				wall->Position[2]))
			{
				hitFlag = true;
				break;
			}
		}
	}

	// �����o������
	if (hitFlag)
	{
		for (int i = 0; i < HitTryNum; ++i)
		{
			for (auto&& wall : walls)
			{
				// �������Ă��Ȃ���Γǂݔ�΂�
				if (!HitCheck_Capsule_Triangle(
					nowPosition,
					VAdd(nowPosition, VGet(0.0f, HitHeight, 0.0f)),
					HitWidth,
					wall->Position[0],
					wall->Position[1],
					wall->Position[2]))
				{
					continue;
				}

				// �v���C���[��@�������Ɉړ�
				nowPosition = VAdd(
					nowPosition, VScale(wall->Normal, HitSlideLength));

				// �S�Ă̕ǂƏՓ˔���
				bool isCollide = std::any_of(walls.begin(), walls.end(),
					[&] (const MV1_COLL_RESULT_POLY* poly)
				{
					return HitCheck_Capsule_Triangle(
						nowPosition,
						VAdd(nowPosition, VGet(0.0f, HitHeight, 0.0f)),
						HitWidth,
						poly->Position[0],
						poly->Position[1],
						poly->Position[2]);
				});

				// �Փ˂��Ă��Ȃ���΃��[�v�����
				if (!isCollide)
				{
					i = HitTryNum;
					break;
				}
			}
		}
	}

	// ���Ƃ̏Փ˔���

	for (auto&& plane : planes)
	{

	}
}

void Player::Separate(
	const MV1_COLL_RESULT_POLY_DIM& hitDimensions,
	PolyContainer& walls,
	PolyContainer& planes)
{
	// �ǂƏ��𕪂���
	for (int i = 0; i < hitDimensions.HitNum; ++i)
	{
		MV1_COLL_RESULT_POLY& dim = hitDimensions.Dim[i];

		// Y����������Ȃ�0�ɋ߂���Ε�
		if (fabs(dim.Normal.y) < 0.000001f)
		{
			// �ǂ̏ꍇ
			// �v���C���[�̍��W + 1.0f �܂ň���
			const float Threshold = m_position.y + 1.0f;
			if (
				dim.Position[0].y > Threshold ||
				dim.Position[1].y > Threshold ||
				dim.Position[2].y > Threshold)
			{
				if (walls.size() < MaxHitCollisions)
				{
					walls.emplace_back(&dim);
				}
			}
		}

		// �ǂłȂ��ꍇ��
		if (planes.size() < MaxHitCollisions)
		{
			planes.emplace_back(&dim);
		}
	}
}

bool Player::HitCheckPolyTriangle(
	const VECTOR& pos1,
	const VECTOR& pos2,
	const MV1_COLL_RESULT_POLY* polygon)
{
	return HitCheck_Capsule_Triangle(
		pos1,
		pos2,
		HitWidth,
		polygon->Position[0],
		polygon->Position[1],
		polygon->Position[2]);
}

const MV1_COLL_RESULT_POLY* Player::IsCollidePolygons(
	const VECTOR& position,
	const Player::PolyContainer& polygons) const
{
	for (auto&& polygon : polygons)
	{
		if (HitCheckPolyTriangle(
			position,
			VAdd(position, VGet(0.0f, HitHeight, 0.0f)),
			polygon))
		{
			return polygon;
		}
	}
	return nullptr;
}

bool Player::CollideOnMoving(
	const VECTOR& moveVector,
	VECTOR& position,
	const Player::PolyContainer& walls)
{
	if (auto poly = IsCollidePolygons(position, walls))
	{
		VECTOR slideVector = VCross(moveVector, poly->Normal);
		slideVector = VCross(poly->Normal, slideVector);
		position = VAdd(m_position, slideVector);

		if (!IsCollidePolygons(position, walls))
		{
			return false;
		}
		return true;
	}
}

void Player::CollideWallOnStop()
{
}

void Player::SlideWall()
{
}

void Player::Rotate()
{

}

void Player::PlayAnimation(int playAnimation)
{

}

void Player::Animation()
{

}

void Player::Shadow() const
{

}
