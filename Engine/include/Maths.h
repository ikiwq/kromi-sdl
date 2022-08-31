#pragma once
#include <math.h>

//This is just a simple Math header to implement some Vectors

struct Vector2 {
	float x;
	float y;

	Vector2(float x_ = 0.0f, float y_ = 0.0f)
		:x(x_), y(y_) {}

	float MagnitudeSqr() {
		return(x * x + y * y);
	}

	float Magnitude() {
		return float(sqrt(x * x + y * y));
	}

	Vector2 Normalized() {
		float mag = Magnitude();

		return Vector2(x / mag, y / mag);
	}
};

inline Vector2 operator +(const Vector2& leftVec, const Vector2& rightVec) {
	return Vector2(leftVec.x + rightVec.x, leftVec.y + rightVec.y);
}

inline Vector2 operator -(const Vector2& leftVec, const Vector2& rightVec) {
	return Vector2(leftVec.x - rightVec.x, leftVec.y - rightVec.y);
}

inline Vector2 operator *(const Vector2& leftVec, const Vector2& rightVec) {
	return Vector2(leftVec.x * rightVec.x, leftVec.y * rightVec.y);
}

inline Vector2 operator /(const Vector2& leftVec, const Vector2& rightVec) {
	return Vector2(leftVec.x / rightVec.x, leftVec.y / rightVec.y);
}

inline Vector2 operator+(const Vector2& leftVec, const int& num) {
	return Vector2(leftVec.x + num, leftVec.y + num);
}

inline Vector2 operator-(const Vector2& leftVec, const int& num) {
	return Vector2(leftVec.x - num, leftVec.y - num);
}

inline Vector2 operator*(const Vector2& leftVec, const int& num) {
	return Vector2(leftVec.x * num, leftVec.y * num);
}

inline Vector2 operator/(const Vector2& leftVec, const int& num) {
	return Vector2(leftVec.x / num, leftVec.y / num);
}

inline Vector2 operator - (const Vector2& leftVec) {
	return Vector2(-leftVec.x, -leftVec.y);
}

struct Vector3 {
	float x;
	float y;
	float z;

	Vector3(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f)
		:x(x_), y(y_),z(z_) {}

	float MagnitudeSqr() {
		return(x * x + y * y + z * z);
	}

	float Magnitude() {
		return float(sqrt(x * x + y * y + z * z));
	}

	Vector3 Normalized() {
		float mag = Magnitude();

		return Vector3(x / mag, y / mag, z / mag);
	}
};

inline Vector3 operator +(const Vector3& leftVec, const Vector3& rightVec) {
	return Vector3(leftVec.x + rightVec.x, leftVec.y + rightVec.y, leftVec.z + rightVec.z);
}

inline Vector3 operator -(const Vector3& leftVec, const Vector3& rightVec) {
	return Vector3(leftVec.x - rightVec.x, leftVec.y - rightVec.y, leftVec.z + rightVec.z);
}

inline Vector3 operator *(const Vector3& leftVec, const Vector3& rightVec) {
	return Vector3(leftVec.x * rightVec.x, leftVec.y * rightVec.y, leftVec.z * rightVec.z);
}

inline Vector3 operator /(const Vector3& leftVec, const Vector3& rightVec) {
	return Vector3(leftVec.x / rightVec.x, leftVec.y / rightVec.y, leftVec.z / rightVec.z);
}