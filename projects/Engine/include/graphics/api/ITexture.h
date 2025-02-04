#ifndef itexture_h__
#define itexture_h__

#include "graphics/api/IGraphicsContext.h"
#include "graphics/api/IImage.h"
#include "graphics/api/IImageView.h"
#include "graphics/api/ISampler.h"
#include "graphics/api/IDescriptorPool.h"

class TextureAsset;
struct TextureCreateInfo
{
	TextureAsset* textureAsset;
	ISampler* sampler;
	ShaderStageFlags shaderStageAccess;
	uint32_t binding;
};

class ITexture
{
	public:
		explicit ITexture(IGraphicsContext* aContext);
		ITexture(const ITexture&) = delete;
		ITexture(ITexture&&) noexcept = delete;
		virtual ~ITexture() = default;

		ITexture& operator=(const ITexture&) = delete;
		ITexture& operator=(ITexture&&) noexcept = delete;

		virtual void construct(const TextureCreateInfo&) = 0;
		virtual ShaderStageFlags getStageFlags() const = 0;
		virtual uint32_t getBindingPoint() const = 0;
	protected:
		IGraphicsContext* mContext;
};

#endif // itexture_h__
