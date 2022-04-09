#include "SkyBox.h"
#include "Model.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>


SkyBox::SkyBox(ID3D11Device* dev, float size)
{
	int nverts = 24;
	pVerts = new StandardVertex[nverts];
	int ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind + 0].set(size, size, size, 0.5, 0.333);
	pVerts[vind + 1].set(-size, size, size, 0.75, 0.333);
	pVerts[vind + 2].set(-size, -size, size, 0.75, 0.667);
	pVerts[vind + 3].set(size, -size, size, 0.5, 0.65);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind + 0].set(size, size, -size, 0.25, 0.333);
	pVerts[vind + 1].set(-size, size, -size, 0, 0.333);
	pVerts[vind + 2].set(-size, -size, -size, 0, 0.66);
	pVerts[vind + 3].set(size, -size, -size, 0.25, 0.66);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind + 0].set(size, size, -size, 0.25, 0.333);
	pVerts[vind + 1].set(size, size, size, 0.5, 0.333);
	pVerts[vind + 2].set(size, -size, size, 0.5, 0.65);
	pVerts[vind + 3].set(size, -size, -size, 0.25, 0.66);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind + 0].set(-size, size, size, 0.75, 0.335);
	pVerts[vind + 1].set(-size, size, -size, 1.0, 0.335);
	pVerts[vind + 2].set(-size, -size, -size, 1.0, 0.665);
	pVerts[vind + 3].set(-size, -size, size, 0.75, 0.665);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind , vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind + 0].set(size, size, -size, 0.5, 0.0);
	pVerts[vind + 1].set(-size, size, -size, 0.75, 0.0);
	pVerts[vind + 2].set(-size, size, size, 0.75, 0.333);
	pVerts[vind + 3].set(size, size, size, 0.5, 0.333);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind , vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind + 0].set(size, -size, size, 0.5, 0.6667);
	pVerts[vind + 1].set(-size, -size, size, 0.72, 0.666);
	pVerts[vind + 2].set(-size, -size, -size, 0.72, 0.99);
	pVerts[vind + 3].set(size, -size, -size, 0.5, 0.99);
	pTriList[tind].set(vind , vind + 1, vind + 2);
	pTriList[tind + 1].set(vind , vind + 2, vind + 3);

	pModel = new Model(dev, pVerts, nverts, pTriList, ntri);
}

SkyBox::~SkyBox()
{
	delete[] pVerts;
	delete[] pTriList;
	delete pModel;
}

void SkyBox::Render(ID3D11DeviceContext* context)
{
	pModel->SetToContext(context);
	pModel->Render(context);
}

Model* SkyBox::GetModel()
{
	return pModel;
}