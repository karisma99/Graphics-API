// GraphicObject_ColorLight

#ifndef _GraphicObject_ColorLight
#define _GraphicObject_ColorLight

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColorLight.h"
#include "Texture.h"

class GraphicObject_ColorLight : public GraphicObject_Base
{
	friend class ShaderColorLight;

public:
	GraphicObject_ColorLight(const GraphicObject_ColorLight&) = delete;				 // Copy constructor
	GraphicObject_ColorLight(GraphicObject_ColorLight&&) = default;                    // Move constructor
	GraphicObject_ColorLight& operator=(const GraphicObject_ColorLight&) & = default;  // Copy assignment operator
	GraphicObject_ColorLight& operator=(GraphicObject_ColorLight&&) & = default;       // Move assignment operator
	~GraphicObject_ColorLight();		  											 // Destructor

	GraphicObject_ColorLight() = delete;

	void SetToContext(ID3D11DeviceContext* devcon);
	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendLightParameters(const Vect& eyepos);
	void SetWorld(const Matrix& m);
	void SetMaterial(const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));
	void SetMaterial(const int meshNum, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));
	void SendFogData(const Vect& color = Colors::MidnightBlue, const float& start = 0.0f, const float& range = -1.0f);

	virtual void Render() override;

	GraphicObject_ColorLight(ShaderColorLight* shader, Model* mod);

private:
	ShaderColorLight* pShader;
	Matrix World;
	Vect* MeshAmb;
	Vect* MeshSp;
	Vect* MeshDif;

};

#endif _GraphicObject_ColorLight
