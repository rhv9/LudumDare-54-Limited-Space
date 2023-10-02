#include "Sprite.h"
#include "Game.h"

using namespace Gonk;

std::array<Ref<Texture2D>, 1> Sprite::s_Textures;
std::array<Ref<SubTexture2D>, 10> Sprite::s_SubTextures;
std::array<std::vector<Ref<SubTexture2D>>, 10> Sprite::s_GifTextures;

void Sprite::Init()
{
	s_Textures[Tex::Spritesheet] = Texture2D::Create("assets/textures/spritesheet.png");

	s_SubTextures[Sub::Grass] = SubTexture2D::CreateFromCoords(s_Textures[Tex::Spritesheet], { 0.0f, 4.0f }, SIZE);

	s_GifTextures[Gif::PlayerUp] = SubTexture2D::CreateMulti(s_Textures[Tex::Spritesheet], { 0.0f, 0.0f }, SIZE, { 4, 1 });
}

const Ref<Texture2D>& Sprite::GetTex(Tex id)
{
	return s_Textures[id];
}

const Ref<SubTexture2D>& Sprite::GetSub(Sub id)
{
	return s_SubTextures[id];
}

const std::vector<Ref<SubTexture2D>>& Sprite::GetGif(Gif id)
{
	return s_GifTextures[id];
}
