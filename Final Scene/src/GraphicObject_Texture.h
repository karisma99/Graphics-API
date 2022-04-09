// GraphicObject_Texture

#ifndef _GraphicObject_Texture
#define _GraphicObject_Texture

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderTexture.h"
#include "Texture.h"

class GraphicObject_Texture : public GraphicObject_Base
{
	friend class ShaderTexture;

public:
	GraphicObject_Texture(const GraphicObject_Texture&) = delete;				 // Copy constructor
	GraphicObject_Texture(GraphicObject_Texture&&) = default;                    // Move constructor
	GraphicObject_Texture& operator=(const GraphicObject_Texture&) & = default;  // Copy assignment operator
	GraphicObject_Texture& operator=(GraphicObject_Texture&&) & = default;       // Move assignment operator
	~GraphicObject_Texture();		  											 // Destructor

	GraphicObject_Texture() = delete;

	void SetToContext(ID3D11DeviceContext* devcon);
	void SetTexture(Texture* tex);
	void SetTexture(Texture* tex, int meshNum);
	void SetWorld(const Matrix& m);
	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	virtual void Render() override;

	GraphicObject_Texture(ShaderTexture* shader, Model* mod);

private:
	ShaderTexture* pShader;
	Texture** pMeshTexture;
	Matrix World;

};

#endif _GraphicObject_Texture
