#pragma once

typedef struct tagVector2
{
	float fX, fY;

	tagVector2() : fX(0), fY(0) {}
	tagVector2(float _fX, float _fY) : fX(_fX), fY(_fY) {}

	tagVector2		operator+(const tagVector2& _Value) const
	{
		tagVector2 Temp;
		Temp.fX = fX + _Value.fX;
		Temp.fY = fY + _Value.fY;

		return Temp;
	}

	void		operator+=(const tagVector2& _Value)
	{
		fX += _Value.fX;
		fY += _Value.fY;
	}

	tagVector2		operator-(const tagVector2& _Value) const
	{
		tagVector2 Temp;
		Temp.fX = fX - _Value.fX;
		Temp.fY = fY - _Value.fY;

		return Temp;
	}

	void		operator-=(const tagVector2& _Value)
	{
		fX -= _Value.fX;
		fY -= _Value.fY;
	}

	tagVector2		operator*(const float& _fValue) const
	{
		return tagVector2(fX * _fValue, fY * _fValue);
	}

	void		operator*=(const float& _fValue)
	{
		fX *= _fValue;
		fY *= _fValue;
	}

	tagVector2		operator/(const float& _fValue) const
	{
		return tagVector2(fX / _fValue, fY / _fValue);
	}

	void		operator/=(const float& _fValue)
	{
		fX /= _fValue;
		fY /= _fValue;
	}

	bool		operator==(const tagVector2& _Value) const
	{
		return (FLT_EPSILON >= abs(fX - _Value.fX) && FLT_EPSILON >= abs(fY - _Value.fY));
	}

	bool		operator!=(const tagVector2& _Value) const
	{
		return (FLT_EPSILON < abs(fX - _Value.fX) && FLT_EPSILON < abs(fY - _Value.fY));
	}


	float		Length()	const
	{
		return sqrt((fX * fX) + (fY * fY));
	}

	float		SquareLen()	const
	{
		return ((fX * fX) + (fY * fY));
	}

	void		Normalize()
	{
		fX /= Length();
		fY /= Length();
	}

	tagVector2		Normalized()	const
	{
		tagVector2 Temp(fX, fY);

		Temp /= Temp.Length();

		return Temp;
	}

	float		Distance(tagVector2 _Value)	const
	{
		return (_Value - tagVector2(fX, fY)).Length();
	}

}VEC2;