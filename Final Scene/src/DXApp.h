// DXApp
// Andre Berthiaume, June 2016
// Note: DX 11 SDK https://www.microsoft.com/en-us/download/details.aspx?id=6812
// Note on weird stuff with swap chain (1s and 2s) https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include <string>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"
#include "ShaderColor.h"
#include "ShaderTexture.h"
#include "ShaderColorLight.h"
#include "ShaderTextureLight.h"
#include "Mirror.h"

class Model;
class Texture;
class FlatPlane;
class TerrainModel;
class Skybox;
class SkyBox;
class GraphicObject_Color;
class GraphicObject_Texture;
class GraphicObject_ColorLight;
class GraphicObject_TextureLight;


class DXApp : public Align16
{
private:	
	// Main window handle
	HWND      mhMainWnd;

	Vect BackgroundColor;

	// DX application elements
	ID3D11Device* md3dDevice;					// Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
	IDXGISwapChain* mSwapChain;					// image buffers used for rendering
	ID3D11RenderTargetView* mRenderTargetView;	// Where to send rendring operations (typically: points to one of the swap buffers)
	ID3D11DepthStencilView* mpDepthStencilView; // Needed to force depth-buffer operations

	GameTimer mTimer;
	std::string mMainWndCaption;
	int mClientWidth;
	int mClientHeight;


	//Cleaning up with functions
	void SetShaders(); 
	void SetModels(); 
	void SetTextures(); 
	void CreateGraphicObjects();
	void CreateWorlds();
	void SetStationaryLights();
	void SetMovingLights(Vect eyepos);
	void RenderRelection(Vect eyepos);

	void InitDirect3D();
	void InitDemo();
	void UpdateScene();
	void DrawScene();
	void CalculateFrameStats();

	// Shader loading utility. SHould be moved elsewhere later...
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// Debug utility
	void ReportLiveDXObjects();

	// Demo specific additions
	Camera mCam;

	//Graphic Objects
	GraphicObject_TextureLight* pGO_Clownfish; 
	GraphicObject_TextureLight* pGO_Terrain; 
	GraphicObject_TextureLight* pGO_Volcano; 
	GraphicObject_Texture* pGO_SkyBox; 
	GraphicObject_Color* pGO_Starfish; 
	GraphicObject_ColorLight* pGO_Bubble1; 
	GraphicObject_ColorLight* pGO_Bubble2; 

	//Textures
	Texture* pTexTerrain; 
	Texture* pTexSkybox; 
	Texture* pTexClownfish; 
	Texture* pTexVolcano; 


	//Models
	FlatPlane* pModelMirror;
	TerrainModel* pModelTerrain; 
	SkyBox* pModelSkybox; 
	Model* pModelClownfish;
	Model* pModelVolcano;
	Model* pModelStarfish;
	Model* pModelBubble; 
	Model* pModel2;

	//Shaders
	ShaderColor* pShaderCol;
	ShaderTexture* pShaderTex; 
	ShaderColorLight* pShaderColLight;
	ShaderTextureLight* pShaderTexLight;

	//Worlds
	Matrix mWorldSkybox; 
	Matrix mWorldTerrain;
	Matrix mWorldSportLight;
	Matrix mWorldMirror;
	Matrix mWorldClownfish;
	Matrix mWorldVolcano;
	Matrix mWorldStarfish;
	Matrix mWorldBubble1;
	Matrix mWorldBubble2;
	Matrix planeMat;
	Matrix planeMat2;
	Matrix mWorld1;
	Matrix mWorld2;
	Matrix mWorldR;

	//Positions
	Vect posSpotlight;
	Vect pos2;
	Vect posR;
	Vect posLava1; 
	Vect posLava2; 

	// Mirror
	Mirror* pMirrorFront;
	Matrix mirrorMat;
	Matrix ReflectionMat;

	ID3D11Buffer* mpcbViewProj;

	struct ViewProjData
	{
		Matrix mView;
		Matrix mProjection;
	};

	ID3D11Buffer* mpcbWorld;
	
	struct WorldData
	{
		Matrix World;
		// The texture might change too, but that's done through mpTextureRV
	};

	
public:
	DXApp(HWND hwnd);
	virtual ~DXApp();
	
	void FrameTick();

	// overrides for handling mouse input.
	void OnMouseDown(WPARAM btnState, int xval, int yval);
	void OnMouseUp(WPARAM btnState, int xval, int yval);
	void OnMouseMove(WPARAM btnState, int xval, int yval);
	void OnMouseWheel(short delta);


};

#endif _DXApp