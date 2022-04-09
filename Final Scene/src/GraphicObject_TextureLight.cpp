#include "GraphicObject_TextureLight.h"
#include "Model.h"
#include "ShaderTextureLight.h"
#include <assert.h>

GraphicObject_TextureLight::GraphicObject_TextureLight(ShaderTextureLight* shader, Model* mod)
{
	SetModel(mod);
	pShader = shader;
	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	pMeshTexture = new Texture * [n];
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

GraphicObject_TextureLight::~GraphicObject_TextureLight()
{
	delete[] pMeshTexture;
	delete[] MeshAmb;
	delete[] MeshDif;
	delete[] MeshSp;
}

void GraphicObject_TextureLight::SetTexture(Texture* tex)
{
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pMeshTexture[i] = tex;
	}
}

void GraphicObject_TextureLight::SetTexture(Texture* tex, int meshNum)
{
	assert(pModel->ValidMeshNum(meshNum));
	pMeshTexture[meshNum] = tex;
}

void GraphicObject_TextureLight::SetToContext(ID3D11DeviceContext* devcon)
{
	pShader->SetToContext(devcon);
}

void GraphicObject_TextureLight::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	pShader->SendCamMatrices(view, proj);
}

void GraphicObject_TextureLight::SetDirectionalLightParameters(const Vect& dir, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SetDirectionalLightParameters(dir, amb, dif, sp);
}

void GraphicObject_TextureLight::SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp, int index)
{
	pShader->SetPointLightParameters(pos, r, att, amb, dif, sp, index);
}

void GraphicObject_TextureLight::SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp, int index)
{
	pShader->SetSpotLightParameters(pos, r, att, dir, spotExp, amb, dif, sp, index);
}

void GraphicObject_TextureLight::SendLightParameters(const Vect& eyepos)
{
	pShader->SendLightParameters(eyepos);
}

void GraphicObject_TextureLight::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_TextureLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
	{
		MeshAmb[i] = amb;
		MeshDif[i] = dif;
		MeshSp[i] = sp;
	}
}

void GraphicObject_TextureLight::SetMaterial(const int meshNum, const Vect& amb, const Vect& dif, const Vect& sp)
{
	assert(pModel->ValidMeshNum(meshNum));
	MeshAmb[meshNum] = amb;
	MeshDif[meshNum] = dif;
	MeshSp[meshNum] = sp;
}

void GraphicObject_TextureLight::SendFogData(const Vect& color, const float& start, const float& range)
{
	pShader->SendFogData(color, start, range);
}

void GraphicObject_TextureLight::Render()
{
	pModel->SetToContext(pShader->GetContext());

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SetTextureResourceAndSampler(pMeshTexture[i]);
		pShader->SendWorldAndMaterial(World, MeshAmb[i], MeshDif[i], MeshSp[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}