#include "gkpch.h"
#include "Tile.h"
#include "Game.h"
using namespace Gonk;

Tile* PresetTile::GrassTile;
Tile* PresetTile::WaterTile;

void PresetTile::Init()
{
    GrassTile = new TexturedTile(Sprite::Sub::Grass);
    WaterTile = new AnimatedTile(Sprite::Gif::Water, 2.0f);
}

Tile* TexturedTile::Clone() const
{
    return new TexturedTile(m_SubTexId);
}

void AnimatedTile::OnUpdate(const glm::vec3& pos, Timestep ts)
{
    auto gif = Sprite::GetGif(m_Gif);
    auto texture = gif[(int)(Game::s_TimePassed * m_AnimationSpeed) % gif.size()];
    Renderer2D::DrawQuad(pos, texture->GetSize(), texture);
}
