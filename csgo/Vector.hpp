#pragma once

typedef float matrix3x4_t[3][4];

//#define VECTOR_NO_SLOW_OPERATIONS

enum
{
	PITCH = 0,	// up / down
	YAW,		// left / right
	ROLL		// fall over
};

struct vec2
{
	float x, y;

	vec2() noexcept : x(0.f), y(0.f) {}

	vec2(float xx, float yy) : x(xx), y(yy) {}

#ifdef VECTOR_NO_SLOW_OPERATIONS
private:
#endif
	vec2(const vec2& vec) : x(vec.x), y(vec.y) {}
public:

	inline bool isZero() const { return (*reinterpret_cast<const int*>(&x) == 0 && *reinterpret_cast<const int*>(&y) == 0); }

	inline float Length() const { return sqrt(x * x + y * y); }

	vec2& operator*=(const vec2& vec) { x *= vec.x; y *= vec.y; return *this; }
	vec2& operator*=(float fl) { x *= fl; y *= fl; return *this; }

	vec2& operator/=(const vec2& vec) { x /= vec.x; y /= vec.y; return *this; }
	vec2& operator/=(float fl) { x /= fl; y /= fl; return *this; }

	vec2& operator+=(const vec2& vec) { x += vec.x; y += vec.y; return *this; }
	//vec2& operator+=(float fl) { x += fl; y += fl; return *this; }

	vec2& operator-=(const vec2& vec) { x -= vec.x; y -= vec.y; return *this; }
	//vec2& operator-=(float fl) { x -= fl; y -= fl; return *this; }
};
#ifndef VECTOR_NO_SLOW_OPERATIONS
inline vec2 operator*(vec2 vec0, const vec2& vec1) { return vec0 *= vec1; }
inline vec2 operator*(vec2 vec, float fl) { return vec *= fl; }

inline vec2 operator/(vec2 vec0, const vec2& vec1) { return vec0 /= vec1; }
inline vec2 operator/(vec2 vec, float fl) { return vec /= fl; }

inline vec2 operator+(vec2 vec0, const vec2& vec1) { return vec0 += vec1; }
//inline vec2 operator+(vec2 vec, float fl) { return vec += fl; }

inline vec2 operator-(vec2 vec0, const vec2& vec1) { return vec0 -= vec1; }
//inline vec2 operator-(vec2 vec, float fl) { return vec -= fl; }

#else

inline void VectorAdd(const vec2& a, const vec2& b, vec2& res)
{
	res.x = a.x + b.x;
	res.y = a.y + b.y;
}

inline void VectorSubtract(const vec2& a, const vec2& b, vec2& res)
{
	res.x = a.x - b.x;
	res.y = a.y - b.y;
}

inline void VectorMultiply(const vec2& a, float b, vec2& res)
{
	res.x = a.x * b;
	res.y = a.y * b;
}

inline void VectorMultiply(const vec2& a, const vec2& b, vec2& res)
{
	res.x = a.x * b.x;
	res.y = a.y * b.y;
}

inline void VectorDivide(const vec2& a, float b, vec2& res)
{
	float oob = 1.0f / b;
	res.x = a.x * oob;
	res.y = a.y * oob;
}

inline void VectorDivide(const vec2& a, const vec2& b, vec2& res)
{
	res.x = a.x / b.x;
	res.y = a.y / b.y;
}
#endif

//inline float DotProduct(const vec2& vec0, const vec2& vec1)
//{
//	return (vec0.x * vec1.x + 
//			vec0.y * vec1.y);
//}

inline float VectorNormalize(vec2& v)
{
	float l = v.Length();
	if (l != 0.f)
		v /= l;
	else
		v.x = v.y = 0.f;
	return l;
}

//void AngleVectors(const vec2& angles, vec2* forward)
//{
//	float radPitch = DEG2RAD(angles.x),
//		radYaw = DEG2RAD(angles.y);
//
//	float cp = cos(radPitch);
//
//	forward->x = cp * cos(radYaw);
//	forward->y = cp * sin(radYaw);
//}



struct vec3
{
	float x, y, z;

	vec3() noexcept : x(0.f), y(0.f), z(0.f) {}

	vec3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}

