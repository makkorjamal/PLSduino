/*
  PLSduinoIO.h - CSV loading helpers for PLSduino.
*/
#ifndef PLSduinoIO_h
#define PLSduinoIO_h

#include "Arduino.h"
#include <ArduinoEigenDense.h>
#include "PLSduino.h"

using Eigen::MatrixXf;

namespace PLSIO
{
	bool loadMatrixFromCSV(
		Stream &stream,
		MatrixXf &matrix );

	bool loadModelFromCSV(
		Stream &bStream,
		Stream &meanXStream,
		Stream &meanYStream,
		PLS &pls );
}

#endif
