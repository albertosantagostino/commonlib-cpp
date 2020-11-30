/// @file grid.h
/// @author Alberto Santagostino

#ifndef DATA_STRUCTURES_GRID_H
#define DATA_STRUCTURES_GRID_H

#include <unordered_map>

#include <data_structures/matrix.h>
#include <primitives/actor.h>

namespace commonlib
{
enum class TileType
{
    kEmpty,
    kWall,
    kUndefined
};

typedef std::unordered_map<std::size_t, Actor> ActorsMap;
typedef std::unordered_map<TileType, char> TilesMap;

/// @class Grid
/// @brief 2D characters grid, inherited as Matrix<char>. It holds a number of actors
class Grid : public Matrix<char>
{
  public:
    using Matrix::Matrix;

    bool AddActor(Actor actor);
    bool AddTileType(TileType tiletype, char character);
    bool ActorExists(const std::size_t actor_id);
    const ActorsMap GetActors() { return m_actors; }
    bool GetActor(const std::size_t actor_id, Actor& actor);
    const TileType GetTileType(std::size_t row, std::size_t col);

    void Print(char row_sep = '\n', char col_sep = ' ');

  private:
    ActorsMap m_actors;
    TilesMap m_tiles;
};

bool Grid::ActorExists(const std::size_t actor_id)
{
    ActorsMap::const_iterator got = m_actors.find(actor_id);
    return (got == m_actors.end()) ? (false) : (true);
}

bool Grid::GetActor(const std::size_t actor_id, Actor& actor)
{
    // TODO: Refactor to reuse ActorExists() and avoid duplication
    ActorsMap::iterator got = m_actors.find(actor_id);
    if (got == m_actors.end())
    {
        return false;
    }
    else
    {
        actor = got->second;
        return true;
    }
}

const TileType Grid::GetTileType(std::size_t row, std::size_t col)
{
    auto tile_char = this->operator()(row, col);
    auto it = std::find_if(m_tiles.begin(), m_tiles.end(), [tile_char](auto& p) { return p.second == tile_char; });
    if (it != m_tiles.end())
    {
        return it->first;
    }
    return TileType::kUndefined;
}

bool Grid::AddActor(Actor actor)
{
    const std::size_t id = actor.Id();
    if (!ActorExists(id))
    {
        m_actors.insert(std::make_pair(id, actor));
        return true;
    }
    return false;
}

bool Grid::AddTileType(TileType tiletype, char character)
{
    if (tiletype != TileType::kUndefined)
    {
        std::vector<char> vals;
        for (auto kv : m_tiles)
        {
            vals.push_back(kv.second);
        }
        if (!std::count(vals.begin(), vals.end(), character))
        {
            m_tiles.insert(std::make_pair(tiletype, character));
            return true;
        }
    }
    return false;
}

void Grid::Print(char row_sep, char col_sep)
{
    for (std::size_t i{0}; i < m_rows; ++i)
    {
        for (std::size_t j = 0; j < m_cols; ++j)
        {
            std::cout << m_data[i][j] << col_sep;
        }
        std::cout << row_sep;
    }
    std::cout << std::endl;
}

}  // namespace commonlib

#endif  // DATA_STRUCTURES_GRID_H
