#ifndef rendersystem_h__
#define rendersystem_h__

#include <vma/vma.h>

#include "core/Window.h"
#include "ecs/System.h"

#include "events/ApplicationEvent.h"

#include "graphics/vk/VulkanCommandBuffer.h"
#include "graphics/vk/VulkanFramebuffer.h"
#include "graphics/vk/VulkanGraphicsContext.h"
#include "graphics/vk/VulkanRenderPass.h"
#include "graphics/vk/VulkanSwapChain.h"
#include "graphics/vk/VulkanGraphicsPipeline.h"
#include "graphics/vk/VulkanPipelineLayout.h"
#include "graphics/vk/VulkanVertexBuffer.h"
#include "graphics/vk/VulkanIndexBuffer.h"
#include "graphics/vk/VulkanTexture.h"
#include "graphics/UniformBufferPool.h"

#include "assets/ShaderAsset.h"
#include "assets/RenderPassAsset.h"

class RenderSystem final : public System
{
	public:
		explicit RenderSystem(Window* aWindow);
		RenderSystem(const RenderSystem&) = delete;
		RenderSystem(RenderSystem&&) noexcept = delete;
		~RenderSystem();

		RenderSystem& operator=(const RenderSystem&) = delete;
		RenderSystem& operator=(RenderSystem&&) noexcept = delete;

		void initialize() override;

		void preRender() override;
		void render() override;
		void postRender() override;

		void onEvent(Event& aEvent) override;
	private:
		const uint32_t mFlightSize = 2;
		uint32_t mCurrentFrame = 0;

		VulkanGraphicsContext* mContext;
		VulkanSwapChain* mSwapChain;
		IRenderPass* mRenderPass;

		IGraphicsPipeline* mGraphicsPipeline;
		VulkanPipelineLayout* mLayout{};

		VulkanCommandBuffer** mPrimaryBuffer = nullptr;
		VulkanFramebuffer** mFramebuffers = nullptr;

		VulkanCommandBuffer* mCpyBuffer = nullptr;

		VulkanVertexBuffer* mVertexBuffer;
		VulkanIndexBuffer* mIndexBuffer;

		UniformBufferObject* mUboObject0;
		UniformBufferPool* mUboPool;

		DescriptorSetPool* mDescPool;

		VulkanTexture* mTexture;
		VulkanTexture* mTexture2;
		VulkanSampler* mSampler;

		SceneData* mSceneData = nullptr;
		MaterialInstance* mMaterialInstance{};
		MaterialInstance* mMaterialInstance2{};
		std::vector<MaterialInstance*> mInstances;

		CommandBufferInheritanceInfo mPrimaryInheritance = {};
		CommandBufferRecordInfo mPrimaryRecordInfo = {};

		Window* mWindow;

		bool _onResize(WindowResizeEvent& aEvent) const;

		std::shared_ptr<ShaderAsset> mShaderAsset;
		std::shared_ptr<RenderPassAsset> mRenderPassAsset;

		uint8_t mCpyReady = 2;
};

#endif // rendersystem_h__