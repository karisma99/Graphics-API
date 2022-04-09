// GraphicObject_TextureLight

#ifndef _GraphicObject_TextureLight
#define _GraphicObject_TextureLight

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "Texture.h"
#include "d3dUtil.h"

class ShaderTextureLight;

class GraphicObject_TextureLight : public GraphicObject_Base
{
	friend class ShaderTextureLight;

public:
	GraphicObject_TextureLight(const GraphicObject_TextureLight&) = delete;				 // Copy constructor
	GraphicObject_TextureLight(GraphicObject_TextureLight&&) = default;                    // Move constructor
	GraphicObject_TextureLight& operator=(const GraphicObject_TextureLight&) & = default;  // Copy assignment operator
	GraphicObject_TextureLight& operator=(GraphicObject_TextureLight&&) & = default;       // Move assignment operator
	~GraphicObject_TextureLight();		  											 // Destructor

	GraphicObject_TextureLight() = delete;

	void SetTexture(Texture* tex);
	void SetTexture(Texture* tex, int meshNum);

	void SetToContext(ID3D11DeviceContext* devcon);
	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1), int index = 0);
	void SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1), int index = 0);
	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendLightParameters(const Vect& eyepos);
	void SetWorld(const Matrix& m);
	void SetMaterial(const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));
	void SetMaterial(const int meshNum, const Vect& amb, const Vect& dif, const Vect& sp);
	void SendFogData(const Vect& color = Colors::MidnightBlue, const float& start = 0.0f, const float& range = -1.0f);

	virtual void Render() override;

	GraphicObject_TextureLight(ShaderTextureLight* shader, Model* mod);

private:
	ShaderTextureLight* pShader;
	Texture** pMeshTexture;
	Matrix World;
	Vect* MeshAmb;
	Vect* MeshSp;
	Vect* MeshDif;

};

#endif _GraphicObject_TextureLight
