#include "Sprite.h"
#include "Game.h"

using namespace Gonk;

std::array<Ref<Texture2D>, 1> Sprite::s_Textures;
std::array<Ref<SubTexture2D>, 10> Sprite::s_SubTextures;
std::array<std::vector<Ref<SubTexture2D>>, 10> Sprite::s_GifTextures;

void Sprite::Init()
{
	const glm::vec2 cellSize = { SPRITE_SIZE, SPRITE_SIZE };

	s_Textures[Tex::Spritesheet] = Texture2D::Create("assets/textures/spritesheet.png");

	s_SubTextures[Sub::Grass] = SubTexture2D::CreateFromCoords(s_Textures[Tex::Spritesheet], { 0.0f, 4.0f }, cellSize);

	s_GifTextures[Gif::PlayerUp] = SubTexture2D::CreateMulti(s_Textures[Tex::Spritesheet], { 0.0f, 0.0f }, cellSize, { 4, 1 });
}

const Ref<Texture2D>& Sprite::GetTex(Tex id)
{
	static auto srite = Texture2D::Create("assets/textures/spritesheet.png");
	return srite;
}

const Ref<SubTexture2D>& Sprite::GetSub(Sub id)
{
	return s_SubTextures[id];
}

const std::vector<Ref<SubTexture2D>>& Sprite::GetGif(Gif id)
{
	return s_GifTextures[id];
}
