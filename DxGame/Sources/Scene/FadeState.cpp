#include "FadeState.hpp"

FadeState::FadeState(float fadeCount, bool isSwallow)
	: fadeCount(fadeCount)
	, currentCount(fadeCount)
	, isSwallow(isSwallow)
{

}
