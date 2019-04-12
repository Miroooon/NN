#include <iostream>
#include <cmath>
#include <cstring>

#define SIZE 300
#define LR 0.2500

using namespace std;

double randM(double M, double N){
    return (M + (rand() / (RAND_MAX/(N-M))))-0.5;
}

class matrix2{
    public:
        int rows;
        int cols;
        float** mat;
        void init(int r, int c, int total = 0){
            rows = r;
            cols = c;
            mat = new float *[rows];
            for (int i = 0; i < rows; i++) {
                mat[i] = new float [cols];
            }

            if (total == 0) {
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        mat[i][j] = 0;
                    }
                }
            }


            if(total == 1){
                for (int i = 0; i < rows; i++)
                    for (int j = 0; j < cols; j++)
                        mat[i][j] = randM(0.1, 0.99);
            }
        }



        void free(){
            for (int i = 0; i < rows; i++) {
                delete []mat[i];
            }
            delete []mat;
        }
};

class matrix{
    public:
        int rows;
        int cols;
        float** mat;
        void init(int r, int c, int total = 0){
            for (int i = 0; i < rows; i++) {
                delete []mat[i];
            }
            delete []mat;
            rows = r;
            cols = c;
            mat = new float *[rows];
            for (int i = 0; i < rows; i++) {
                mat[i] = new float [cols];
            }

            if (total == 0) {
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        mat[i][j] = 0;
                    }
                }
            }

            if(total == 1){
                for (int i = 0; i < rows; i++)
                    for (int j = 0; j < cols; j++)
                        mat[i][j] = randM(0.1, 0.99);
            }
        }

        matrix(){
            rows = 1;
            cols = 1;
            mat = new float *[rows];
            for (int i = 0; i < rows; i++) {
                mat[i] = new float [cols];
            }
        }

        matrix(int r, int c, int total = 0){
            rows = r;
            cols = c;
            mat = new float *[rows];
            for (int i = 0; i < rows; i++) {
                mat[i] = new float [cols];
            }

            if (total == 0) {
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        mat[i][j] = 0;
                    }
                }
            }

            if(total == 1){
                for (int i = 0; i < rows; i++)
                    for (int j = 0; j < cols; j++)
                        mat[i][j] = randM(0.1, 0.99);
            }
        }

        matrix operator= (matrix matr){
            for (int i = 0; i < rows; i++) {
                delete []mat[i];
            }
            delete []mat;

            rows = matr.rows;
            cols = matr.cols;
            mat = new float *[rows];
            for (int i = 0; i < rows; i++) {
                mat[i] = new float [cols];
            }

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    mat[i][j] = matr.mat[i][j];
                }
            }
            for (int i = 0; i < matr.rows; i++) {
                delete []matr.mat[i];
            }
            delete []matr.mat;
        }

        matrix operator* (matrix matr){
            matrix lol(rows, cols);

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    lol.mat[i][j] = mat[i][j] * matr.mat[i][j];
                }
            }
            return lol;
        }

        matrix operator- (matrix matr){
            matrix lol(rows, cols);

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    lol.mat[i][j] = mat[i][j] - matr.mat[i][j];
                }
            }
            return lol;
        }

        void show(int total = 0){
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    cout << mat[i][j] << ' ';
                }
                if(total == 0)
                    cout << '\n';
            }
        }

        void free(){
            for (int i = 0; i < rows; i++) {
                delete []mat[i];
            }
            delete []mat;
        }

};

matrix operator- (float ci,  matrix matr){
    matrix lol(matr.rows, matr.cols);

    for (int i = 0; i < matr.rows; i++) {
        for (int j = 0; j < matr.cols; j++) {
            lol.mat[i][j] = ci -  matr.mat[i][j];
        }
    }
    return lol;
}

matrix operator- (matrix matr,  float ci){
    matrix lol(matr.rows, matr.cols);

    for (int i = 0; i < matr.rows; i++) {
        for (int j = 0; j < matr.cols; j++) {
            lol.mat[i][j] = matr.mat[i][j] - ci;
        }
    }
    return lol;
}

matrix  operator* (matrix matr, int ci){
    matrix lol(matr.rows, matr.cols);

    for (int i = 0; i < matr.rows; i++) {
        for (int j = 0; j < matr.cols; j++) {
            lol.mat[i][j] = matr.mat[i][j] * ci;
        }
    }
    return lol;
}

matrix  operator* (int ci, matrix matr){
    matrix lol(matr.rows, matr.cols);

    for (int i = 0; i < matr.rows; i++) {
        for (int j = 0; j < matr.cols; j++) {
            lol.mat[i][j] = matr.mat[i][j] * ci;
        }
    }
    return lol;
}


matrix sigmoida(matrix Matrix){
    float e = 2.7180;
    matrix Matrixp(Matrix.rows, Matrix.cols);

    for (int i = 0; i < Matrix.rows; i++) {
        for (int j = 0; j < Matrix.cols; j++) {
             Matrixp.mat[i][j] = 1 / (1 + pow(e, (Matrix.mat[i][j] * -1)));
        }
    }
    return Matrixp;
}

matrix matrix_multiplication(matrix Matrix1, matrix Matrix2){
    matrix Matrixp(Matrix1.rows, Matrix2.cols);

    float temp = 0.0;
    for (int i = 0; i < Matrix1.rows; i++){
        for (int j = 0; j < Matrix2.cols; j++){
            for(int k = 0; k < Matrix1.cols; k++){
                 temp += Matrix1.mat[i][k] * Matrix2.mat[k][j];
            }
            Matrixp.mat[i][j] = temp;
            temp = 0.0;
        }
    }

    return Matrixp;
}

matrix transpose(matrix Matrix){
    matrix Matrixp(Matrix.cols, Matrix.rows);

    float temp;
    for(int i = 0; i < Matrix.rows; ++i){
        for(int j = 0; j < Matrix.cols; ++j){
            Matrixp.mat[j][i] = Matrix.mat[i][j];
        }
    }
    return Matrixp;
}

int main(int argc, char const *argv[]) {
    float ll = 1;
    matrix l(2, 2, 1);
    matrix l1(2, 2, 1);
    matrix b(2,2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            b.mat[i][j] = l.mat[i][j] * l1.mat[i][j];
        }
    }

    l.show();
    std::cout << "\n" << '\n';
    l1.show();
std::cout << "\n" << '\n';
    b.show();
std::cout << "\n" << '\n';

    return 0;
}
