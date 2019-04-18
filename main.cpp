#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

#define SIZE 100
#define LR 0.25000

double randM(double M, double N){
    return (M + (rand() / (RAND_MAX/(N-M))))-0.5;
}

class matrix{
    public:
        int rows;
        int cols;
        float** mat;

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

        matrix transpose(){
            matrix Matrixp(cols, rows);

            for(int i = 0; i < rows; ++i){
                for(int j = 0; j < cols; ++j){
                    Matrixp.mat[j][i] = mat[i][j];
                }
            }
            return Matrixp;
        }

        matrix operator= (matrix matr){
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

class NeuralNetwork{
    public:
        matrix wih;
        matrix who;
        NeuralNetwork(int input_nodes, int hidden_nodes, int output_nodes, float learningrate){
            i_n = input_nodes;
            o_n = output_nodes;
            h_n = hidden_nodes;
            lr = learningrate;

            a.init(10, 1, 0);
            b.init(10, 1, 0);
            c.init(10, 1, 0);
            d.init(1, SIZE, 0);
            f.init(10, SIZE, 0);

            g.init(SIZE, 1, 0);
            h.init(SIZE, 1, 0);
            p.init(SIZE, 1, 0);
            l.init(1, 784, 0);
            m.init(SIZE, 784, 0);

            srand(time(NULL));
            wih.init(SIZE, 784, 1);
            who.init(10, SIZE, 1);

        }

        void back(matrix inputs, matrix targets){
            //who
            //self.who += self.lr * numpy.dot((output_errors * final_outputs * ( 1.0 - final_outputs)), numpy.transpose(hidden_outputs))
            float tempk = 0.0;

            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 1; j++) {
                    a.mat[i][j] = 1.0000 - final_outputs.mat[i][j];
                }
            }

            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 1; j++) {
                    b.mat[i][j] = output_errors.mat[i][j] * final_outputs.mat[i][j];
                }
            }

            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 1; j++) {
                    c.mat[i][j] = a.mat[i][j] * b.mat[i][j];
                }
            }

            for(int i = 0; i < 100; ++i){
                for(int j = 0; j < 1; ++j){
                    d.mat[j][i] = hidden_outputs.mat[i][j];
                }
            }

            tempk = 0;
            for (int i = 0; i < 10; i++){
                for (int j = 0; j < 100; j++){
                    for(int k = 0; k < 1; k++){
                         tempk += c.mat[i][k] * d.mat[k][j];
                    }
                    f.mat[i][j] = tempk;
                    tempk = 0;
                }
            }

            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 1; j++) {
                    f.mat[i][j] = LR * f.mat[i][j];
                }
            }

            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 1; j++) {
                    who.mat[i][j] = who.mat[i][j] + f.mat[i][j];
                }
            }



            //wih
            //self.wih += self.lr * numpy.dot( (hidden_errors * hidden_outputs * (1.0 - hidden_outputs)), numpy.transpose(inputs))
            for (int i = 0; i < 100; i++) {
                for (int j = 0; j < 1; j++) {
                    g.mat[i][j] = 1.0000 - hidden_outputs.mat[i][j];
                }
            }

            for (int i = 0; i < 100; i++) {
                for (int j = 0; j < 1; j++) {
                    h.mat[i][j] = hidden_errors.mat[i][j] * hidden_outputs.mat[i][j];
                }
            }

            for (int i = 0; i < 100; i++) {
                for (int j = 0; j < 1; j++) {
                    p.mat[i][j] = g.mat[i][j] * h.mat[i][j];
                }
            }

            for(int i = 0; i < 784; ++i){
                for(int j = 0; j < 1; ++j){
                    l.mat[j][i] = inputs.mat[i][j];
                }
            }

            tempk = 0;
            for (int i = 0; i < 100; i++){
                for (int j = 0; j < 784; j++){
                    for(int k = 0; k < 1; k++){
                         tempk += p.mat[i][k] * l.mat[k][j];
                    }
                    m.mat[i][j] = tempk;
                    tempk = 0;
                }
            }

            for (int i = 0; i < 100; i++) {
                for (int j = 0; j < 784; j++) {
                    m.mat[i][j] = LR * m.mat[i][j];
                }
            }

            for (int i = 0; i < 100; i++) {
                for (int j = 0; j < 784; j++) {
                    wih.mat[i][j] = wih.mat[i][j] + m.mat[i][j];
                }
            }
            if(cou == 9999){
                FILE *file;
                file = fopen("w.csv", "w");
                for (int i = 0; i < 100; i++) {
                    for (int j = 0; j < 784; j++) {
                        fprintf(file, "%f,", wih.mat[i][j]);
                    }
                }
                fprintf(file,"\n");

                for (int i = 0; i < 10; i++) {
                    for (int j = 0; j < 100; j++) {
                        fprintf(file, "%f,", who.mat[i][j]);
                    }
                }
                fclose(file);
            }
            cou++;
            freeAll();
        }

        void freeAll(){
            hidden_inputs.free();
            hidden_outputs.free();
            final_inputs.free();
            final_outputs.free();
            hidden_errors.free();
            output_errors.free();
            whoT.free();
        }

        void train(matrix inputs, matrix targets){

            hidden_inputs = matrix_multiplication(wih, inputs);
            hidden_outputs = sigmoida(hidden_inputs);

            final_inputs = matrix_multiplication(who, hidden_outputs);
            final_outputs = sigmoida(final_inputs);

            output_errors = targets - final_outputs;
            whoT = who.transpose();
            hidden_errors = matrix_multiplication(whoT, output_errors);

            back(inputs, targets);
        }

        void init_w(){
            FILE* file;
            char* mass;
            char* pch;
            char buff[2500000];
            file = fopen("w.csv", "r");


            mass = fgets(buff, 2500000, file);
            for (int i = 0; i < 100; i++){
                for (int j = 0; j < 784; j++) {
                    if(i == 0 && j == 0){
                        pch = strtok(mass,",");
                        wih.mat[0][0] = atof(pch);
                        continue;
                    }
                    pch = strtok(NULL, ",");
                    wih.mat[i][j] = atof(pch);
                }
            }



            mass = fgets(buff, 30000, file);
            for (int i = 0; i < 10; i++){
                for (int j = 0; j < 100; j++) {
                    if(i == 0 && j == 0){
                        pch = strtok(mass,",");
                        who.mat[0][0] = atof(pch);
                        continue;
                    }
                    pch = strtok(NULL, ",");
                    who.mat[i][j] = atof(pch);
                }
            }



            fclose(file);
        }

        matrix quary(matrix inputs){

            hidden_inputs = matrix_multiplication(wih, inputs);
            hidden_outputs = sigmoida(hidden_inputs);

            final_inputs = matrix_multiplication(who, hidden_outputs);
            final_outputs = sigmoida(final_inputs);

            hidden_inputs.free();
            hidden_outputs.free();
            final_inputs.free();

            return final_outputs;
        }

    private:
        matrix hidden_inputs;
        matrix hidden_outputs;
        matrix final_inputs;
        matrix final_outputs;
        matrix whoT;

        matrix hidden_errors;
        matrix output_errors;

        int i_n;
        int o_n;
        int h_n;
        int lr;
        int cs;
        int cou = 0;

        matrix a;
        matrix b;
        matrix c ;
        matrix d ;
        matrix f ;

        matrix g ;
        matrix h ;
        matrix p ;
        matrix l ;
        matrix m ;



};

