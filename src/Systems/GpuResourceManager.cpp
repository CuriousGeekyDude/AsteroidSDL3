

#include "Systems/GpuResouceManager.hpp"
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

		LogSystem::LogCommandLine("Attempting to load {4}.", "INFO", "GPU-RESOURCE-CREATION", __LINE__, __FILE__, l_texturePath.c_str());

		auto* lv_gpuTexture = IMG_LoadTexture(l_renderer, l_texturePath.c_str());

		if (nullptr == lv_gpuTexture) {
			LogSystem::LogCommandLine("Failed to load texture {4}.", "WARNING", "GPU-RESOURCE-CREATION", __LINE__, __FILE__, l_texturePath.c_str());
			return nullptr;
		}

		LogSystem::LogCommandLine("{4} was loaded successfully.", "INFO", "GPU-RESOURCE-CREATION", __LINE__, __FILE__, l_texturePath.c_str());

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
		LogSystem::LogCommandLine("Attempting to load {4}.", "INFO", "GPU-RESOURCE-CREATION", __LINE__, __FILE__, l_texturePath.c_str());

		auto* lv_gpuTexture = IMG_LoadTexture(l_renderer, l_texturePath.c_str());

		if (nullptr == lv_gpuTexture) {

			LogSystem::LogCommandLine("Failed to load texture {4}.", "WARNING", "GPU-RESOURCE-CREATION", __LINE__, __FILE__, l_texturePath.c_str());
			return UINT32_MAX;
		}

		LogSystem::LogCommandLine("{4} was loaded successfully.", "INFO", "GPU-RESOURCE-CREATION", __LINE__, __FILE__, l_texturePath.c_str());

		m_gpuTextures.push_back(lv_gpuTexture);

		m_textureNamesMappedToIndices.insert
		(std::pair<std::string, uint32_t>(l_nameToAssociateTextureWith, (uint32_t)(m_gpuTextures.size() - 1)));

		return (uint32_t)(m_gpuTextures.size()-1);
	}

	SDL_Texture* GpuResourceManager::RetrieveGpuTexture(const std::string& l_textureName)
	{

		LogSystem::LogCommandLine("Attempting to retrieve gpu texture {4}.", "INFO", "GPU-RESOURCE-FETCH", __LINE__, __FILE__, l_textureName.c_str());


		if (m_textureNamesMappedToIndices.end() != m_textureNamesMappedToIndices.find(l_textureName)) {
			LogSystem::LogCommandLine("Retrieve of gpu texture {4} was successfull.", "INFO", "GPU-RESOURCE-FETCH", __LINE__, __FILE__, l_textureName.c_str());
			return m_gpuTextures[m_textureNamesMappedToIndices[l_textureName]];
		}

		LogSystem::LogCommandLine("Retrieve of gpu texture {4} failed.", "WARNING", "GPU-RESOURCE-FETCH", __LINE__, __FILE__, l_textureName.c_str());

		return nullptr;
	}
	SDL_Texture* GpuResourceManager::RetrieveGpuTexture(const uint32_t l_textureHandle)
	{

		if (false == m_gpuTextures.empty()) {
			if (l_textureHandle >= (uint32_t)m_gpuTextures.size()) {
				LogSystem::LogCommandLine("Texture handle is bigger than the size of the gpu textures vector.", "WARNING", "GPU-RESOURCE-FETCH", __LINE__, __FILE__);
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