#ifdef VECTOR_NO_SLOW_OPERATIONS
private:
#endif
	vec3(const vec3& vec) : x(vec.x), y(vec.y), z(vec.z) {}
public:

	inline bool isZero() const { return (*reinterpret_cast<const int*>(&x) == 0 && *reinterpret_cast<const int*>(&y) == 0 && *reinterpret_cast<const int*>(&z) == 0); }

	inline float Length() const { return sqrt(x * x + y * y + z * z); }
	inline float Length2D() const { return sqrt(x * x + y * y); }
	inline float LengthSqr() const { return (x * x + y * y); }

	vec3& operator*=(const vec3& vec) { x *= vec.x; y *= vec.y; z *= vec.z; return *this; }
	vec3& operator*=(float fl) { x *= fl; y *= fl; z *= fl; return *this; }

	vec3& operator/=(const vec3& vec) { x /= vec.x; y /= vec.y; z /= vec.z; return *this; }
	vec3& operator/=(float fl) { x /= fl; y /= fl; z /= fl; return *this; }

	vec3& operator+=(const vec3& vec) { x += vec.x; y += vec.y; z += vec.z; return *this; }
	//vec3& operator+=(float fl) { x += fl; y += fl; z += fl; return *this; }

	vec3& operator-=(const vec3& vec) { x -= vec.x; y -= vec.y; z -= vec.z; return *this; }
	//vec3& operator-=(float fl) { x -= fl; y -= fl; z -= fl; return *this; }
};
#ifndef VECTOR_NO_SLOW_OPERATIONS
inline vec3 operator*(vec3 vec0, const vec3& vec1) { return vec0 *= vec1; }
inline vec3 operator*(vec3 vec, float fl) { return vec *= fl; }

inline vec3 operator/(vec3 vec0, const vec3& vec1) { return vec0 /= vec1; }
inline vec3 operator/(vec3 vec, float fl) { return vec /= fl; }

inline vec3 operator+(vec3 vec0, const vec3& vec1) { return vec0 += vec1; }
//inline vec3 operator+(vec3 vec, float fl) { return vec += fl; }

inline vec3 operator-(vec3 vec0, const vec3& vec1) { return vec0 -= vec1; }
//inline vec3 operator-(vec3 vec, float fl) { return vec -= fl; }

#else

inline void VectorAdd(const vec3& a, const vec3& b, vec3& res)
{
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
}

inline void VectorSubtract(const vec3& a, const vec3& b, vec3& res)
{
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
}

inline void VectorMultiply(const vec3& a, float b, vec3& res)
{
	res.x = a.x * b;
	res.y = a.y * b;
	res.z = a.z * b;
}

inline void VectorMultiply(const vec3& a, const vec3& b, vec3& res)
{
	res.x = a.x * b.x;
	res.y = a.y * b.y;
	res.z = a.z * b.z;
}

inline void VectorDivide(const vec3& a, float b, vec3& res)
{
	float oob = 1.0f / b;
	res.x = a.x * oob;
	res.y = a.y * oob;
	res.z = a.z * oob;
}

inline void VectorDivide(const vec3& a, const vec3& b, vec3& res)
{
	res.x = a.x / b.x;
	res.y = a.y / b.y;
	res.z = a.z / b.z;
}
#endif

//inline float VectorDistance(const vec3& start, const vec3& end)
//{
//	return Fsqrt((start.x - end.x) * (start.x - end.x) +
//		(start.y - end.y) * (start.y - end.y) +
//		(start.z - end.z) * (start.z - end.z));
//}

//inline float DotProduct(const float* vec0, const float* vec1)
//{
//	return (vec0[0] * vec1[0] +
//		vec0[1] * vec1[1] +
//		vec0[2] * vec1[2]);
//}

//inline float VectorNormalize(vec3& v)
//{
//	float l = v.Length();
//	if (l != 0.f)
//		v /= l;
//	else
//	{
//		v.x = v.y = 0.f;
//		v.z = 1.f;
//	}
//	return l;
//}

//void AngleVectors(const vec3& angles, vec3* forward)
//{
//	float radPitch = DEG2RAD(angles.x),
//		radYaw = DEG2RAD(angles.y);
//
//	float cp = cos(radPitch);
//
//	forward->x = cp * cos(radYaw);
//	forward->y = cp * sin(radYaw);
//	forward->z = -sin(radPitch);
//}

