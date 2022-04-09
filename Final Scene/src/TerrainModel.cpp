#include "TerrainModel.h"
#include "Model.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>


TerrainModel::TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
	assert(SUCCEEDED(hr));

	const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width);

	size_t side = hgtmap->height;	// the image should be square
	pixel_width = 4;			// 4 bytes RGBA per pixel
	//uint8_t h_val = hgtmap->pixels[TexelIndex(side, 3, 5)]; // the 'R' byte of the pixel at (3,5)


	// ** much work to add below **
	int numVerts = (int)len * (int)len;
	pVerts = new StandardVertex[numVerts];
	int numTri = ((int)len - 1) * ((int)len - 1) * 2;
	pTri = new TriangleByIndex[numTri];

	//Avoiding repeating calculations
	float imageScale = len / side;
	float yScale = (255 / maxheight);
	float repU = RepeatU / (len - 1);
	float repV = RepeatV / (len - 1);

	//Set Vertices
	for (float x = -len / 2, i = 0; x < len / 2; x++, i++)
	{
		for (float z = -len / 2, j = 0; z < len / 2; z++, j++)
		{
			pVerts[VertexIndex(len, i, j)].set(
				(float)x,
				hgtmap->pixels[TexelIndex(side, i / imageScale, j / imageScale)] / yScale,
				(float)z,
				(float)x * repU,
				(float)z * repV);
		}
	}

	//Set triangles (winding)
	int index = 0;
	Vect up, down, left, right, dright, dleft;
	for (int i = 0; i < len - 1; i++)
	{

		for (int j = 0; j < len - 1; j++)
		{
			pTri[index++].set(j + (len * i) + 1, j + len + (len * i), j + (len * i));
			pTri[index++].set(j + (len * i) + 1, j + len + (len * i) + 1, j + len + (len * i));

			if (i != 0 && j != 0 && i != len - 2 && j != len - 2) //dont care about edges
			{
				left = pVerts[VertexIndex(len, i, j)].Pos - pVerts[VertexIndex(len, i - 1, j)].Pos;
				right = pVerts[VertexIndex(len, i, j)].Pos - pVerts[VertexIndex(len, i + 1, j)].Pos;
				up = pVerts[VertexIndex(len, i, j)].Pos - pVerts[VertexIndex(len, i, j + 1)].Pos;
				down = pVerts[VertexIndex(len, i, j)].Pos - pVerts[VertexIndex(len, i, j - 1)].Pos;
				dright = pVerts[VertexIndex(len, i, j)].Pos - pVerts[VertexIndex(len, i - 1, j + 1)].Pos;
				dleft = pVerts[VertexIndex(len, i, j)].Pos - pVerts[VertexIndex(len, i + 1, j - 1)].Pos;

				pVerts[VertexIndex(len, i, j)].normal = ((up.cross(dright) + dright.cross(right) + right.cross(down) +
					down.cross(dleft) + dleft.cross(left) + left.cross(up)) * (1.0f / 6.0f)).getNorm();
			}
		}
	}

	World = Matrix(TRANS, 0, ytrans, 0);
	pModTerrain = new Model(dev, pVerts, numVerts, pTri, numTri);

}

TerrainModel::~TerrainModel()
{
	delete[] pVerts;
	delete[] pTri;
	delete pModTerrain;
}

void TerrainModel::Render(ID3D11DeviceContext* context)
{
	pModTerrain->SetToContext(context);
	pModTerrain->Render(context);
}

int TerrainModel::TexelIndex(int side, int a, int b)
{
	return pixel_width * (b * side + a);
}

int TerrainModel::VertexIndex(int side, int x, int z)
{
	return z * side + x;
}

Matrix TerrainModel::GetWorld()
{
	return this->World;
}

Model* TerrainModel::GetModel()
{
	return this->pModTerrain;
}