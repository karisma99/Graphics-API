#ifndef _TerrainModel
#define _TerrainModel

#include "Matrix.h"
#include <tuple>
#include <d3d11.h>
#include "DirectXTex.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;
struct StandardVertex; 
struct TriangleByIndex;

class TerrainModel : public Align16
{

private:
	int TexelIndex(int side, int x, int z);
	int VertexIndex(int side, int x, int z);

	Model* pModTerrain;
	StandardVertex* pVerts;
	TriangleByIndex* pTri;
	Matrix World;
	size_t pixel_width;

public:
	TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV);
	TerrainModel(Model&&) = delete;
	TerrainModel& operator = (const TerrainModel&) & = delete;
	TerrainModel& operator = (TerrainModel&&) & = delete;
	~TerrainModel();

	void Render(ID3D11DeviceContext* context);
	Model* GetModel();
	Matrix GetWorld();

};



#endif _TerrainModel