void AngleVectors(const vec3& angles, vec2* forward, vec2* right, vec2* up)
{
	float radPitch = DEG2RAD(angles.x),
		radYaw = DEG2RAD(angles.y),
		radRoll = DEG2RAD(angles.z);

	float sp = sin(radPitch),
		cp = cos(radPitch);

	float sy = sin(radYaw),
		cy = cos(radYaw);

	float sr = sin(radRoll),
		cr = cos(radRoll);

	if (forward)
	{
		forward->x = cp * cy;
		forward->y = cp * sy;
	}

	if (right)
	{
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
	}

	if (up)
	{
		up->x = (cr*sp*cy + -sr * -sy);
		up->y = (cr*sp*sy + -sr * cy);
	}
}

//void AngleVectors(const vec3& angles, vec3* forward, vec3* right, vec3* up)
//{
//	float radPitch = DEG2RAD(angles.x),
//		radYaw = DEG2RAD(angles.y),
//		radRoll = DEG2RAD(angles.z);
//
//	float sp = sin(radPitch),
//		cp = cos(radPitch);
//
//	float sy = sin(radYaw),
//		cy = cos(radYaw);
//
//	float sr = sin(radRoll),
//		cr = cos(radRoll);
//
//	if (forward)
//	{
//		forward->x = cp * cy;
//		forward->y = cp * sy;
//		forward->z = -sp;
//	}
//
//	if (right)
//	{
//		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
//		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
//		right->z = -1 * sr*cp;
//	}
//
//	if (up)
//	{
//		up->x = (cr*sp*cy + -sr * -sy);
//		up->y = (cr*sp*sy + -sr * cy);
//		up->z = cr * cp;
//	}
//}

//void VectorAngles(const vec3& forward, vec2& angles)
//{
//	float pitch, yaw;
//
//	if (forward.y == 0.f && forward.x == 0.f)
//	{
//		if (forward.z > 0.f)
//			pitch = 270.f;
//		else
//			pitch = 90.f;
//
//		yaw = 0.f;
//	}
//	else
//	{
//		pitch = RAD2DEG(atan2(-forward.z, forward.Length2D()));
//		if (pitch < 0.f)
//			pitch += 360.f;
//
//		yaw = RAD2DEG(atan2(forward.y, forward.x));
//		if (yaw < 0.f)
//			yaw += 360.f;
//	}
//
//	angles.x = pitch;
//	angles.y = yaw;
//}

inline void ClampAngle(float* ang)
{
	if (ang[0] > 89.f) ang[0] = 89.f;
	else if (ang[0] < -89.f) ang[0] = -89.f;
	while (ang[1] > 180.f) ang[1] -= 360.f;
	while (ang[1] < -180.f) ang[1] += 360.f;
}

void DegreeByCenter(float* vec, const vec3& center, float deg)
{
	vec[0] -= center.x;
	vec[1] -= center.y;

	const float radius = sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
	const float rad = DEG2RAD(deg);

	vec[0] = radius * cos(rad);
	vec[1] = radius * sin(rad);

	vec[0] += center.x;
	vec[1] += center.y;
}

inline vec2 CalcAngle(const vec3& posDelta, float posDeltaLength)
{
	return { RAD2DEG(-asin(posDelta.z / posDeltaLength)),
			RAD2DEG(atan2(posDelta.y, posDelta.x)) };
}

inline vec2 CalcAngle(const vec3& localPos, const vec3& enemyPos)
{
	const vec3 posDelta(enemyPos - localPos);
	return { RAD2DEG(-asin(posDelta.z / posDelta.Length())),
			RAD2DEG(atan2(posDelta.y, posDelta.x)) };
}

float GetFOV(const vec2& localAngles, const vec2& enemyAngles)
{
	vec2 anglesDelta(enemyAngles - localAngles);
	ClampAngle(&anglesDelta.x);

	float anglesDeltaLen = anglesDelta.Length();
	if (anglesDeltaLen > 180.f)
		anglesDeltaLen = 360.f - anglesDeltaLen;

	return anglesDeltaLen;
}

