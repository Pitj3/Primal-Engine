#ifndef vulkanvertexbuffer_h__
#define vulkanvertexbuffer_h__

#include "graphics/api/IVertexBuffer.h"

#include <vulkan/vulkan.h>
#include <vma/vk_mem_alloc.h>
#include "graphics/api/IGraphicsPipeline.h"

class VulkanVertexBuffer final : public IVertexBuffer
{
		friend class VulkanCommandBuffer;
	public:
		explicit VulkanVertexBuffer(IGraphicsContext* aContext);
		VulkanVertexBuffer(const VulkanVertexBuffer& aOther) = delete;
		VulkanVertexBuffer(VulkanVertexBuffer&& aOther) noexcept = delete;
		virtual ~VulkanVertexBuffer() override;

		VulkanVertexBuffer& operator = (const VulkanVertexBuffer& aOther) = delete;
		VulkanVertexBuffer& operator = (VulkanVertexBuffer&& aOther) noexcept = delete;

		void construct(const VertexBufferCreateInfo& aInfo) override;

		void setLayout(const BufferLayout& aLayout) override;

		[[nodiscard]] VertexInputBindingDescription getBinding() const;
		[[nodiscard]] std::vector<VertexInputAttributeDescription> getAttributes() const;

	private:
		VkBuffer mBuffer = VK_NULL_HANDLE;
		VkBuffer mStagingBuffer = VK_NULL_HANDLE;
		VmaAllocation mStagingAllocation{};
		VmaAllocation mAllocation{};

		VertexBufferCreateInfo mInfo;
		VkVertexInputBindingDescription mBindingDescription{};
		std::vector<VkVertexInputAttributeDescription> mAttributeDescriptions;
};

#endif // vulkanvertexbuffer_h__