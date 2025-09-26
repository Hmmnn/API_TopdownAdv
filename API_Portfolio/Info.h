#pragma once

struct tagVector2;

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;

	tagInfo		operator+(const tagInfo& _Value) const
	{
		tagInfo Temp;
		Temp.fX = fX + _Value.fX;
		Temp.fY = fY + _Value.fY;

		return Temp;
	}
	tagInfo		operator+(const tagVector2 _Value) const;

	tagInfo		operator-(const tagInfo& _Value) const
	{
		tagInfo Temp;
		Temp.fX = fX - _Value.fX;
		Temp.fY = fY - _Value.fY;

		return Temp;
	}
	tagInfo		operator-(const tagVector2 _Value) const;

	void		operator+=(const tagInfo& _Value)
	{
		fX += _Value.fX;
		fY += _Value.fY;
	}
	void		operator+=(const tagVector2& _Value);

	void		operator-=(const tagInfo& _Value)
	{
		fX -= _Value.fX;
		fY -= _Value.fY;
	}
	void		operator-=(const tagVector2& _Value);

}INFO;
