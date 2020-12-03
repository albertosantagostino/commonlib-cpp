/// @file grid.h
/// @author Alberto Santagostino

#ifndef DATA_STRUCTURES_GRID_H
#define DATA_STRUCTURES_GRID_H

#include <algorithm>
#include <optional>
#include <unordered_map>

#ifdef TEST_BUILD
#include <data_structures/matrix.h>
#include <primitives/actor.h>
#else
#include <commonlib/include/data_structures/matrix.h>
#include <commonlib/include/primitives/actor.h>
#endif

namespace commonlib
{
enum class TileType
{
    kTileType_Empty,
    kTileType_Wall,
    kTileType_Tree,
    kTileType_Undefined
};

typedef std::unordered_map<std::size_t, Actor> ActorsMap;
typedef std::unordered_map<TileType, char> TilesMap;

/// @class Grid
/// @brief 2D characters grid, inherited as Matrix<char>. It holds a number of actors
class Grid : public Matrix<char>
{
  public:
    // Constructors
    using Matrix::Matrix;

    // Grid-specific setters
    bool AddActor(Actor actor);
    bool AddTileTypeDefinition(TileType tiletype, char character);
    bool ActorExists(const std::size_t actor_id);
    inline void MakeInfinite(const bool infinite) { m_infinite = infinite; }

    // Grid-specific getters
    inline const ActorsMap GetActors() { return m_actors; }
    bool GetActor(const std::size_t actor_id);
    bool GetActor(const std::size_t actor_id, Actor& actor);
    const TileType GetTileType(std::size_t row, std::size_t col);

    // Operators
    char operator()(std::size_t row, std::size_t col);
    char const operator()(std::size_t row, std::size_t col) const;

  private:
    ActorsMap m_actors;
    TilesMap m_tiles;
    bool m_infinite;
};

/// @brief Check if a specific actor exists
/// @param actor_id Id of the actor
bool Grid::GetActor(const std::size_t actor_id)
{
    ActorsMap::const_iterator got = m_actors.find(actor_id);
    return (got == m_actors.end()) ? (false) : (true);
}

/// @brief Return a specific actor
/// @param actor_id Id of the actor
/// @param actor Variable to fill with the desired actor
bool Grid::GetActor(const std::size_t actor_id, Actor& actor)
{
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

/// @brief Get the tile type at the specific position
const TileType Grid::GetTileType(std::size_t row, std::size_t col)
{
    auto tile_char = this->operator()(row, col);
    auto it = std::find_if(m_tiles.begin(), m_tiles.end(), [tile_char](auto& p) { return p.second == tile_char; });
    if (it != m_tiles.end())
    {
        return it->first;
    }
    return TileType::kTileType_Undefined;
}

/// @brief Add an actor to the grid
/// @param actor Actor to add
bool Grid::AddActor(Actor actor)
{
    const std::size_t id = actor.Id();
    if (!GetActor(id))
    {
        m_actors.insert(std::make_pair(id, actor));
        return true;
    }
    return false;
}

/// @brief Add a tile definition (linking a tile type to a character)
/// @param tiletype Tile type to define (type: TileType)
/// @param character Character to link
bool Grid::AddTileTypeDefinition(TileType tiletype, char character)
{
    if (tiletype != TileType::kTileType_Undefined)
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

/// @brief Redefinition of operator() to take into account infinite grids
char Grid::operator()(std::size_t row, std::size_t col)
{
    if (row >= m_rows || col >= m_cols)
    {
        if (m_infinite)
        {
            return m_data[row % m_rows][col % m_cols];
        }
        else
        {
            throw std::out_of_range("Matrix<T>::operator(): Index is out of range");
        }
    }
    return m_data[row][col];
}

/// @brief Redefinition of operator() to take into account infinite grids
char const Grid::operator()(std::size_t row, std::size_t col) const
{
    if (row >= m_rows || col >= m_cols)
    {
        if (m_infinite)
        {
            return m_data[row % m_rows][col % m_cols];
        }
        else
        {
            throw std::out_of_range("Matrix<T>::operator(): Index is out of range");
        }
    }
    return m_data[row][col];
}

}  // namespace commonlib

#endif  // DATA_STRUCTURES_GRID_H