// Math routines done in optimized assembly math package routines
//void inline SinCos(float radians, float *sine, float *cosine)
//{
//	_asm
//	{
//		fld		DWORD PTR[radians]
//		fsincos
//
//		mov edx, DWORD PTR[cosine]
//		mov eax, DWORD PTR[sine]
//
//		fstp DWORD PTR[edx]
//		fstp DWORD PTR[eax]
//	}
//}
//
//void AngleMatrix(const vec3 &angles, matrix3x4_t& matrix)
//{
//	float sr, sp, sy, cr, cp, cy;
//
//	SinCos(DEG2RAD(angles.y), &sy, &cy);
//	SinCos(DEG2RAD(angles.x), &sp, &cp);
//	SinCos(DEG2RAD(angles.z), &sr, &cr);
//
//	// matrix = (YAW * PITCH) * ROLL
//	matrix[0][0] = cp * cy;
//	matrix[1][0] = cp * sy;
//	matrix[2][0] = -sp;
//
//	float crcy = cr * cy;
//	float crsy = cr * sy;
//	float srcy = sr * cy;
//	float srsy = sr * sy;
//	matrix[0][1] = sp * srcy - crsy;
//	matrix[1][1] = sp * srsy + crcy;
//	matrix[2][1] = sr * cp;
//
//	matrix[0][2] = (sp*crcy + srsy);
//	matrix[1][2] = (sp*crsy - srcy);
//	matrix[2][2] = cr * cp;
//
//	matrix[0][3] = 0.0f;
//	matrix[1][3] = 0.0f;
//	matrix[2][3] = 0.0f;
//}
//
//void MatrixSetColumn(const vec3 &in, int column, matrix3x4_t& out)
//{
//	out[0][column] = in.x;
//	out[1][column] = in.y;
//	out[2][column] = in.z;
//}
//
//void AngleMatrix(const vec3 &angles, const vec3 &position, matrix3x4_t& matrix)
//{
//	AngleMatrix(angles, matrix);
//	MatrixSetColumn(position, 3, matrix);
//}
//
//// rotate by the inverse of the matrix
//void VectorIRotate(const float *in1, const matrix3x4_t& in2, float *out)
//{
//	out[0] = in1[0] * in2[0][0] + in1[1] * in2[1][0] + in1[2] * in2[2][0];
//	out[1] = in1[0] * in2[0][1] + in1[1] * in2[1][1] + in1[2] * in2[2][1];
//	out[2] = in1[0] * in2[0][2] + in1[1] * in2[1][2] + in1[2] * in2[2][2];
//}
//
//inline void VectorIRotate(const vec3& in1, const matrix3x4_t &in2, vec3 &out)
//{
//	VectorIRotate(&in1.x, in2, &out.x);
//}
//
//// assuming the matrix is orthonormal, transform in1 by the transpose (also the inverse in this case) of in2.
//void VectorITransform(const float *in1, const matrix3x4_t& in2, float *out)
//{
//	float in1t[3];
//
//	in1t[0] = in1[0] - in2[0][3];
//	in1t[1] = in1[1] - in2[1][3];
//	in1t[2] = in1[2] - in2[2][3];
//
//	out[0] = in1t[0] * in2[0][0] + in1t[1] * in2[1][0] + in1t[2] * in2[2][0];
//	out[1] = in1t[0] * in2[0][1] + in1t[1] * in2[1][1] + in1t[2] * in2[2][1];
//	out[2] = in1t[0] * in2[0][2] + in1t[1] * in2[1][2] + in1t[2] * in2[2][2];
//}
//
//inline void VectorITransform(const vec3& in1, const matrix3x4_t &in2, vec3 &out)
//{
//	VectorITransform(&in1.x, in2, &out.x);
//}
//
//FORCEINLINE float DotProduct(const float *v1, const float *v2)
//{
//	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
//}
//
//// assume in2 is a rotation and rotate the input vector
//void VectorRotate(const float *in1, const matrix3x4_t& in2, float *out)
//{
//	out[0] = DotProduct(in1, in2[0]);
//	out[1] = DotProduct(in1, in2[1]);
//	out[2] = DotProduct(in1, in2[2]);
//}
//
//inline void VectorRotate(const vec3& in1, const matrix3x4_t &in2, vec3 &out)
//{
//	VectorRotate(&in1.x, in2, &out.x);
//}