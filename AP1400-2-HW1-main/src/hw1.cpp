#include "hw1.h"
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <functional>
using namespace algebra;
using Row = vector<double>;

static inline pair<int, int> getMatrixRowAndCol(const Matrix &matrix)
{
    if (matrix.size() == 0)
    {
        return {0, 0};
    }
    int Col = matrix[0].size();
    for (auto row : matrix)
    {
        if (row.size() != Col)
        {
            throw logic_error("");
        }
    }
    return {matrix.size(), Col};
}
static void for_each(Matrix &matrix, function<void(double &)> f)
{
    for_each(matrix.begin(), matrix.end(), [&f](Row &row)
             { for_each(row.begin(), row.end(), f); });
}

Matrix algebra::zeros(size_t n, size_t m)
{
    return vector<Row>(n, Row(m, 0));
}

Matrix algebra::ones(size_t n, size_t m)
{
    return vector<Row>(n, Row(m, 1));
}

Matrix algebra::random(size_t n, size_t m, double min, double max)
{
    if (min > max)
    {
        throw logic_error("");
    }
    Matrix ret(n, Row(m));
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(min, max);
    int dice_roll = distribution(generator);
    for_each(ret, [&generator, &distribution](double &d)
             { d = distribution(generator); });
    return ret;
}

Matrix algebra::multiply(const Matrix &matrix, double c)
{
    Matrix ret = matrix;
    for_each(ret, [c](double &d)
             { d *= c; });
    return ret;
}

Matrix algebra::multiply(const Matrix &matrix1, const Matrix &matrix2)
{
    if (matrix1.size() == 0 || matrix2.size() == 0)
    {
        return Matrix();
    }
    auto RC = getMatrixRowAndCol(matrix1);
    int Row1 = RC.first;
    int Col1 = RC.second;
    RC = getMatrixRowAndCol(matrix2);
    int Row2 = RC.first;
    int Col2 = RC.second;

    if (Col1 != Row2)
    {
        throw logic_error("");
    }

    Matrix result = zeros(Row1, Col2);
    for (int r = 0; r < Row1; r++)
    {
        for (int c = 0; c < Col2; c++)
        {
            Element sumOfProduct = 0;
            for (int i = 0; i < Row2; i++)
            {
                sumOfProduct += matrix1[r][i] * matrix2[i][c];
            }
            result[r][c] = sumOfProduct;
        }
    }
    return result;
}

void algebra::show(const Matrix &matrix)
{
    std::cout << std::fixed << std::setprecision(3);
    for (auto row : matrix)
    {
        for (auto number : row)
        {
            cout << number << " ";
        }
        cout << endl;
    }
    std::cout << std::defaultfloat;
}

Matrix algebra::sum(const Matrix &matrix, double c)
{
    Matrix ret = matrix;
    for_each(ret, [c](Element &e)
             { e += c; });
    return ret;
}

Matrix algebra::transpose(const Matrix &matrix)
{
    auto RC = getMatrixRowAndCol(matrix);
    int Row = RC.first;
    int Col = RC.second;
    Matrix result = zeros(Col, Row);
    for (int r = 0; r < Row; r++)
    {
        for (int c = 0; c < Col; c++)
        {
            result[c][r] = matrix[r][c];
        }
    }
    return result;
}

Matrix algebra::sum(const Matrix &matrix1, const Matrix &matrix2)
{
    auto RC1 = getMatrixRowAndCol(matrix1);
    auto RC2 = getMatrixRowAndCol(matrix2);
    if (RC1.first != RC2.first || RC1.second != RC2.second)
    {
        throw logic_error("");
    }
    Matrix result = zeros(RC1.first, RC1.second);
    for (int r = 0; r < RC1.first; r++)
    {
        for (int c = 0; c < RC1.second; c++)
        {
            result[r][c] = matrix1[r][c] + matrix2[r][c];
        }
    }
    return result;
}

