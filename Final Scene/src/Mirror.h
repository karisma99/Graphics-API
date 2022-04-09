// Mirror

#ifndef _Mirror
#define _Mirror

#include <Windows.h>
#include <string>
#include <d3d11.h>
#include "DirectXTex.h"
#include "Matrix.h"
#include "FlatPlane.h"
#include "ShaderColor.h"
#include "ShaderTextureLight.h"
#include "ShaderColorLight.h"

class Mirror
{
public:
	Mirror(const Mirror&) = delete;				 // Copy constructor
	Mirror(Mirror&&) = delete;                    // Move constructor
	Mirror& operator=(const Mirror&) & = delete;  // Copy assignment operator
	Mirror& operator=(Mirror&&) & = delete;       // Move assignment operator
	~Mirror();									     // Destructor
	Mirror() = delete;

	Mirror(ID3D11Device* d3dDev, FlatPlane* model, Matrix mat);

	void RenderFront(ID3D11DeviceContext* devcon, ShaderColor* pShader);
	void RenderBehind(ID3D11DeviceContext* devcon, ShaderColor* pShader);

	void RenderFront(ID3D11DeviceContext* devcon, ShaderColorLight* pShader, const Matrix& view, const Matrix& proj, const Vect& eyepos);
	void RenderBehind(ID3D11DeviceContext* devcon, ShaderColorLight* pShader, const Matrix& view, const Matrix& proj, const Vect& eyepos);

	void RenderFront(ID3D11DeviceContext* devcon, ShaderTextureLight* pShader, Texture* tex, const Matrix & view, const Matrix & proj, const Vect & eyepos);
	void RenderBehind(ID3D11DeviceContext* devcon, ShaderTextureLight* pShader, Texture* tex, const Matrix& view, const Matrix& proj, const Vect& eyepos);

	Matrix GetMatrix();

private:
	Matrix mMatrix;
	Matrix ReflectionMat;
	FlatPlane* pMirror;

	ID3D11DepthStencilState* MarkMirrorDSS;
	ID3D11DepthStencilState* DrawReflectionDSS;
	ID3D11RasterizerState* FrontFaceAsCCWRS;
	ID3D11RasterizerState* MirrorFrontFaceAsClockWiseRS;
	ID3D11BlendState* NoWriteToRenderTargetBS;
	ID3D11BlendState* TransparentBS;


};

#endif _Mirror