#include "gkpch.h"
#include "Tile.h"

using namespace Gonk;

Tile* PresetTile::GrassTile;

void PresetTile::Init()
{
    GrassTile = new TexturedTile(Sprite::Sub::Grass);
}

Tile* TexturedTile::Clone() const
{
    return new TexturedTile(m_SubTexId);
}

