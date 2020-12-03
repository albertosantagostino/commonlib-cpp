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

TEST_F(GridTests, FileLoadingTest)
{
    std::ifstream fp;
    fp.open("data/input_grid.txt", std::ifstream::in);
    Grid gridfp(fp, '\0');
    ASSERT_TRUE(gridfp == *grid);
    fp.close();
}

TEST_F(GridTests, TilesTest)
{
    grid->AddTileTypeDefinition(TileType::kTileType_Empty, '.');
    grid->AddTileTypeDefinition(TileType::kTileType_Wall, 'x');
    auto tile_00 = grid->GetTileType(0, 0);
    auto tile_10 = grid->GetTileType(1, 0);

    EXPECT_EQ(tile_00, TileType::kTileType_Empty);
    EXPECT_EQ(tile_10, TileType::kTileType_Wall);

    bool res = grid->AddTileTypeDefinition(TileType::kTileType_Undefined, '!');
    EXPECT_FALSE(res);
    res = grid->AddTileTypeDefinition(TileType::kTileType_Empty, 'x');
    EXPECT_FALSE(res);
}

TEST_F(GridTests, InfiniteTest)
{
    grid->MakeInfinite(true);
    EXPECT_EQ(grid->operator()(10, 10), 'x');
    grid->MakeInfinite(false);
    try
    {
        char tile = grid->operator()(10, 10);
    }
    catch (const std::exception& e)
    {
        EXPECT_EQ(e.what(), std::string("Matrix<T>::operator(): Index is out of range"));
    }
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
