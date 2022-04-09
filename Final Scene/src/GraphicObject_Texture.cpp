#include "GraphicObject_Texture.h"
#include "Model.h"
#include <assert.h>

GraphicObject_Texture::GraphicObject_Texture(ShaderTexture* shader, Model* mod)
{
	SetModel(mod);
	pShader = shader;
	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	pMeshTexture = new Texture * [n];
	//Insert default textures?
}

GraphicObject_Texture::~GraphicObject_Texture()
{
	delete[] pMeshTexture;
}

void GraphicObject_Texture::SetToContext(ID3D11DeviceContext* devcon)
{
	pShader->SetToContext(devcon);
}

void GraphicObject_Texture::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	pShader->SendCamMatrices(view, proj);
}

void GraphicObject_Texture::SetTexture(Texture* tex)
{
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pMeshTexture[i] = tex;
	}
}

void GraphicObject_Texture::SetTexture(Texture* tex, int meshNum)
{
	assert(pModel->ValidMeshNum(meshNum));
	pMeshTexture[meshNum] = tex;
}


void GraphicObject_Texture::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_Texture::Render()
{
	pShader->SendWorld(World);
	pModel->SetToContext(pShader->GetContext());

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SetTextureResourceAndSampler(pMeshTexture[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
	
}