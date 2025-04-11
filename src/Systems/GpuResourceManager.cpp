

#include "Systems/GpuResouceManager.hpp"

#define LOGGING
#include "Systems/LogSystem.hpp"

#include <SDL3_image/SDL_image.h>
#include <limits>

namespace Asteroid
{
	
	
	SDL_Texture* GpuResourceManager::CreateGpuTextureReturnResource
		(SDL_Renderer* l_renderer
		,const std::string& l_texturePath
		, const std::string& l_nameToAssociateTextureWith)
	{
		using namespace LogSystem;

		LOG(Severity::INFO, Channel::GRAPHICS, "Attempting to load %s", l_texturePath.c_str());

		//LogSystem::LogCommandLine("Attempting to load {4}.", "INFO", "GPU-RESOURCE-CREATION", __LINE__, __FILE__, );

		auto* lv_gpuTexture = IMG_LoadTexture(l_renderer, l_texturePath.c_str());

		if (nullptr == lv_gpuTexture) {
			LOG(Severity::WARNING, Channel::GRAPHICS, "Failed to load texture %s", l_texturePath.c_str());
			return nullptr;
		}

		LOG(Severity::INFO, Channel::GRAPHICS, "%s was loaded successfully.", l_texturePath.c_str());

		m_gpuTextures.push_back(lv_gpuTexture);

		m_textureNamesMappedToIndices.insert
		(std::pair<std::string, uint32_t>(l_nameToAssociateTextureWith, (uint32_t)(m_gpuTextures.size() - 1)));

		return lv_gpuTexture;

	}

	uint32_t GpuResourceManager::CreateGpuTextureReturnHandle
		(SDL_Renderer* l_renderer
		, const std::string& l_texturePath
		, const std::string& l_nameToAssociateTextureWith)
	{
		using namespace LogSystem;

		LOG(Severity::INFO, Channel::GRAPHICS, "Attempting to load %s", l_texturePath.c_str());

		auto* lv_gpuTexture = IMG_LoadTexture(l_renderer, l_texturePath.c_str());

		if (nullptr == lv_gpuTexture) {

			LOG(Severity::WARNING, Channel::GRAPHICS, "Failed to load texture %s", l_texturePath.c_str());
			return UINT32_MAX;
		}


		LOG(Severity::INFO, Channel::GRAPHICS, "%s was loaded successfully.",l_texturePath.c_str());

		m_gpuTextures.push_back(lv_gpuTexture);

		m_textureNamesMappedToIndices.insert
		(std::pair<std::string, uint32_t>(l_nameToAssociateTextureWith, (uint32_t)(m_gpuTextures.size() - 1)));

		return (uint32_t)(m_gpuTextures.size()-1);
	}

	SDL_Texture* GpuResourceManager::RetrieveGpuTexture(const std::string& l_textureName)
	{
		using namespace LogSystem;

		LOG(Severity::INFO, Channel::GRAPHICS, "Attempting to retrieve gpu texture %s", l_textureName.c_str());


		if (m_textureNamesMappedToIndices.end() != m_textureNamesMappedToIndices.find(l_textureName)) {

			LOG(Severity::INFO, Channel::GRAPHICS
				, "Retrieve of the following gpu texture was successful  %s", l_textureName.c_str());
			return m_gpuTextures[m_textureNamesMappedToIndices[l_textureName]];
		}

		LOG(Severity::WARNING, Channel::GRAPHICS
			, "Retrieve of the following gpu texture failed  %s", l_textureName.c_str());
		return nullptr;
	}
	SDL_Texture* GpuResourceManager::RetrieveGpuTexture(const uint32_t l_textureHandle)
	{
		using namespace LogSystem;

		if (false == m_gpuTextures.empty()) {
			if (l_textureHandle >= (uint32_t)m_gpuTextures.size()) {

				LOG(Severity::WARNING, Channel::GRAPHICS,"Texture handle is bigger than the size of the gpu textures vector.");
				return nullptr;
			}
			return m_gpuTextures[l_textureHandle];
		}

		return nullptr;
	}
	

	uint32_t GpuResourceManager::RetrieveGpuTextureHandle(const std::string& l_textureName)
	{
		if (m_textureNamesMappedToIndices.end() != m_textureNamesMappedToIndices.find(l_textureName)) {
			return m_textureNamesMappedToIndices[l_textureName];
		}

		return UINT32_MAX;
	}


	GpuResourceManager::~GpuResourceManager()
	{
		for (auto l_gpuTexture : m_gpuTextures) {
			SDL_DestroyTexture(l_gpuTexture);
		}
	}
}