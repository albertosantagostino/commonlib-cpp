/// @file data_structures_grid_tests.cpp
/// @test commonlib::Grid

#include <iostream>
#include <string>
#include <vector>

#include <data_structures/grid.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace commonlib;

class GridTests : public ::testing::Test
{
  protected:
    Grid* grid;
    virtual void SetUp() { grid = new Grid({{'.', '.', '.'}, {'x', 'x', '.'}, {'.', 'x', '.'}}); }
    virtual void TearDown() { delete grid; }
};

TEST_F(GridTests, TilesTest)
{
    grid->AddTileType(TileType::kEmpty, '.');
    grid->AddTileType(TileType::kWall, 'x');
    auto tile_00 = grid->GetTileType(0, 0);
    auto tile_10 = grid->GetTileType(1, 0);

    EXPECT_EQ(tile_00, TileType::kEmpty);
    EXPECT_EQ(tile_10, TileType::kWall);

    bool res = grid->AddTileType(TileType::kUndefined, '!');
    EXPECT_FALSE(res);
    res = grid->AddTileType(TileType::kEmpty, 'x');
    EXPECT_FALSE(res);
}

TEST_F(GridTests, ActorsTest)
{
    Actor actor_1(0U, 'x');
    Actor actor_2(1U, 'y');
    grid->AddActor(actor_1);
    grid->AddActor(actor_2);

    Actor res;
    grid->GetActor(0U, res);
    EXPECT_EQ(res.GetCharacter(), 'x');
    grid->GetActor(1U, res);
    EXPECT_EQ(res.GetCharacter(), 'y');
}
