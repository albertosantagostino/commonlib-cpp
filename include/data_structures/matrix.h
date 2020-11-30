/// @file matrix.h
/// @author Alberto Santagostino

#ifndef DATA_STRUCTURES_MATRIX_H
#define DATA_STRUCTURES_MATRIX_H

#include <charconv>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace commonlib
{
/// @class Matrix
/// @brief 2D generic matrix template
/// @tparam T Type of data stored
template <typename T>
class Matrix
{
  public:
    Matrix(const std::size_t n_rows, const std::size_t n_cols);
    Matrix(const std::vector<std::vector<T>> matrix);
    Matrix(std::ifstream& fp, const std::size_t n_rows, const std::size_t n_cols);
    Matrix(std::ifstream& fp);

    // Setters / Inserters
    void InsertRow(const std::size_t index, const std::vector<T> new_row = {});
    void InsertColumn(const std::size_t index, const std::vector<T> new_col = {});
    void RemoveRow(const std::size_t index);     // TODO
    void RemoveColumn(const std::size_t index);  // TODO

    // Getters
    inline std::vector<std::vector<T>> Data() const { return m_data; }
    inline std::vector<T> Row(const std::size_t row) { return m_data[row]; };
    inline std::vector<T> Column(const std::size_t col)
    {
        std::vector<T> out;
        for (const auto& row : m_data)
            out.push_back(row[col]);
        return out;
    }
    inline std::size_t NRows() const { return m_data.size(); }
    inline std::size_t NCols() const { return m_data[0].size(); }

    // Utils / Properties
    void Print(char row_sep = '\n', char col_sep = ' ');
    inline bool IsSquare() { return (NRows() == NCols()); }
    bool IsNumeric();  // TODO

    // Operators
    T& operator()(std::size_t row, std::size_t col);
    T const& operator()(std::size_t row, std::size_t col) const;
    inline bool operator==(T const& other) { return m_data == other.m_data; }
    inline bool operator!=(T const& other) { return m_data != other.m_data; }

  protected:
    std::vector<std::vector<T>> m_data;
    std::size_t m_rows;
    std::size_t m_cols;

    void m_UnpackFlatMatrix(std::vector<T> flat_matrix);
    inline void m_UpdateSize()
    {
        m_rows = m_data.size();
        m_cols = m_data[0].size();
    }
};

/// @brief Constructor: initialize a matrix with the default value of T
/// @param n_rows Number of rows
/// @param n_cols Number of columns
template <typename T>
Matrix<T>::Matrix(const std::size_t n_rows, const std::size_t n_cols) : m_data(n_rows), m_rows(n_rows), m_cols(n_cols)
{
    if ((m_rows == 0) || (m_cols == 0))
        throw std::length_error("Matrix<T>::Matrix(std::size_t n_rows, std::size_t n_cols): Dimensions cannot be 0");
    for (std::size_t i{0}; i < m_rows; ++i)
        m_data[i].resize(m_cols);
}

/// @brief Constructor: initialize a matrix with the default value of T
/// @param matrix The matrix represented as a vector of vectors
/// @throw std::length_error If the size is not coherent (not all vectors have same length)
template <typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>> matrix) : m_data(matrix)
{
    std::size_t row_length{m_data[0].size()};
    for (std::size_t i = 1; i < m_data.size(); ++i)
    {
        if (row_length != m_data[i].size())
        {
            throw std::length_error(
                "Matrix<T>::Matrix(std::vector<std::vector<T>> matrix): Size not coherent, all vectors must have the "
                "same length");
        }
    }
    m_UpdateSize();
}

