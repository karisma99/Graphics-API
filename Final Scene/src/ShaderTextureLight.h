// ShaderTextureLight

#ifndef _ShaderTextureLight
#define _ShaderTextureLight

#include "ShaderBase.h"
#include "Matrix.h"
#include "Texture.h"
#include "d3dUtil.h"

struct ID3D11Buffer;
struct ID3D11Device;

class ShaderTextureLight : public ShaderBase
{

public:
	ShaderTextureLight(const ShaderTextureLight&) = delete;				 // Copy constructor
	ShaderTextureLight(ShaderTextureLight&&) = default;                    // Move constructor
	ShaderTextureLight& operator=(const ShaderTextureLight&) & = default;  // Copy assignment operator
	ShaderTextureLight& operator=(ShaderTextureLight&&) & = default;       // Move assignment operator
	~ShaderTextureLight();		  							         // Destructor

	ShaderTextureLight(ID3D11Device* device);

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SetTextureResourceAndSampler(Texture* tex);

	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1), const int ind = 0);
	void SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1), const int ind = 0);

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendLightParameters(const Vect& eyepos);
	void SendWorldAndMaterial(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));
	void SendFogData(const Vect& color = Colors::MidnightBlue, const float& start = 0.0f, const float& range = -1.0f);

private:
	struct Material
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};

	struct PhongADS
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};



	struct DirectionalLight
	{
		PhongADS Light;
		Vect Direction;
	};

	DirectionalLight DirLightData;

	struct PointLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		float Range;
	};

	PointLight PointLightData[3];

	struct SpotLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		Vect Direction;
		float SpotExp;
		float Range;
	};

	SpotLight SpotLightData[3];

	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer* mpBufferCamMatrices;

	struct Data_WorldAndMaterial
	{
		Matrix World;
		Matrix WorlInv;
		Material Mat;
	};

	ID3D11Buffer* mpBuffWordAndMaterial;

	struct Data_LightParams
	{
		DirectionalLight DirLight;
		PointLight PntLight[3];
		SpotLight SptLight[3];
		Vect EyePosWorld;
		int numP = 3;
		int numS = 3;
	};

	ID3D11Buffer* mpBufferLightParams;

	struct Data_Fog
	{
		Vect FogColor;
		float FogStart;
		float FogRange;
	};

	ID3D11Buffer* mpBufferFog;

};

#endif _ShaderTextureLight

