#ifndef AUT_AP_2024_Spring_HW1
#define AUT_AP_2024_Spring_HW1
#include <vector>
#include <optional>

namespace algebra {
    // Matrix data structure
    template<typename T>
    using MATRIX = std::vector<std::vector<T>>;

    // Matrix initialization types
    enum class MatrixType { Zeros, Ones, Identity, Random };
    // Function template for matrix initialization
    template<typename T>
    MATRIX<T> create_matrix(std::size_t rows, std::size_t columns, std::optional<MatrixType> type = MatrixType::Zeros,
                            std::optional<T> lowerBound = std::nullopt, std::optional<T> upperBound = std::nullopt);
}

#endif //AUT_AP_2024_Spring_HW1
