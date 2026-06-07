# Partial Least Squares for Arduino/ESP32

## Introduction

Partial Least Squares (PLS) is a statistical technique used to model relationships between groups of variables. It is especially useful when predictor variables are highly correlated or when there are more predictors than observations. PLS is widely used in fields such as chemistry, social sciences, and bioinformatics.

## Usage

Download all source files and install the library in your Arduino environment.

### Examples

examples/basic_usage/basic_usage.ino
  Demonstrates basic usage of the library with predefined matrices.

examples/read_XY_from_SD_card/read_from_XY_from_SD.ino
  Demonstrates how to read the feature matrix (X) and response matrix (Y) from files stored on an SD card.

## Installation

1. Install the Arduino Eigen/Dense library.
2. Download or clone this repository.
3. Copy the library into your Arduino libraries folder.
4. Restart the Arduino IDE.

## Notice

1. This library depends on the Arduino Eigen/Dense library.
2. Arduino and ESP32 devices have limited computational resources. You can load a pre-trained matrix **B** and use it to predict **Y**, provided that the dimensionality remains consistent.

## Reference

Refer to the /doc directory for additional details (to be completed).

---

## Contributing

Contributions are welcome. To contribute:

1. Fork the repository.
2. Make your changes.
3. Commit your modifications.
4. Submit a pull request.

Adding a changelog and your contact information in the file header is encouraged.

Thank you for your contribution!


