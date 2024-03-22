#include <iostream>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <vector>

class Matrix {
private:
  std::vector<float> _data;
  size_t _rows;
  size_t _cols;

public:
  Matrix(size_t rows, size_t cols) : _data(rows * cols, 0), _rows(rows), _cols(cols) { }

  size_t rows() const noexcept {
    return _rows;
  }

  size_t cols() const noexcept {
    return _cols;
  }

  float operator()(size_t i, size_t j) const {
    return _data[i * _cols + j];
  }

  float& operator()(size_t i, size_t j) {
    return _data[i * _cols + j];
  }
};

std::ostream& operator<<(std::ostream& stream, const Matrix& m) {
  const size_t rows = m.rows();
  const size_t cols = m.cols();

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      stream << m(i, j) << ' ';
    }
    stream << '\n';
  }

  return stream;
}

float row_x_col(const Matrix& m1, size_t r1, const Matrix& m2, size_t c2) {
  const size_t n = m1.cols();

  double v = 0;
  for (size_t i = 0; i < n; ++i) {
    v += static_cast<double>(m1(r1, i)) * m2(i, c2);
  }

  return static_cast<float>(v);
}

void multiply_v1(const Matrix& m1, const Matrix& m2, Matrix& r) {
  if (m1.cols() != m2.rows()) {
    throw std::logic_error("m1.cols() != m2.rows()");
  }

  if (m1.rows() != r.rows()) {
    throw std::logic_error("m1.rows() != r.rows()");
  }

  if (m2.cols() != r.cols()) {
    throw std::logic_error("m2.cols() != r.cols()");
  }

  const size_t rows = r.rows();
  const size_t cols = r.cols();
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      r(i, j) = row_x_col(m1, i, m2, j);
    }
  }
}

void multiply_v2_internal(const Matrix& m1, const Matrix& m2, Matrix& r, size_t row_begin, size_t row_end) {
  const size_t rows = r.rows();
  const size_t cols = r.cols();
  for (size_t i = row_begin; i < row_end; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      r(i, j) = row_x_col(m1, i, m2, j);
    }
  }
}

void multiply_v2(const Matrix& m1, const Matrix& m2, Matrix& r) {
  if (m1.cols() != m2.rows()) {
    throw std::logic_error("m1.cols() != m2.rows()");
  }

  if (m1.rows() != r.rows()) {
    throw std::logic_error("m1.rows() != r.rows()");
  }

  if (m2.cols() != r.cols()) {
    throw std::logic_error("m2.cols() != r.cols()");
  }

  const size_t tn = 4;
  const size_t n = r.rows() / tn;

  std::thread t1(multiply_v2_internal, std::cref(m1), std::cref(m2), std::ref(r), 0 * n, 1 * n);
  std::thread t2(multiply_v2_internal, std::cref(m1), std::cref(m2), std::ref(r), 1 * n, 2 * n);
  std::thread t3(multiply_v2_internal, std::cref(m1), std::cref(m2), std::ref(r), 2 * n, 3 * n);
  std::thread t4(multiply_v2_internal, std::cref(m1), std::cref(m2), std::ref(r), 3 * n, 4 * n);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
}

int main() {
  const size_t n = 1000;

  std::cout << "Creating matrices...\n";

  Matrix m1(n, n);
  Matrix m2(n, n);
  Matrix r1(n, n);
  Matrix r2(n, n);

  std::cout << "Computing v1...\n";

  multiply_v1(m1, m2, r1);

  std::cout << "Computing v2...\n";

  multiply_v2(m1, m2, r2);

  std::cout << "Completed\n";
}
