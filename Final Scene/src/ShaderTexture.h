//ShaderTexture.h
#ifndef _ShaderTexture
#define _ShaderTexture

#include "ShaderBase.h"
#include "Texture.h"

class ShaderTexture : public ShaderBase
{
public:
	ShaderTexture() = default;
	ShaderTexture(ID3D11Device* device);
	ShaderTexture(ShaderTexture&&) = default;                    // Move constructor
	ShaderTexture& operator=(const ShaderTexture&) & = default;  // Copy assignment operator
	ShaderTexture& operator=(ShaderTexture&&) & = default;       // Move assignment operator
	~ShaderTexture();

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SetTextureResourceAndSampler(Texture* tex);
	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void ShaderTexture::SendWorld(const Matrix& world);

private:
	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer* mpBufferCamMatrices;

	struct Data_WorldColor
	{
		Matrix World;
		Vect Color;
	};

	ID3D11Buffer* mpBuffWordColor;
};

#endif _ShaderTexture