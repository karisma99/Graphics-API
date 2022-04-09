#include "GraphicObject_ColorLight.h"
#include "Model.h"
#include <assert.h>

GraphicObject_ColorLight::GraphicObject_ColorLight(ShaderColorLight* shader, Model* mod)
{
	SetModel(mod);
	pShader = shader;
	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount(); 
	MeshAmb = new Vect[n];
	MeshDif = new Vect[n];
	MeshSp = new Vect[n];

	for (int i = 0; i < n; i++)
	{
		MeshAmb[i] = Vect(0, 0, 0);
		MeshDif[i] = Vect(0, 0, 0);
		MeshSp[i] = Vect(0, 0, 0);
	}
}

GraphicObject_ColorLight::~GraphicObject_ColorLight()
{
	delete[] MeshAmb;
	delete[] MeshDif;
	delete[] MeshSp;
}

void GraphicObject_ColorLight::SetToContext(ID3D11DeviceContext* devcon)
{
	pShader->SetToContext(devcon);
}

void GraphicObject_ColorLight::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	pShader->SendCamMatrices(view, proj);
}

void GraphicObject_ColorLight::SetDirectionalLightParameters(const Vect& dir, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SetDirectionalLightParameters(dir, amb, dif, sp);
}

void GraphicObject_ColorLight::SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SetPointLightParameters(pos, r, att, amb, dif, sp);
}

void GraphicObject_ColorLight::SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SetSpotLightParameters(pos, r, att, dir, spotExp, amb, dif, sp);
}

void GraphicObject_ColorLight::SendLightParameters(const Vect& eyepos)
{
	pShader->SendLightParameters(eyepos);
}

void GraphicObject_ColorLight::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_ColorLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
	{
		MeshAmb[i] = amb;
		MeshDif[i] = dif;
		MeshSp[i] = sp;
	}
}

void GraphicObject_ColorLight::SetMaterial(const int meshNum, const Vect& amb, const Vect& dif, const Vect& sp)
{
	assert(pModel->ValidMeshNum(meshNum));
	MeshAmb[meshNum] = amb;
	MeshDif[meshNum] = dif;
	MeshSp[meshNum] = sp;
	
}

void GraphicObject_ColorLight::SendFogData(const Vect& color, const float& start, const float& range)
{
	pShader->SendFogData(color, start, range);
}

void GraphicObject_ColorLight::Render()
{
	pModel->SetToContext(pShader->GetContext());

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendWorldAndMaterial(World, MeshAmb[i], MeshDif[i], MeshSp[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}