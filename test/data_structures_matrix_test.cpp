/// @file data_structures_matrix_test.cpp
/// @test commonlib::Matrix

#include <iostream>
#include <string>
#include <vector>

#include <data_structures/matrix.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace commonlib;

class IntMatrixTests : public ::testing::Test
{
  protected:
    Matrix<int>* matrix;
    virtual void SetUp() { matrix = new Matrix<int>({{1, 2, 3}, {4, 5, 6}}); }
    virtual void TearDown() { delete matrix; }
};

TEST_F(IntMatrixTests, AccessTests)
{
    std::vector<std::vector<int>> expected_data({{1, 2, 3}, {4, 5, 6}});
    std::vector<int> expected_row({1, 2, 3});
    std::vector<int> expected_column({1, 4});
    ASSERT_EQ(matrix->Data(), expected_data);
    ASSERT_EQ(matrix->Row(0), expected_row);
    ASSERT_EQ(matrix->Column(0), expected_column);
    ASSERT_EQ(matrix->NRows(), 2);
    ASSERT_EQ(matrix->NCols(), 3);
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
    ASSERT_EQ(matrix.NRows(), 2);
    ASSERT_EQ(matrix.NCols(), 3);
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
