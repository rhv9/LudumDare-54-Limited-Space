#include "gkpch.h"
#include "SubTexture2D.h"

namespace Gonk {

	SubTexture2D::SubTexture2D(const Ref<Texture2D>&texture, const glm::vec2 & bottomLeftCoords, const glm::vec2 & topRightCoords)
		: m_Texture(texture)
	{
		m_Width = (int)(m_Texture->GetWidth() * topRightCoords.x - m_Texture->GetWidth() * bottomLeftCoords.x + 0.5f);
		m_Height = (int)(m_Texture->GetHeight() * topRightCoords.y - m_Texture->GetHeight() * bottomLeftCoords.y + 0.5f);

		m_TexCoords[0] = { bottomLeftCoords.x, bottomLeftCoords.y };
		m_TexCoords[1] = { topRightCoords.x  , bottomLeftCoords.y };
		m_TexCoords[2] = { topRightCoords.x  , topRightCoords.y   };
		m_TexCoords[3] = { bottomLeftCoords.x, topRightCoords.y   };
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize)
	{
		const glm::vec2 bottomLeftCoords = {
			(coords.x * cellSize.x) / texture->GetWidth(),
			(coords.y * cellSize.y) / texture->GetHeight()
		};

		const glm::vec2 topRightCoords = {
			((coords.x + spriteSize.x) * cellSize.x) / texture->GetWidth(),
			((coords.y + spriteSize.y) * cellSize.y) / texture->GetHeight()
		};

		return CreateRef<SubTexture2D>(texture, bottomLeftCoords, topRightCoords);
	}
	std::vector<Ref<SubTexture2D>> SubTexture2D::CreateMulti(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& quantity, const glm::vec2& spriteSize)
	{
		std::vector<Ref<SubTexture2D>> subTextures;
		subTextures.reserve(quantity.x * quantity.y);

		for (int y = 0; y < quantity.y; y++)
		{
			for (int x = 0; x < quantity.x; x++)
			{
				subTextures.push_back(CreateFromCoords(texture, coords + glm::vec2{(float)x, (float)y}, cellSize, spriteSize));
			}
		}
		return subTextures;
	}
}