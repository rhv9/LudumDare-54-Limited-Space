#include "Sprite.h"
#include "Game.h"

using namespace Gonk;

static std::array<Ref<Texture2D>, 2> s_Textures;
static std::array<Ref<SubTexture2D>, 10> s_SubTextures;
static std::array<std::vector<Ref<SubTexture2D>>, 10> s_GifTextures;

void Sprite::Init()
{
	s_Textures[(int)Tex::Spritesheet] = Texture2D::Create("assets/textures/spritesheet.png");

	s_SubTextures[(int)Sub::Grass] = SubTexture2D::CreateFromCoords(GetTex(Tex::Spritesheet), { 0.0f, 4.0f }, SIZE);
	s_SubTextures[(int)Sub::CollisionBox] = SubTexture2D::CreateFromCoords(GetTex(Tex::Spritesheet), { 6.0f, 4.0f }, SIZE);

	s_GifTextures[(int)Gif::PlayerUp] = SubTexture2D::CreateMulti(GetTex(Tex::Spritesheet), { 0.0f, 0.0f }, SIZE, { 4, 1 });
	s_GifTextures[(int)Gif::Water] = SubTexture2D::CreateMulti(GetTex(Tex::Spritesheet), { 2.0f, 4.0f }, SIZE, { 3, 1 });
}

const Ref<Texture2D>& Sprite::GetTex(Tex id)
{
	return s_Textures[(int)id];
}

const Ref<SubTexture2D>& Sprite::GetSub(Sub id)
{
	return s_SubTextures[(int)id];
}

const std::vector<Ref<SubTexture2D>>& Sprite::GetGif(Gif id)
{
	return s_GifTextures[(int)id];
}
