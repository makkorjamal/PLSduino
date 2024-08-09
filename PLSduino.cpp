/*
  PLS.cpp - Library for Partial least squares
  created by Jamal Makkor public@makkor.de
  Released into the public domain.
*/

#include "Arduino.h"
#include "PLSduino.h"
#include <ArduinoEigenDense.h>

using Eigen::MatrixXf;
using Eigen::VectorXf;

PLS::PLS( )
{
  Serial.begin(9600); // Initialize serial communication	
}

PLS::PLS(int brate)
{
	Serial.begin(brate); // Initialize serial communication
}

PLS::PLS(
	const MatrixXf &B,
	const MatrixXf &meanX,
	const MatrixXf &meanY ) : B(B), mean0X(meanX), mean0Y(meanY)
{
	// nothing to do
}

PLS::~PLS()
{
	//Default destructor
}
void PLS::train(
	const MatrixXf &Xdata,
	const MatrixXf &Ydata,
	float epsilon )
{
	if (Xdata.rows() != Ydata.rows()){

		Serial.println("X and Y dimentionality does not match");
		return;
	}

	MatrixXf X, Y;
	X = Xdata;
	mean0X = X.colwise().mean();
	Y = Ydata;
	mean0Y = Y.colwise().mean();

	for (int i = 0; i < X.rows(); ++i)
		X.row(i) = X.row(i) - mean0X;

	for (int i = 0; i < Y.rows(); ++i)
		Y.row(i) = Y.row(i) - mean0Y;

        MatrixXf T, U, W, C, P, Q, Bdiag;
        VectorXf t, w, u_old,e, c, p, q, b;
	VectorXf u = VectorXf::Random(X.rows());
	while (1)
	{
		while (1)
		{
			//maximizing infomation content in from X and Y
			w = X.transpose() * u;
			w = w / w.norm();
			t = X * w; // latent vector in X
			t = t / t.norm();
			c = Y.transpose() * t;
			c = c / c.norm();
			u_old = u;
			u = Y * c; // latent vector in Y
			e = u- u_old; // try to minimise the error
			float error = e.norm();
			if (error < epsilon) break;
		}
		b = t.transpose() * u;
		assert(b.cols() == 1 && b.rows() == 1);
		if (C.cols() == 0)
			C = c;
		else
			C.conservativeResize(C.rows(), C.cols() + 1);
			C.col(C.cols() - 1) = c;

		float temp = t.norm();
		p = X.transpose() * t / (temp * temp);
		if (P.cols() == 0)
			P = p;
		else
			P.conservativeResize(P.rows(), P.cols() + 1);
			P.col(P.cols() - 1) = p;
		if (Bdiag.cols() == 0)
			Bdiag = b;
		else
			Bdiag.conservativeResize(Bdiag.rows(), Bdiag.cols() + 1);
			Bdiag.col(Bdiag.cols() - 1) = b;

		X = X - t * p.transpose();
		Y = Y - t * c.transpose();
		if (X.norm() < 0.001) break;
	}
	Bdiag = Bdiag.diagonal();
	MatrixXf P_t = P.transpose();
	B = Eigen::pseudoInverse(P_t); 
	B = B * Bdiag;
	B = B * C.transpose();
}

MatrixXf PLS::predict(
	const MatrixXf &v ) const
{
	MatrixXf temp;
	MatrixXf result = MatrixXf::Zero(v.rows(),B.cols());
	temp = v;

	for (int i = 0; i < temp.rows(); ++i)
	{
		temp.row(i) -= mean0X;
		result.row(i) = temp.row(i) * B;
		result.row(i) += mean0Y;
	}

	return result;
}
