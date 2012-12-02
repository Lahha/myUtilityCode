#pragma once

#include <cmath>
#include <iostream>

template <typename T = float>
class Vec3
{
public:
	typedef T ValueType;
	typedef Vec3<T> Type;

protected:
	T x, y, z;

public:
	Vec3():
		x(0), y(0), z(0) {};

	Vec3(const Type &v)
	{
		assign(v);
	}

	Vec3(const ValueType& x_, const ValueType& y_, const ValueType& z_)
	{
		assign(x_, y_, z_);
	}

	//all modification through this.
	virtual void assign(const ValueType& x_, const ValueType& y_, const ValueType& z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}

	void assign(const Type &v)
	{
		assign(v.x, v.y, v.z);
	}

	void assignX(const ValueType &v)
	{
		assign(v, y, z);
	}

	void assignY(const ValueType &v)
	{
		assign(x, v, z);
	}

	void assignZ(const ValueType &v)
	{
		assign(x, y, v);
	}

	const ValueType& X() const
	{
		return x;
	}

	const ValueType& Y() const
	{
		return y;
	}

	const ValueType& Z() const
	{
		return z;
	}

	bool isWithinRange(const Type& v1, const Type& v2)
	{
		if(!(min(v1.x, v2.x) <= x && x <= max(v1.x, v2.x)))
			return false;

		if(!(min(v1.y, v2.y) <= y && y <= max(v1.y, v2.y)))
			return false;

		if(!(min(v1.z, v2.z) <= z && z <= max(v1.z, v2.z)))
			return false;

		return true;
	}

	void operator = (const Vec3<T>& v)
	{
		assign(v);
	}
	
	Type operator + (const Type& v) const
	{
		return Type(x + v.x, y + v.y, z + v.z);
	}

	Type operator - () const
	{
		return Type(-x, -y, -z);
	}

	Type operator - (const Type& v) const
	{
		return *this + (-v);
	}

	Type operator * (const ValueType& v) const
	{
		return Type(x * v, y * v, z * v);
	}

	Type operator * (const Type& v) const
	{
		return Type(x * v.x, y * v.y, z * v.z);
	}

	Type operator / (const T& v) const
	{
		return Type(x / v, y / v, z / v);
	}

	Type operator / (const Type& v) const
	{
		return Type(x / v.x, y / v.y, z / v.z);
	}

	Type& operator += (const Type& v)
	{
		*this = *this + v;
		return *this;
	}

	Type& operator -= (const Type& v)
	{
		*this = *this - v;
		return *this;
	}
	
	Type& operator *= (const T& v)
	{
		*this = *this * v;
		return *this;
	}

	Type& operator *= (const Type& v)
	{
		*this = *this * v;
		return *this;
	}

	Type& operator /= (const T& v)
	{
		*this = *this / v;
		return *this;
	}

	ValueType dot(const Type& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	Type cross(const Type& v) const
	{
		return Vec3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x );
	}

	ValueType pow2() const
	{
		return dot(*this);
	}

	ValueType length() const
	{
		return sqrt(pow2());
	}

	Type normal() const
	{
		Type result(*this);
		return result / length();
	}

	void normalize()
	{
		*this /= length();
	}

	double det(const Type& v) const
	{
		return x*v.y - y*v.x;
	}

	//Matrix<T> getMatrix3() const
	//{
	//	Matrix<T> tmp(3, 1);
	//	tmp.element(0) = x;
	//	tmp.element(1) = y;
	//	tmp.element(2) = z;

	//	return tmp;
	//}

	//Matrix<T> getMatrix4() const
	//{
	//	Matrix<T> tmp(4, 1);
	//	tmp.element(0) = x;
	//	tmp.element(1) = y;
	//	tmp.element(2) = z;
	//	tmp.element(3) = 1;

	//	return tmp;
	//}

	//void readMatrix(Matrix<T> matrix)
	//{
	//	x = matrix.element(0);
	//	y = matrix.element(1);
	//	z = matrix.element(2);
	//}

	//Type rotate(const Type& origin, const Type& axis, const T& angle) const
	//{
	//	axis.normalize();

	//	// macig happens

	//	T c = cos (angle);
	//	T s = sin(angle);
	//	T t = 1 - c;

	//	T tX2 = t * axis.x * axis.x;
	//	T tXY = t * axis.x * axis.y;
	//	T tXZ = t * axis.x * axis.z;
	//	T tY2 = t * axis.y * axis.y;
	//	T tYZ = t * axis.y * axis.z;
	//	T tZ2 = t * axis.z * axis.z;

	//	T sX = s * axis.x;
	//	T sY = s * axis.y;
	//	T sZ = s * axis.z;

	//	Matrix<T> rotationMatrix(4, 4);
	//	
	//	rotationMatrix.element(0, 0) = tX2 + c;
	//	rotationMatrix.element(0, 1) = tXY + sZ;
	//	rotationMatrix.element(0, 2) = tXZ - sY;
	//	rotationMatrix.element(0, 3) = 0;

	//	rotationMatrix.element(1, 0) = tXY - sZ; 
	//	rotationMatrix.element(1, 1) = tY2 + c;
	//	rotationMatrix.element(1, 2) = tYZ + sX;
	//	rotationMatrix.element(1, 3) = 0;

	//	rotationMatrix.element(2, 0) = tXY + sY;
	//	rotationMatrix.element(2, 1) = tYZ - sX;
	//	rotationMatrix.element(2, 2) = tZ2 + c;
	//	rotationMatrix.element(2, 3) = 0;

	//	rotationMatrix.element(3, 0) = 0;
	//	rotationMatrix.element(3, 1) = 0;
	//	rotationMatrix.element(3, 2) = 0;
	//	rotationMatrix.element(3, 3) = 1;

	//	Type result;
	//	result.readMatrix(rotationMatrix * (*this - origin).getMatrix4());

	//	return result + origin;
	//}

	//void rotateSelf(const Type& origin, const Type& axis, const T& angle)
	//{
	//	*this = rotate(origin, axis, angle);
	//}

	Type& rotateSelf(const Type& axis, const T& theta)
	{
		T x_ = x;
		T y_ = y;
		T z_ = z;

		//just to make it bit easier to read. Hopefully compiler will optimize these away;
		const T & u = axis.x;
		const T & v = axis.y;
		const T & w = axis.z;

		T cosT = cos(theta);
		T oneMinusCosT = 1 - cosT;
		T sinT = sin(theta);

        x = ((- u*(- u*x_ - v*y_ - w*z_)) * oneMinusCosT
                + x_*cosT + (- w*y_ + v*z_)*sinT);

        y = ((- v*(- u*x_ - v*y_ - w*z_)) * oneMinusCosT
                + y_*cosT + (w*x_ - u*z_)*sinT);

        z = ((- w*(- u*x_ - v*y_ - w*z_)) * oneMinusCosT
                + z_*cosT + (- v*x_ + u*y_)*sinT);

        return *this;
	}

	Type rotate(const Type& axis, const T& theta)
	{
		return Type(*this).rotateSelf(axis, theta);
	}

	void print() const
	{
		//std::cout << std::fixed << std::setprecision(2);
		std::cout << "[" << x << " " << y << " " << z << "] (" << length() << ")" ;
	}
};