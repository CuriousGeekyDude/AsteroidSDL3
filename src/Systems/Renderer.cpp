




#include "Systems/Renderer.hpp"
#include "Systems/Colors.hpp"
#include "Systems/RenderingData.hpp"
#include "Systems/GpuResouceManager.hpp"
#include <glm.hpp>
#include <SDL3/SDL_render.h>


#define LOGGING
#include "Systems/LogSystem.hpp"


namespace Asteroid
{

	namespace RenderSystem
	{
		Renderer::Renderer(GpuResourceManager* l_gpuResManager)
			:m_renderer(nullptr)
			,m_gpuResourceManager(l_gpuResManager)
		{

		}


		bool Renderer::Init(SDL_Window* l_window)
		{
			using namespace LogSystem;

			m_renderer = SDL_CreateRenderer(l_window, nullptr);
			if (nullptr == m_renderer) {
				LOG(Severity::FAILURE, Channel::GRAPHICS, "SDL failed to create the renderer %s", SDL_GetError());
				return false;
			}

			return true;
		}


		bool Renderer::SetClearColor(const Colors& l_clearColor)
		{
			using namespace LogSystem;

			glm::u8vec4 lv_color;

			switch (l_clearColor) {

			case Colors::BLACK:
				lv_color = glm::u8vec4{0, 0, 0, 1};
				break;
			case Colors::BLUE:
				lv_color = glm::u8vec4{0, 0, 1, 1};
				break;
			case Colors::GREEN:
				lv_color = glm::u8vec4{0, 1, 0, 1};
				break;
			case Colors::RED:
				lv_color = glm::u8vec4{1, 0, 0, 1};
				break;
			case Colors::WHITE:
				lv_color = glm::u8vec4{1, 1, 1, 1};
				break;

			}

			if (false == SDL_GetRenderDrawColor
			(m_renderer, &lv_color.r, &lv_color.g, &lv_color.b, &lv_color.a)) {

				LOG(Severity::FAILURE, Channel::GRAPHICS, "SDL failed to set the clear color to the requested one %s", SDL_GetError());
				return false;
			}

			return true;
		}


		bool Renderer::ClearWindow()
		{
			using namespace LogSystem;

			if (false == SDL_RenderClear(m_renderer)) {
				LOG(Severity::FAILURE, Channel::GRAPHICS, "SDL failed to clear the swapchain %s", SDL_GetError());
				return false;
			}

			return true;
		}

		bool Renderer::RenderEntity(const RenderingData& l_renderData)
		{
			using namespace LogSystem;
			auto* lv_sdlTexture = m_gpuResourceManager->RetrieveGpuTexture(l_renderData.m_entityTextureHandle);

			assert(lv_sdlTexture != nullptr);

			SDL_FRect lv_dstRect;
			lv_dstRect.x = l_renderData.m_entityPos.x;
			lv_dstRect.y = l_renderData.m_entityPos.y;
			lv_dstRect.w = (0 == l_renderData.m_widthToRender) ? (float)lv_sdlTexture->w : (float)l_renderData.m_widthToRender;
			lv_dstRect.h = (0 == l_renderData.m_widthToRender) ? (float)lv_sdlTexture->h : (float)l_renderData.m_heightToRender;

			if (false == SDL_RenderTexture(m_renderer
				, lv_sdlTexture, nullptr, &lv_dstRect)) {

				LOG(Severity::FAILURE, Channel::GRAPHICS, "SDL failed to render the requested entity %s", SDL_GetError());
				return false;
			}

			return true;

		}


		bool Renderer::PresentToWindow()
		{
			if (false == SDL_RenderPresent(m_renderer)) {
				return false;
			}

			return true;
		}


		SDL_Renderer* Renderer::GetSDLRenderer()
		{
			return m_renderer;
		}


		Renderer::~Renderer()
		{
			SDL_DestroyRenderer(m_renderer);
		}
	}

}