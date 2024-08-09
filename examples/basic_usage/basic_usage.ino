#include <ArduinoEigenDense.h>
#include <PLSduino.h>

Eigen::MatrixXf X(5, 3);
Eigen::MatrixXf Y(5, 1);
Eigen::MatrixXf result;
int baudrate = 115200;
PLS pls(baudrate);
void printMatrix(const MatrixXf& mat);

void setup()
{
    Serial.begin(baudrate); // Initialize serial communication for debugging
    X << 1.0, 2.0, 3.0,
         4.0, 5.0, 6.0,
         7.0, 8.0, 9.0,
         10.0, 11.0, 12.0,
         13.0, 14.0, 15.0;

    // generate a matrix that Y that have linear dependence on X
    for (int i = 0; i < 5; ++i) {
        Y(i, 0) = 2.0 * X(i, 0) + 3.0 * X(i, 1) - 1.0 * X(i, 2) 
                + (static_cast<float>(random(0, 100)) / 100.0 - 0.5); // random noise

    }
    Serial.println("Hello there");

    pls.train(X, Y);
    Serial.println("original Y");
    printMatrix(Y);
}
void loop()
{
  result = pls.predict(X);
  Serial.println("Predicted Y");
  printMatrix(result);
  sleep(2000);

}

void printMatrix(const MatrixXf& mat) {
    for (int i = 0; i < mat.rows(); ++i) {
        for (int j = 0; j < mat.cols(); ++j) {
            Serial.print(mat(i, j));
            Serial.print("\t");
        }
        Serial.println();
    }
}
