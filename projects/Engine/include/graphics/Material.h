#ifndef material_h__
#define material_h__

#include "graphics/DescriptorSetPool.h"
#include "graphics/UniformBufferPool.h"
#include "graphics/api/IDescriptorSet.h"
#include "graphics/api/IGraphicsPipeline.h"
#include "graphics/api/ITexture.h"

struct MaterialCreateInfo
{
	DescriptorSetPool* pool;
	IGraphicsPipeline* pipeline;
	std::vector<UniformBufferPool*> layouts;
	std::unordered_map<std::string, ITexture*> textures;
};

class MaterialInstance;

class Material
{
	friend class MaterialInstance;
	friend class VulkanCommandBuffer;

	uint32_t mChildInstances = 0;

	struct BackingBufferInfo
	{
		std::vector<void*> blocks;
		size_t elementCount;
		size_t elementSize;
	};

	public:
		explicit Material(const MaterialCreateInfo& aCreateInfo);
		Material(const Material&) = delete;
		Material(Material&&) noexcept = delete;
		~Material();

		Material& operator=(const Material&) = delete;
		Material& operator=(Material&&) noexcept = delete;

		MaterialInstance* createInstance();
		void destroyInstance(MaterialInstance* aInstance);

		[[nodiscard]] Material* clone();

	private:
		MaterialCreateInfo mCreateInfo;
		IGraphicsPipeline* mPipeline;
		DescriptorSet mSet{};
		DescriptorSetPool* mDescSetPool;
		IDescriptorSetLayout* mLayout = nullptr;
		std::unordered_map<std::string, ITexture*> mTextures;
		std::vector<UniformBufferPool*> mUboLayouts;

		std::unordered_map<UniformBufferPool*, BackingBufferInfo> mBackingBuffers;
		std::vector<size_t> mFreeSlots;
		uint64_t mCursor = 0;

		std::unordered_map<std::string, std::pair<UniformBufferPool*, UniformBufferObjectElement*>> mElements;
		Material* mParent = nullptr;
};

class MaterialInstance
{
	friend class Material;
	friend class VulkanCommandBuffer;

	Material* mParent;
	std::vector<UniformBufferObject*> mUbos;
	size_t mInstanceId;

	explicit MaterialInstance(Material* aMaterial, std::vector<UniformBufferObject*> aUbos, size_t aInstanceId);
public:
	MaterialInstance(const MaterialInstance&) = delete;
	MaterialInstance(MaterialInstance&&) noexcept = delete;
	~MaterialInstance();

	MaterialInstance& operator=(const MaterialInstance&) = delete;
	MaterialInstance& operator=(MaterialInstance&&) noexcept = delete;

	template<typename T>
	void setVariable(const std::string& aName, T aValue);

	template<typename T>
	T* getVariable(const std::string& aName);

	[[nodiscard]] Material* setTexture(std::string aName, ITexture* aTexture);

private:
	[[nodiscard]] std::pair<UniformBufferPool*, UniformBufferObjectElement*> _getElementFromName(const std::string& aName) const;
};

template <typename T>
void MaterialInstance::setVariable(const std::string& aName, T aValue)
{
	memcpy(getVariable<T>(aName), &aValue, sizeof(T));
}

template <typename T>
T* MaterialInstance::getVariable(const std::string& aName)
{
	auto parent = mParent;
	while (parent->mParent != nullptr)
	{
		parent = parent->mParent;
	}

	const auto pair = _getElementFromName(aName);
	PRIMAL_ASSERT(pair.first != nullptr && pair.second != nullptr, "Invalid variable");
	const Material::BackingBufferInfo& buf = parent->mBackingBuffers[pair.first];
	const size_t blockIndex = mInstanceId / buf.elementCount;
	const size_t offset = ((mInstanceId - (blockIndex * buf.elementCount)) * buf.elementCount) + pair.second->offset;
	char* block = reinterpret_cast<char*>(buf.blocks[blockIndex]);
	return reinterpret_cast<T*>(block + offset);
}

#endif // material_h__
