#include "szn.h"

math_t math;

D3DXVECTOR3 math_t::vec_to_angles(D3DXVECTOR3 angle)
{
	if (angle.x == 0.f && angle.y == 0.f)
	{
		this->Yaw = 0.f;

		if (angle.z > 0.f)
			this->Pitch = 90.f;
		else
			this->Pitch = 270.f;
	}
	else
	{
		if (angle.z != -1.f)
			this->Yaw = (float)atan2((double)angle.y, (double)angle.x) * 180.f / D3DX_PI;
		else if (angle.y > 0.f)
			this->Yaw = 90.f;
		else
			this->Yaw = 270.f;

		if (this->Yaw < 0.f)
			this->Yaw += 360.f;

		this->Forward = (float)sqrt((double)(angle.x * angle.x + angle.y * angle.y));
		this->Pitch = (float)(atan2((double)angle.z, (double)this->Forward) * 180.f / D3DX_PI);

		if (this->Pitch < 0.f)
			this->Pitch += 360.f;
	}

	D3DXVECTOR3 AnglesVector(-this->Pitch, this->Yaw, 0);
	return AnglesVector;
}

D3DXVECTOR3 math_t::angles_to_forward(D3DXVECTOR3 origin, D3DXVECTOR3 angle, float diff)
{
	this->PiDiv = ((float)D3DX_PI / 180.f);
	this->Angle = angle.y * this->PiDiv;

	this->SY = (float)sinf(this->Angle);
	this->CY = (float)cosf(this->Angle);

	this->Angle = (angle.x * this->PiDiv);

	this->SP = (float)sinf(this->Angle);
	this->CP = (float)cosf(this->Angle);

	this->Angle = (angle.y * this->PiDiv);

	this->SR = (float)sinf(this->Angle);
	this->CR = (float)cosf(this->Angle);

	D3DXVECTOR3 Retn((this->CP * this->CY * diff) + origin.x, (this->CP * this->SY * diff) + origin.y, (-this->SP * diff) + origin.z);
	return Retn;
}

void math_t::normalize_vector(D3DXVECTOR3& vec)
{
	float totalLength = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	vec.x /= totalLength;
	vec.y /= totalLength;
	vec.z /= totalLength;
}

float math_t::get_3d_distance(D3DXVECTOR3& my_coords, D3DXVECTOR3& enemy_coords)
{
	return sqrtf(
		powf((enemy_coords.x - my_coords.x), 2.0) +
		powf((enemy_coords.y - my_coords.y), 2.0) +
		powf((enemy_coords.z - my_coords.z), 2.0)
		);
}

float math_t::get_2d_distance(D3DXVECTOR3 first, D3DXVECTOR3 second)
{
	float disX = first.x - second.x, disY = first.y - second.y, disZ = first.z - second.z;
	return (float)sqrt((disX * disX) + (disY * disY) + (disZ * disZ)) * 0.03048f;
}

float math_t::distance(D3DXVECTOR3 v1, D3DXVECTOR3 v2)
{
	this->dDistance[0] = v1.x - v2.x;
	this->dDistance[1] = v1.y - v2.y;
	this->dDistance[2] = v1.z - v2.z;

	this->m_iDistance = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	return (this->m_iDistance / 40.f);
}


float math_t::vector_length(D3DXVECTOR3 vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

float math_t::vector_distance(D3DXVECTOR3 v1, D3DXVECTOR3 v2)
{
	D3DXVECTOR3 subtracted;

	VectorSubtract(v2, v1, subtracted);
	return this->vector_length(subtracted);
}