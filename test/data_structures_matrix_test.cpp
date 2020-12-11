/// @file data_structures_matrix_test.cpp
/// @test commonlib::Matrix

#include <iostream>
#include <string>
#include <vector>

#include <data_structures/matrix.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace commonlib;

typedef std::vector<std::vector<int>> IntMatrixData;

class IntMatrixTests : public ::testing::Test
{
  protected:
    Matrix<int>* matrix;
    virtual void SetUp() { matrix = new Matrix<int>({{1, 2, 3}, {4, 5, 6}}); }
    virtual void TearDown() { delete matrix; }
};

TEST_F(IntMatrixTests, AccessTests)
{
    IntMatrixData expected_data({{1, 2, 3}, {4, 5, 6}});
    std::vector<int> expected_row({1, 2, 3});
    std::vector<int> expected_column({1, 4});
    ASSERT_EQ(matrix->Data(), expected_data);
    ASSERT_EQ(matrix->Row(0), expected_row);
    ASSERT_EQ(matrix->Column(0), expected_column);
    ASSERT_EQ(matrix->NRows(), 2U);
    ASSERT_EQ(matrix->Data().size(), 2U);
    ASSERT_EQ(matrix->NCols(), 3U);
    ASSERT_EQ(matrix->Data()[0].size(), 3U);
    ASSERT_EQ(matrix->operator()(0, 0), 1);
}

TEST_F(IntMatrixTests, EditTests)
{
    matrix->operator()(0, 0) = 9;
    ASSERT_EQ(matrix->operator()(0, 0), 9);

    std::vector<int> new_row({7, 8, 9});
    matrix->InsertRow(1, new_row);
    ASSERT_EQ(matrix->operator()(1, 0), 7);
    ASSERT_EQ(matrix->operator()(1, 1), 8);
    ASSERT_EQ(matrix->operator()(1, 2), 9);

    std::vector<int> new_column({10, 11, 12});
    matrix->InsertColumn(2, new_column);
    ASSERT_EQ(matrix->operator()(1, 0), 7);
    ASSERT_EQ(matrix->operator()(1, 1), 8);
    ASSERT_EQ(matrix->operator()(1, 2), 11);
    ASSERT_EQ(matrix->operator()(1, 3), 9);
}

TEST_F(IntMatrixTests, PropertiesTest)
{
    ASSERT_FALSE(matrix->IsSquare());

    std::vector<int> new_row({7, 8, 9});
    matrix->InsertRow(1, new_row);
    ASSERT_TRUE(matrix->IsSquare());
}

TEST_F(IntMatrixTests, FileLoadingTest)
{
    std::ifstream fp;
    fp.open("data/input_matrix.txt", std::ifstream::in);
    Matrix<int> matfp(fp);
    ASSERT_TRUE(matfp == *matrix);

    std::ifstream fp_flat;
    fp_flat.open("data/input_matrix_flat.txt", std::ifstream::in);
    Matrix<int> matfp_flat(fp_flat, 2, 3);
    ASSERT_TRUE(matfp_flat == *matrix);

    fp.close();
    fp_flat.close();
}

TEST_F(IntMatrixTests, NeighboursTests)
{
    Matrix<int> big_mat({{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}});

    auto sub1 = big_mat.CutWindow(0U, 0U, 1U);
    ASSERT_EQ(sub1(0U, 0U), 1);
    ASSERT_EQ(sub1.NRows(), 1U);
    ASSERT_EQ(sub1.NCols(), 1U);

    auto sub2 = big_mat.CutWindow(1U, 1U, 3U);
    IntMatrixData expected_data2({{1, 2, 3}, {6, 7, 8}, {11, 12, 13}});
    ASSERT_EQ(sub2.Data(), expected_data2);

    auto sub3 = big_mat.CutWindow(0U, 0U, 3U);
    IntMatrixData expected_data3({{0, 0, 0}, {0, 1, 2}, {0, 6, 7}});
    ASSERT_EQ(sub3.Data(), expected_data3);

    auto sub4 = big_mat.CutWindow(3U, 3U, 3U);
    IntMatrixData expected_data4({{13, 14, 15}, {18, 19, 20}, {0, 0, 0}});
    ASSERT_EQ(sub4.Data(), expected_data4);

    auto sub4_99 = big_mat.CutWindow(3U, 3U, 3U, 99);
    IntMatrixData expected_data4_99({{13, 14, 15}, {18, 19, 20}, {99, 99, 99}});
    ASSERT_EQ(sub4_99.Data(), expected_data4_99);
}

// TODO TEST_F(IntMatrixTests, ExceptionsTest)

template <class T>
struct TypeTests : public ::testing::Test
{
    static Matrix<T> matrix;
};

TYPED_TEST_CASE_P(TypeTests);
TYPED_TEST_P(TypeTests, BasicTests)
{
    auto matrix = TypeTests<TypeParam>::matrix;
    ASSERT_EQ(matrix.NRows(), 2U);
    ASSERT_EQ(matrix.Data().size(), 2U);
    ASSERT_EQ(matrix.NCols(), 3U);
    ASSERT_EQ(matrix.Data()[0].size(), 3U);
    ASSERT_FALSE(matrix.IsSquare());
}
REGISTER_TYPED_TEST_CASE_P(TypeTests, BasicTests);

typedef ::testing::Types<int, float, bool, char, std::string> MyTypes;
INSTANTIATE_TYPED_TEST_CASE_P(My, TypeTests, MyTypes);

template <>
Matrix<int> TypeTests<int>::matrix({{1, 2, 3}, {4, 5, 6}});
template <>
Matrix<float> TypeTests<float>::matrix({{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}});
template <>
Matrix<bool> TypeTests<bool>::matrix({{true, true, false}, {false, true, false}});
template <>
Matrix<char> TypeTests<char>::matrix({{'a', 'b', 'c'}, {'d', 'e', 'f'}});
template <>
Matrix<std::string> TypeTests<std::string>::matrix({{"a", "b", "c"}, {"d", "e", "f"}});
