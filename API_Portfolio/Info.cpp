#include "stdafx.h"
#include "Info.h"
#include "Vector2.h"

tagInfo tagInfo::operator+(const Vector2 _Value) const
{
	tagInfo Temp{};
	Temp.fX += _Value.fX;
	Temp.fY += _Value.fY;

	return Temp;
}

tagInfo tagInfo::operator-(const Vector2 _Value) const
{
	tagInfo Temp{};
	Temp.fX -= _Value.fX;
	Temp.fY -= _Value.fY;

	return Temp;
}

void tagInfo::operator+=(const Vector2& _Value)
{
	fX += _Value.fX;
	fY += _Value.fY;
}

void tagInfo::operator-=(const Vector2& _Value)
{
	fX -= _Value.fX;
	fY -= _Value.fY;
}
