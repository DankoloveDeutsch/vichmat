#include <iostream>
#include <math.h>
#include <cassert>

class Gauss {
private:
    int n = 0, m = 0,i,j,k;
    float temp;
    float* tmp;
    float** matrix_up;
    float** matrix_equations;
    float** matrix_variables;
    float** matrix_answer;
    float** matrix_equations3;
    float** Y;
    float** z;
    double max_value;
    int max_value_index;
public:
    Gauss() {
        n = 0;
        m = 0;
        k = 0;
    };
    double f(int select, double x) {
        switch (select)
        {
        case 0:
            return 1;
            break;
        case 1:
            return x;
            break;
        case 2:
            return pow(exp(1), -1*x);
            break;
       }
    }

    void out_matrix(float** mat, int n, int m) {
        int i, j;
        for (i = 0; i < n; i++) {
            std::cout << std::endl;
            for (j = 0; j < m; j++) {
                std::cout << mat[i][j] << " ";
            }
        }
    }
    float** get_matrix(int n, int m) {
        float** matrix = new float* [n];
        for (int i = 0; i < n; i++) {
            matrix[i] = new float[m];
        }
        return matrix;
    };
    void sizematrix() {
        bool flag = true;
        while (flag) {
        std::cout << "Number of equations: ";
        std::cin >> n;
        std::cout << "Number of variables: ";
        std::cin >> m;
        if (n == m) {
            
            flag = false;
        }
        else {
            std::cout << "\nError\nequations != variables. Please repeat.";
        }
        matrix_up = get_matrix(n, m+1);
        matrix_equations = get_matrix(n, m);
        matrix_variables = get_matrix(n, 1);
        };
        
        for (i = 0; i < n; i++){
            for (j = 0; j < m+1; j++)
            {
                std::cout << " Element " << "[" << i + 1 << " , " << j + 1 << "]: ";
                
                std::cin >> temp;
                matrix_up[i][j] = temp;
                if (m-j>=1) {
                    matrix_equations[i][j]=temp;
                }
                std::cout << j << m;
                if (j==m) {
                    matrix_variables[i][0] = temp;
                } 
            }
        }
    
        
   

    };
    float** trans_matrix(float** mat, int n) {
        int i, j;
        float** trans_ms = get_matrix(n, n);
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                trans_ms[j][i] = mat[i][j];
            }
        }
        return trans_ms;
    }
    float** multiplication(float** a_mat, float** b_mat, int n, int a_size, int b_size) {
        float** new_matrix = get_matrix(a_size, b_size);
        for (i = 0; i < a_size; i++) {
            for (j = 0; j < b_size; j++) {
                new_matrix[i][j] = 0;
                for (k = 0; k < n; k++) {
                    new_matrix[i][j] += a_mat[i][k] * b_mat[k][j];
                }
            }
        }
        return new_matrix;
    }
    void swap_rows(float** matrix,int n,int i, int j)
    {
        
        for (int k = 0; k <= n; k++)
            std::swap(matrix[i][k], matrix[j][k]);
    }

    void averse() {
        // прямой ход
        if (rec_determinant(matrix_equations, n) == 0) {
            std::cout << "\nError determinant = 0\n";
        }
        temp = 0;
        k = 0;
        
        for (k = 0; k < n; k++) {
            max_value = abs(matrix_up[k][k]);
            max_value_index = k;

            for (i = k + 1; i < n; i++)
                if (abs(matrix_up[i][k]) > max_value) {
                    max_value = abs(matrix_up[i][k]);
                    max_value_index = i;
                }

            assert(matrix_up[max_value_index][k] != 0);

            if (k != max_value_index) {
                swap_rows(matrix_up,n, k, max_value_index);
            }

   
            for (i = n; i >= k; i--) {
                matrix_up[k][i] /= matrix_up[k][k];
            }
            for (i = k + 1; i < n; i++) {
                temp = matrix_up[i][k] / matrix_up[k][k];
                for (j = k + 1; j <= n; j++) {
                    matrix_up[i][j] -= matrix_up[k][j] * temp;
                }
                matrix_up[i][k] = 0;
            }
            std::cout << std::endl;
            out_matrix(matrix_up, n, m);
        }
    };
    void reverse() {
        // обратный ход 
        matrix_answer = get_matrix(n, 1);
        matrix_answer[n - 1][0] = matrix_up[n - 1][n];
        for (i = n - 2; i >= 0; i--)
        {
            matrix_answer[i][0] = matrix_up[i][n];
            for (j = i + 1; j < n; j++) {
                matrix_answer[i][0] -= matrix_up[i][j] * matrix_answer[j][0];
            }
            std::cout << std::endl;
            out_matrix(matrix_up, n, m+1);
        }
        std::cout << "\n\nAx=B answer\n";
        out_matrix(matrix_answer, n, 1);
    };
 
    float get_alg_addition(float** mat, int n, int x, int y) {
        float** algebric_addition = get_matrix(n - 1, n - 1);
        int now_row = 0, now_column = 0;
        for (int i = 0; i < n; i++) {
            if (i == x) continue;
            for (int j = 0; j < n; j++) {
                if (j == y) continue;
                algebric_addition[now_row][now_column] = mat[i][j];
                now_column++;
            }
            now_column = 0;
            now_row++;
        }
        float result = rec_determinant(algebric_addition, n - 1);
        del_matrix(algebric_addition, n - 1);
        if ((x + y) % 2 == 1) return -result;
        else return result;
    };
    float rec_determinant(float** mat, int n) {
        // рекурсивная ф-я получения детерминанта
        if (n == 1)
            return mat[0][0];
        if (n == 2)
            return mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];
        float determinant = 0;
        for (int i = 0; i < n; i++) {
            float result = get_alg_addition(mat, n, i, 0);
            determinant += mat[i][0] * result;
        }
        return determinant;
    };
    void del_matrix(float** mat, int n) {
        for (int i = 0; i < n; i++) {
            delete[] mat[i];
        }
        delete[] mat;
        mat = nullptr;
    };
    void start() {

        sizematrix();
        std::cout << "\nMatrix A" << std::endl;
        out_matrix(matrix_equations, n, m);
        averse();
        
        reverse();
    }
    ~Gauss() {
        del_matrix(matrix_up, n);
        del_matrix(matrix_equations, n);
        del_matrix(matrix_variables, n);
        del_matrix(matrix_answer, n);
        del_matrix(matrix_equations3, n);
        del_matrix(Y, n);
        del_matrix(z, n);
    };
};



int main() {
    Gauss* a = new Gauss;
    a->start();
}