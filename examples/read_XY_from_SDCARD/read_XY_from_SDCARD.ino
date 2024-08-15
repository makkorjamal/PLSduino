#include "Arduino.h"
#include "FS.h"
#include "SD_MMC.h"
#include <ArduinoEigenDense.h>
#include <PLSduino.h>

#define SD_MMC_CMD 38  //Please do not modify it.
#define SD_MMC_CLK 39  //Please do not modify it.
#define SD_MMC_D0 40   //Please do not modify it.
void printMatrix(const Eigen::MatrixXd& mat) ;
Eigen::MatrixXd readFromFile(fs::FS &fs, const char * path);
Eigen::MatrixXd result;
int baudrate = 115200;
PLS pls(baudrate);
void setup() {
  Serial.begin(115200);

  SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD, SD_MMC_D0);
  int error = SD_MMC.begin("/sdcard", true, true, SDMMC_FREQ_DEFAULT, 5);
  if (!error) {
    Serial.printf("Card Mount Failed: %d\r\n", error);
    return;
  }
  Serial.println("Card Mount Success.");
  Eigen::MatrixXd X = readFromFile(SD_MMC, "/toyX.csv");
  Eigen::MatrixXd Y = readFromFile(SD_MMC, "/toyY.csv");
  // Check if matrices are initialized
  if(X.rows() != Y.rows()) {
      Serial.println("One of the matrices is uninitialized!");
  }
  printMatrix(X);
  printMatrix(Y);
  pls.train(X, Y);



}

void loop() {
}
Eigen::MatrixXd readFromFile(fs::FS &fs, const char * path) {
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if (!file) {
        Serial.println("Failed to open file for reading");
        return Eigen::MatrixXd(); // Return an empty matrix
    }

    int ccount = 0;
    int rcount = 0;

    // First pass: Count rows and columns
    while (file.available()) {
        String sval = file.readStringUntil('\n');
        if (sval.length() > 0) {
            rcount++;
            ccount += countCommas(sval) + 1; // Count columns based on commas
        }
    }
    file.close(); // Close the file after counting

    if (rcount == 0) {
        Serial.println("No data found in file");
        return Eigen::MatrixXd(); // Return an empty matrix
    }

    int nrows = rcount;
    int ncols = ccount / rcount;

    Eigen::MatrixXd X(nrows, ncols);
    file = fs.open(path); // Reopen the file for reading data

    int i = 0;
    while (file.available()) {
        String sval = file.readStringUntil('\n');
        int j = 0;
        String value;
        for (int k = 0; k < sval.length(); k++) {
            if (sval.charAt(k) == ',') {
                X(i, j) = value.toDouble();
                value = ""; // Reset value for next column
                j++;
            } else {
                value += sval.charAt(k); // Accumulate characters for the current value
            }
        }
        // Add the last value after the loop
        if (value.length() > 0) {
            X(i, j) = value.toFloat();
        }
        i++;
    }
    file.close(); // Close the file after reading

    return X;
}

int countCommas(const String& sval) {
    int count = 0;
    for (char c : sval) {
        if (c == ',') {
            count++;
        }
    }
    return count;
}

void printMatrix(const Eigen::MatrixXd& mat) {
    for (int i = 0; i < mat.rows(); ++i) {
        for (int j = 0; j < mat.cols(); ++j) {
            Serial.print(mat(i, j), 3);
            Serial.print("\t");
        }
        Serial.println();
    }
}
