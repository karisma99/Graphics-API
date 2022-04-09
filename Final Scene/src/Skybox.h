#ifndef _SkyBox
#define _SkyBox

#include "Matrix.h"
#include "Model.h"
#include "d3dUtil.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;
struct StandardVertex; 
struct TriangleByIndex; 

class SkyBox : public Align16
{
public:
	SkyBox(ID3D11Device* dev, float size);
	SkyBox(Model&&) = delete;
	SkyBox& operator = (const SkyBox&) & = delete;
	SkyBox& operator = (SkyBox&&) & = delete;
	~SkyBox();

	void Render(ID3D11DeviceContext* context);
	Model* GetModel();

private:
	StandardVertex* pVerts;
	TriangleByIndex* pTriList;
	Model* pModel;

};



#endif _SkyBox