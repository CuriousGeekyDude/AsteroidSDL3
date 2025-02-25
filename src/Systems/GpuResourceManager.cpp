

#include "Systems/GpuResouceManager.hpp"
#include <SDL3_image/SDL_image.h>
#include <limits>

namespace Asteroid
{
	
	
	SDL_Texture* GpuResourceManager::CreateGpuTextureReturnResource
		(SDL_Renderer* l_renderer
		,const std::string& l_texturePath
		, const std::string& l_nameToAssociateTextureWith)
	{
		SDL_Log("Attempting to load %s\n", l_texturePath.c_str());

		auto* lv_gpuTexture = IMG_LoadTexture(l_renderer, l_texturePath.c_str());

		if (nullptr == lv_gpuTexture) {
			SDL_Log("Failed to load texture %s\n", l_texturePath.c_str());
			return nullptr;
		}

		SDL_Log("%s was loaded successfully.\n", l_texturePath.c_str());

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
		SDL_Log("Attempting to load %s\n", l_texturePath.c_str());

		auto* lv_gpuTexture = IMG_LoadTexture(l_renderer, l_texturePath.c_str());

		if (nullptr == lv_gpuTexture) {
			SDL_Log("Failed to load texture %s\n", l_texturePath.c_str());
			return std::numeric_limits<uint32_t>::max();
		}

		SDL_Log("%s was loaded successfully.\n", l_texturePath.c_str());

		m_gpuTextures.push_back(lv_gpuTexture);

		m_textureNamesMappedToIndices.insert
		(std::pair<std::string, uint32_t>(l_nameToAssociateTextureWith, (uint32_t)(m_gpuTextures.size() - 1)));

		return (uint32_t)(m_gpuTextures.size()-1);
	}

	SDL_Texture* GpuResourceManager::RetrieveGpuTexture(const std::string& l_textureName)
	{
		SDL_Log("Attempting to retrieve gpu texture %s\n", l_textureName.c_str());


		if (m_textureNamesMappedToIndices.end() != m_textureNamesMappedToIndices.find(l_textureName)) {
			SDL_Log("Retrieve of gpu texture %s was successfull.\n", l_textureName.c_str());
			return m_gpuTextures[m_textureNamesMappedToIndices[l_textureName]];
		}

		SDL_Log("Retrieve of gpu texture %s failed.\n", l_textureName.c_str());

		return nullptr;
	}
	SDL_Texture* GpuResourceManager::RetrieveGpuTexture(const uint32_t l_textureHandle)
	{

		if (false == m_gpuTextures.empty()) {
			if (l_textureHandle >= (uint32_t)m_gpuTextures.size()) {
				SDL_Log("Texture handle is bigger than the size of the gpu textures vector.\n");
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

		return std::numeric_limits<uint32_t >::max();
	}


	GpuResourceManager::~GpuResourceManager()
	{
		for (auto l_gpuTexture : m_gpuTextures) {
			SDL_DestroyTexture(l_gpuTexture);
		}
	}
}