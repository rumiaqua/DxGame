# pragma once

# include <DxLib.h>

# include "IAccessor.hpp"

class Player
{
private:

	enum PlayerState
	{
		Stop,
		Run,
		Jump,
	};

	enum Animation
	{
		Empty = -1,
		Run = 1,
		Jump = 2,
		Fall = 3,
		Stand = 4,
	};

public:

	Player();

	virtual ~Player();

	void Initialize();

	void Update();

	void Render() const;

	void Finalize();

private:

	void Move(VECTOR moveVector);

	using PolyContainer = std::vector<MV1_COLL_RESULT_POLY*>;

	void Separate(
		const MV1_COLL_RESULT_POLY_DIM& hitDimensions,
		PolyContainer& walls,
		PolyContainer& planes);

	static bool HitCheckPolyTriangle(
		const VECTOR& pos1,
		const VECTOR& pos2,
		const MV1_COLL_RESULT_POLY* polygon);

	const MV1_COLL_RESULT_POLY* IsCollidePolygons(
		const VECTOR& position,
		const Player::PolyContainer& polygons) const;

	bool CollideOnMoving(
		const VECTOR& moveVector,
		VECTOR& position,
		const Player::PolyContainer& walls);

	void CollideWallOnStop();

	void SlideWall();

	void Rotate();

	void PlayAnimation(int playAnimation);

	void Animation();

	void Shadow() const;

public:

	Getter<VECTOR> Position { m_position };

	Getter<VECTOR> TargetMoveDirection { m_position };

private:

	VECTOR m_position;

	VECTOR m_direction;

	float m_angle;

	float m_jumpPower;

	int m_modelHandle;

	int m_shadowHandle;

	int m_state;

	int m_playAnimation1;

	float m_playAnimationCount1;

	int m_playAnimation2;

	float m_playAnimationCount2;

	float m_animationBlendRate;
};