void train(NeuralNetwork ner){
    FILE* file;
    char *mass;
    char* pch;
    char buff[3000];

    matrix inputs(784, 1);
    matrix targets(10,1);
    int correct_label;

    for (size_t zen = 0; zen < 1; zen++) {
        file = fopen("mnist_train.csv", "r");
        int count = 0;
        while (count < 10000) {

            mass = fgets(buff, 3000, file);
            pch = strtok(mass,",");

            correct_label = atoi(pch);
            for (int i = 0; i < 10; i++) {
                targets.mat[i][0] = 0.01;
            }
            targets.mat[correct_label][0] = 0.99;

            for (int i = 0; i < 784; i++){
                pch = strtok(NULL, ",");
                inputs.mat[i][0] = (atoi(pch)/ 255.001 * 0.99) + 0.01;
            }
            cout << count << '\n';
            ner.train(inputs, targets);
            count++;
        }
    fclose(file);
    }
}

void quary(NeuralNetwork ner){
    FILE* file;
    char *mass;
    char* pch;
    char buff[3000];
    file = fopen("mnist_test.csv", "r");
    matrix inputs(784, 1);
    int count_label = 0;
    matrix final_outputs;
    float max;
    int label;
    int correct_label;
    ner.init_w();

    int count = 0;
    while (count < 10000) {


        mass = fgets(buff, 3000, file);
        pch = strtok(mass, ",");
        correct_label = atoi(pch);

        for (int i = 0; i < 784; i++){
            pch = strtok(NULL, ",");
            inputs.mat[i][0] = (atoi(pch)/ 255.001 * 0.99) + 0.01;
        }
        final_outputs = ner.quary(inputs);


        max = final_outputs.mat[0][0];
        label = 0;
        for (int i = 0; i < 10; i++) {
            if (max < final_outputs.mat[i][0]) {
                label = i;
                max = final_outputs.mat[i][0];
            }
        }

        if (label == correct_label) {
            count_label++;
        }

        std::cout << ner.wih.mat[99][784] << '\n';
        std::cout << ner.who.mat[9][99] << '\n';
        std::cout << '\n';
        cout << "истинный маркер - "<< correct_label << '\n';
        cout << "ответ сети - "<< label << '\n';
        count++;
    }

    fclose(file);
    std::cout << '\n'<< "эффективность - "<< (count_label/(count + 0.1)) * 100.1<< '%' << '\n';
}

void oTest(NeuralNetwork ner){
    FILE* file;
    char *mass;
    char* pch;
    char buff[3000];
    file = fopen("text.csv", "r");
    matrix inputs(784, 1);
    int count_label = 0;
    matrix final_outputs;
    float max;
    int label;
    int correct_label;

    ner.init_w();

    mass = fgets(buff, 3000, file);
    pch = strtok(mass,",");
    correct_label = atoi(pch);

    for (int i = 0; i < 784; i++){
        pch = strtok(NULL, ",");
        inputs.mat[i][0] = (atoi(pch)/ 255.001 * 0.99) + 0.01;
    }
    final_outputs = ner.quary(inputs);



    std::cout << '\n';
    cout << "истинный маркер - "<< correct_label << '\n';
    cout << "ответ сети - "<< label << '\n';

    fclose(file);
}

int main(int argc, char const *argv[]) {
    int input_nodes = 784;
    int hidden_nodes = SIZE;
    int output_nodes = 10;
    float learning_rate = LR;

    NeuralNetwork nn(input_nodes, hidden_nodes, output_nodes, learning_rate);

    int choise;
    while(1){
        cout << "1. train" << '\n' << "2. efficiency test" << '\n' << "3. test" << '\n' << "4. train + efficiency test" << '\n' << "5. exit" << '\n' << "Enter: ";
        cin >> choise;
        cout << '\n';

        switch (choise) {
            case 1:
                train(nn);
                continue;
            case 2:
                quary(nn);
                continue;
            case 3:
                oTest(nn);
                continue;
            case 4:
                train(nn);
                quary(nn);
                break;
            case 5:
                return 0;
        }
    }


    return 0;
}
