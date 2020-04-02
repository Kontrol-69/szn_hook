#define ANGLE_PITCH 0
#define ANGLE_YAW 1
#define ANGLE_ROLL 2

#define ANGLE2SHORT(x)          ((int)((x) * 65536 / 360) & 65535)
#define SHORT2ANGLE(x)          ((x)*(360.0 / 65536))

#define	VectorScale(v, s, o)	((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))
#define VectorCopy(a,b)			((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])

#define VectorSubtract(a,b,c)	((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define	VectorMA(v, s, b, o)	((o)[0]=(v)[0]+(b)[0]*(s),(o)[1]=(v)[1]+(b)[1]*(s),(o)[2]=(v)[2]+(b)[2]*(s))
#define DotProduct(x,y)			((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])

class math_t
{
private:
	float Forward, Pitch, Yaw;
	float Angle, SR, SP, SY, CR, CP, CY, PiDiv;
	float dDistance[3], m_iDistance;
public:
	D3DXVECTOR3 vec_to_angles(D3DXVECTOR3 angle);
	D3DXVECTOR3 angles_to_forward(D3DXVECTOR3 origin, D3DXVECTOR3 angle, float diff);

	void normalize_vector(D3DXVECTOR3& vec);
	float get_3d_distance(D3DXVECTOR3& my_coords, D3DXVECTOR3& enemy_coords);
	float get_2d_distance(D3DXVECTOR3 first, D3DXVECTOR3 second);
	float distance(D3DXVECTOR3 v1, D3DXVECTOR3 v2);

	float vector_length(D3DXVECTOR3 vector);
	float vector_distance(D3DXVECTOR3 v1, D3DXVECTOR3 v2);
}; extern math_t math;