Matrix algebra::minor(const Matrix &matrix, size_t n, size_t m)
{
    auto RC = getMatrixRowAndCol(matrix);
    int Row = RC.first, Col = RC.second;
    if (Row <= n || Col <= m)
    {
        throw logic_error("");
    }
    Matrix result = matrix;
    result.erase(result.begin() + n);
    for (auto &row : result)
    {
        row.erase(row.begin() + m);
    }
    return result;
}

double algebra::determinant(const Matrix &matrix)
{
    auto RC = getMatrixRowAndCol(matrix);
    if (RC.first != RC.second)
    {
        throw logic_error("");
    }
    if (RC.first == 0)
    {
        return 1;
    }
    double result = 0;
    for (int i = 0; i < RC.first; i++)
    {
        result += (i % 2 == 0 ? 1 : -1) * matrix[0][i] * determinant(minor(matrix, 0, i));
    }
    return result;
}

Matrix adj(const Matrix &matrix)
{
    auto RC = getMatrixRowAndCol(matrix);
    if (RC.first != RC.second)
    {
        throw logic_error("");
    }
    int Row = RC.first;
    int Col = RC.second;
    Matrix result = zeros(Row, Col);
    for (int r = 0; r < Row; r++)
    {
        for (int c = 0; c < Col; c++)
        {
            result[r][c] = ((r + c) % 2 == 0 ? 1 : -1) * determinant(minor(matrix, r, c));
        }
    }
    return transpose(result);
}

Matrix algebra::inverse(const Matrix &matrix)
{
    Matrix result;
    if (abs(determinant(matrix)) <= __DBL_EPSILON__)
    {
        throw logic_error("");
    }
    return multiply(adj(matrix), 1.0 / determinant(matrix));
}

Matrix algebra::concatenate(const Matrix &matrix1, const Matrix &matrix2, int axis)
{
    Matrix result = matrix1;
    auto RC1 = getMatrixRowAndCol(matrix1);
    auto RC2 = getMatrixRowAndCol(matrix2);
    if (axis == 0)
    {
        if (RC1.second != RC2.second)
        {
            throw logic_error("");
        }
        for (auto &row : matrix2)
        {
            result.push_back(row);
        }
        return result;
    }
    else if (axis == 1)
    {
        if (RC1.first != RC2.first)
        {
            throw logic_error("");
        }
        for (int i = 0; i < RC1.first; i++)
        {
            result[i].insert(result[i].end(), matrix2[i].begin(), matrix2[i].end());
        }
        return result;
    }
    else
    {
        throw logic_error("");
    }
}

Matrix algebra::ero_swap(const Matrix &matrix, size_t r1, size_t r2)
{
    auto RC = getMatrixRowAndCol(matrix);
    if (r1 < 0 || r2 < 0 || r1 >= RC.first || r2 >= RC.first)
    {
        throw logic_error("");
    }
    Matrix result = matrix;
    swap(result[r1], result[r2]);
    return result;
}

Matrix algebra::ero_multiply(const Matrix &matrix, size_t r, double c)
{

    auto RC = getMatrixRowAndCol(matrix);
    if (r < 0 || r >= RC.first)
    {
        throw logic_error("");
    }
    Matrix result = matrix;
    for_each(result[r].begin(), result[r].end(), [c](Element &e)
             { e *= c; });
    return result;
}

Matrix algebra::ero_sum(const Matrix &matrix, size_t r1, double c, size_t r2)
{
    auto RC = getMatrixRowAndCol(matrix);
    if (r1 < 0 || r2 < 0 || r1 >= RC.first || r2 >= RC.first)
    {
        throw logic_error("");
    }
    Matrix result = matrix;
    for (int col = 0; col < RC.second; col++)
    {
        result[r2][col] += c * matrix[r1][col];
    }
    return result;
}

Matrix algebra::upper_triangular(const Matrix &matrix)
{
    auto RC = getMatrixRowAndCol(matrix);
    if (RC.first != RC.second){
        throw logic_error("");
    }
    Matrix result = matrix;
    for(int i = 0; i < RC.first; i++) {
        for(int j = i + 1; j < RC.first; j++) {
            Element factor = result[j][i] / result[i][i] * -1;
            result = ero_sum(result, i, factor, j);
        }
    }
    return result;
}