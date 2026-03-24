/*
This code was tested on ESP32 S3 Vroom which has an
embedded SD card already. Other boards may need a
different SD initialization step.
*/
#include "Arduino.h"
#include "FS.h"
#include "SD_MMC.h"
#include <ArduinoEigenDense.h>
#include <PLSduino.h>
#include <PLSduinoIO.h>

#define SD_MMC_CMD 38  // Please do not modify it.
#define SD_MMC_CLK 39  // Please do not modify it.
#define SD_MMC_D0 40   // Please do not modify it.

int baudrate = 115200;
PLS pls(baudrate);

bool readMatrix(fs::FS &fs, const char *path, MatrixXf &matrix);
bool readModel(fs::FS &fs, const char *bPath, const char *meanXPath, const char *meanYPath);
void printMatrix(const MatrixXf& mat);

void setup() {
  Serial.begin(baudrate);

  SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD, SD_MMC_D0);
  int mounted = SD_MMC.begin("/sdcard", true, true, SDMMC_FREQ_DEFAULT, 5);
  if (!mounted) {
    Serial.printf("Card mount failed: %d\r\n", mounted);
    return;
  }

  if (!readModel(SD_MMC, "/B.csv", "/meanX.csv", "/meanY.csv")) {
    return;
  }

  MatrixXf X;
  if (!readMatrix(SD_MMC, "/predictX.csv", X)) {
    return;
  }

  MatrixXf prediction = pls.predict(X);
  if (prediction.size() == 0) {
    return;
  }

  Serial.println("Prediction input X");
  printMatrix(X);
  Serial.println("Predicted Y");
  printMatrix(prediction);
}

void loop() {
}

bool readMatrix(fs::FS &fs, const char *path, MatrixXf &matrix) {
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return false;
  }

  bool ok = PLSIO::loadMatrixFromCSV(file, matrix);
  file.close();
  return ok;
}

bool readModel(fs::FS &fs, const char *bPath, const char *meanXPath, const char *meanYPath) {
  Serial.println("Loading pretrained model");

  File bFile = fs.open(bPath);
  if (!bFile) {
    Serial.println("Failed to open B matrix file");
    return false;
  }

  File meanXFile = fs.open(meanXPath);
  if (!meanXFile) {
    Serial.println("Failed to open meanX file");
    bFile.close();
    return false;
  }

  File meanYFile = fs.open(meanYPath);
  if (!meanYFile) {
    Serial.println("Failed to open meanY file");
    bFile.close();
    meanXFile.close();
    return false;
  }

  bool ok = PLSIO::loadModelFromCSV(bFile, meanXFile, meanYFile, pls);
  bFile.close();
  meanXFile.close();
  meanYFile.close();
  return ok;
}

void printMatrix(const MatrixXf& mat) {
  for (int i = 0; i < mat.rows(); ++i) {
    for (int j = 0; j < mat.cols(); ++j) {
      Serial.print(mat(i, j), 6);
      Serial.print("\t");
    }
    Serial.println();
  }
}
