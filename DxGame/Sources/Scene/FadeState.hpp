# pragma once

struct FadeState
{
	const float fadeCount;

	float currentCount;

	const bool isSwallow;

	FadeState(float fadeCount, bool isSwallow);
};
