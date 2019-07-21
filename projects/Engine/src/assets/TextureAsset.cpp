#include "assets/TextureAsset.h"
#include "core/Types.h"
#include "filesystem/FileSystem.h"
#include "assets/AssetManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "core/Log.h"
#include <json/json.hpp>

TextureAsset::TextureAsset(const std::string& aPath, const uint32_t aDesiredChannels)
	: mTexture(nullptr)
{
	mPath = aPath;
	mDesiredChannels = aDesiredChannels;
	mFile = {};
}

TextureAsset::~TextureAsset()
{
	delete mTexture;
}

ImageFile TextureAsset::getData() const
{
	return mFile;
}

Texture* TextureAsset::getTexture() const
{
	return mTexture;
}

void TextureAsset::_load()
{
	Path loadPath = FileSystem::instance().getMountedDirectory();

	const std::string jsonData = FileSystem::instance().loadToString(mPath);
	const auto jsonValue = nlohmann::json::parse(jsonData);

	const std::string samplerName = jsonValue["samplername"];

	uint32_t bindingPoint = jsonValue["bindingpoint"];
	uint32_t shaderStage = jsonValue["shaderstage"];

	const std::string textureFileName = jsonValue["texturefile"]; // cacs
	loadPath += textureFileName;

	int x, y, channels;
	auto widePath = loadPath.native();

	std::vector<char> convertedPath;
	convertedPath.reserve(widePath.size());

	std::string s;

	for (const auto& c : widePath)
	{
		if (c > 255)
		{
			PRIMAL_INTERNAL_ERROR("Invalid character code in path.");
			return;
		}
		convertedPath.push_back(static_cast<char>(c));
		s += static_cast<char>(c);
	}

	unsigned char* payload = stbi_load(s.c_str(), &x, &y, &channels, mDesiredChannels);
	std::vector<unsigned char> results;
	results.resize(static_cast<size_t>(x) * static_cast<size_t>(y) * mDesiredChannels);
	memcpy(results.data(), payload, results.size());
	stbi_image_free(payload);

	mFile.payload = results;
	mFile.bitsPerPixel = 8;
	mFile.channels = mDesiredChannels;
	mFile.width = x;
	mFile.height = y;
}
