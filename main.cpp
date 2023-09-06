#include <iostream>
#include <vector>

using namespace std;

class Matrix {
private:
    vector<vector<double>> data;
    int rows;
    int cols;
public:
    Matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        this->data.resize(rows, vector<double>(cols, 0.0));
    }

    Matrix(const vector<vector<double>>& data) {
        this->data = data;
        this->rows = data.size();
        this->cols = data[0].size();
    }

    void set(int i, int j, double val) {
        this->data[i][j] = val;
    }

    double get(int i, int j) const {
        return this->data[i][j];
    }

    int get_rows() const {
        return this->rows;
    }

    int get_cols() const {
        return this->cols;
    }
    Matrix plus(Matrix a) const {
        Matrix added(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                added.set(i, j, this->data[i][j] + a.data[i][j]);
            }
        }
        return added;
    }

    Matrix transpose() const {
        Matrix transposed(cols, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                transposed.set(j, i, data[i][j]);
            }
        }
        return transposed;
    }

    double determinant() const {
        if (rows != cols) {
            cerr << "Cannot compute determinant: matrix is not square" << endl;
            return 0.0;
        }
        if (rows == 1) {
            return data[0][0];
        }
        if (rows == 2) {
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        }
        double det = 0.0;
        for (int j = 0; j < cols; j++) {
            Matrix submatrix(rows - 1, cols - 1);
            for (int i = 1; i < rows; i++) {
                for (int k = 0; k < cols; k++) {
                    if (k < j) {
                        submatrix.set(i - 1, k, data[i][k]);
                    }
                    else if (k > j) {
                        submatrix.set(i - 1, k - 1, data[i][k]);
                    }
                }
            }
            det += pow(-1, j) * data[0][j] * submatrix.determinant();
        }
        return det;
    }

    Matrix inverse() const {
        if (rows != cols) {
            cerr << "Cannot compute inverse: matrix is not square" << endl;
            return Matrix(rows, cols);
        }
        double det = determinant();
        if (det == 0.0) {
            cerr << "Cannot compute inverse: matrix is singular" << endl;
            return Matrix(rows, cols);
        }
        Matrix adjoint(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                Matrix submatrix(rows - 1, cols - 1);
                for (int k = 0; k < rows; k++) {
                    if (k == i) {
                        continue;
                    }
                    for (int l = 0; l < cols; l++) {
                        if (l == j) {
                            continue;
                        }
                        int row = k < i ? k : k - 1;
                        int col = l < j ? l : l - 1;
                        submatrix.set(row, col, data[k][l]);
                    }
                }
                double cofactor = pow(-1, i + j) * submatrix.determinant();
                adjoint.set(j, i, cofactor);
            }
        }
        Matrix inverse(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                inverse.set(i, j, adjoint.get(i, j) / det);
            }
        }
        return inverse;
    }

    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    vector<vector<double>> data = { {1, 3, 3}, {1, 1, 5}, {1, 2,2} }, data2 = { {1, 3, 1}, {1, 1, 1}, {1, 2,1} };
    Matrix mat(data);
    Matrix mat1(data2);
    cout << "Original matrix:" << endl;
    mat.print();
    cout << "Original matrix2:" << endl;
    mat1.print();
    cout << "Transposed matrix:" << endl;
    Matrix transpose = mat.transpose();
    transpose.print();
    cout << "Determinant: " << mat.determinant() << endl;
    cout << "Inverse matrix:" << endl;
    Matrix inverse = mat.inverse();
    inverse.print();
    cout << "matrix+matrix2:" << endl;
    Matrix res = mat.plus(mat1);
    res.print();
    return 0;
}