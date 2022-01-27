#include "TileMap.h"
#include "Tile.h"
#include "../Events/EventDispatcher.h"
#include "../Graphics/AssetManager.h"
#include "../Graphics/GraphicsHandler.h"
#include "../Graphics/GraphicsEvents.h"

namespace Firelight::TileMap
{
    TileMap::TileMap()
        : m_tileHeight(1.0f)
        , m_tileWidth(1.0f)
        , m_tileMapHeight(5.0f)
        , m_tileMapWidth(5.0f)
        , m_tileDistance(1.0f)
        , em_VerticalScale(Scale::Center)
        , em_HorizontalScale(Scale::Center)
        , m_tileMap()
        , m_newTileMap()
        , m_tileAtlas(std::make_unique<std::map<unsigned int, Maths::Rectf>>())
    {}

    void TileMap::Render()
    {
        Events::EventDispatcher::SubscribeFunction<Events::Graphics::OnEarlyRender>(std::bind(&TileMap::DrawTiles, this));
    }

    void TileMap::UpdateTileMapSize()
    {
        for (int x = 0; x < m_tileMapWidth; ++x)
        {
            std::vector<Tile> vec;
            for (int y = 0; y < m_tileMapHeight; ++y)
            {
                  Tile newTile;
                  newTile.SetTileTexture(Graphics::AssetManager::Instance().GetDefaultTexture());
                  vec.emplace_back(newTile);
            }
            m_tileMap.emplace_back(vec);
        }
    }

    void TileMap::DrawTiles()
    {
        int x = 0, y = 0;
        for (auto row = m_tileMap.begin(); row != m_tileMap.end(); ++row)
        {
            for (auto column = row->begin(); column != row->end(); ++column)
            {
                column->SetDestinationRect(x * m_tileDistance, y * m_tileDistance, m_tileWidth, m_tileHeight);
                column->DrawTile();
                ++x;
            }
            ++y;
            x = 0;
        }
    }

   void TileMap::SetTileHeight(float tileHeight)
    {
        m_tileHeight = tileHeight;
    }

    void TileMap::SetTileWidth(float tileWidth)
    {
        m_tileWidth = tileWidth;
    }

    void TileMap::SetTileMapHeight(float tileMapHeight)
    {
        m_tileMapHeight = tileMapHeight;
    }

    void TileMap::SetTileMapWidth(float tileMapWidth)
    {
        m_tileMapWidth = tileMapWidth;
    }

    std::vector<std::vector<Tile>>& TileMap::GetTileMap()
    {
        return m_tileMap;
    }
}
