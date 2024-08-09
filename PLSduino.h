/*
  PLS.h - Library for flashing Morse code.
  Created by Jamal Makkor contact@makkor.de
  Released into the public domain.
*/
#ifndef PLS_h
#define PLS_h

#include "Arduino.h"
#include <ArduinoEigenDense.h>
using Eigen::MatrixXf;
using Eigen::VectorXf;

class PLS
{
	private:
		MatrixXf B, mean0X, mean0Y;
		inline void display(
			const char *name,
			const MatrixXf &value );

	public:
		PLS( );
		PLS(int brate );
		PLS( const MatrixXf &B, const MatrixXf &meanX, const MatrixXf &meanY );
		~PLS();

		void train(
			const MatrixXf &Xdata,
			const MatrixXf &Ydata,
			float epsilon = 0.0001 );
		MatrixXf predict(
			const MatrixXf &v ) const;

		MatrixXf pseudoMat(
				MatrixXf P);

};

#endif