/// @brief Constructor: initialize the matrix using its monodimensional representation
/// @param flat_matrix Flat matrix represented as a vector of elements
/// @param n_rows Number of rows
/// @param n_cols Number of columns
/// @throw std::lenght_error If the matrix cannot be unpacked using the provided n_rows and n_cols values
template <typename T>
Matrix<T>::Matrix(std::ifstream& fp, const std::size_t n_rows, const std::size_t n_cols)
    : m_rows(n_rows), m_cols(n_cols)
{
    if (!fp.is_open())
    {
        throw std::ios_base::failure(
            "Matrix<T>::Matrix(std::ifstream& fp, std::size_t n_rows, std::size_t n_cols): File not found");
    }

    std::string line;
    getline(fp, line);

    std::istringstream streamline(line);
    std::string tok;
    std::vector<T> flat_matrix;
    while (getline(streamline, tok, ','))
    {
        auto value = T{};
        std::from_chars(tok.data(), tok.data() + tok.size(), value);
        flat_matrix.push_back(value);
    }
    if (flat_matrix.size() != m_rows * m_cols)
        throw std::length_error(
            "Matrix<T>::Matrix(std::ifstream& fp, std::size_t n_rows, std::size_t n_cols): Flat_matrix length "
            "is not equal to n_rows*n_cols");

    m_UnpackFlatMatrix(flat_matrix);
}

/// @brief Constructor: initialize the matrix using the provided file
/// @param fp File stream to use as input for the matrix
template <typename T>
Matrix<T>::Matrix(std::ifstream& fp)
{
    if (!fp.is_open())
    {
        throw std::ios_base::failure("Matrix<T>::Matrix(std::ifstream& fp): File not found");
    }

    std::string line;
    while (getline(fp, line))
    {
        std::vector<T> row;
        std::istringstream streamline(line);
        std::string tok;
        while (getline(streamline, tok, ','))
        {
            auto value = T{};
            std::from_chars(tok.data(), tok.data() + tok.size(), value);
            row.push_back(value);
        }
        m_data.push_back(row);
    }
    m_UpdateSize();
}

/// @brief Print the matrix
/// @param row_sep Separator between rows (default is '\n')
/// @param col_sep Separator between columns (default is ' ')
template <typename T>
void Matrix<T>::Print(char row_sep, char col_sep)
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

/// @brief Insert a new row at the specified index
/// @param index Index of the row after which insert the new row
/// @param new_row New row
template <typename T>
void Matrix<T>::InsertRow(const std::size_t index, const std::vector<T> new_row)
{
    if ((index > m_rows) || (new_row.size() != m_cols))
    {
        throw std::length_error(
            "Matrix<T>::InsertRow(std::size_t index, std::vector<T> new_row): Check index value and new_row length");
    }
    auto it = m_data.begin();
    m_data.insert(it + index, new_row);
    m_UpdateSize();
}

/// @brief Insert a new column at the specified index
/// @param index Index of the column after which insert the new column
/// @param new_column New column
template <typename T>
void Matrix<T>::InsertColumn(const std::size_t index, const std::vector<T> new_column)
{
    if ((index > m_cols) || (new_column.size() != m_rows))
    {
        throw std::length_error(
            "Matrix<T>::InsertColumn(std::size_t index, std::vector<T> new_column): Check index value and new_column "
            "length");
    }
    std::size_t i{0};
    std::for_each(m_data.begin(), m_data.end(), [index, new_column, &i](std::vector<T>& v) {
        v.insert(v.begin() + index, new_column[i++]);
    });
    m_UpdateSize();
}

/// @brief Unpack a unidimensional matrix to m_data, using m_rows and m_cols as dimensions
/// @param flat_matrix std::vector containing the elements of the matrix
template <typename T>
void Matrix<T>::m_UnpackFlatMatrix(std::vector<T> flat_matrix)
{
    std::size_t index = 0;
    for (std::size_t i{0}; i < m_rows; ++i)
    {
        std::vector<T> row;
        for (std::size_t j = 0; j < m_cols; ++j)
        {
            row.push_back(flat_matrix[index++]);
        }
        m_data.push_back(row);
    }
}

template <typename T>
T& Matrix<T>::operator()(std::size_t row, std::size_t col)
{
    if (row >= m_rows || col >= m_cols) throw std::out_of_range("Matrix<T>::operator(): Index is out of range");
    return m_data[row][col];
}

template <typename T>
T const& Matrix<T>::operator()(std::size_t row, std::size_t col) const
{
    if (row >= m_rows || col >= m_cols) throw std::out_of_range("Matrix<T>::operator(): Index is out of range");
    return m_data[row][col];
}

template <typename T>
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    return lhs.Data() == rhs.Data();
}

template <typename T>
bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    return lhs.Data() != rhs.Data();
}

}  // namespace commonlib

#endif  // DATA_STRUCTURES_MATRIX_H
