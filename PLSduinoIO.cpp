/*
  PLSduinoIO.cpp - CSV loading helpers for PLSduino.
*/

#include "PLSduinoIO.h"
#include <stdlib.h>

namespace
{
	bool parseLine(
		const String &rawLine,
		int expectedColumns,
		MatrixXf &row )
	{
		String line = rawLine;
		line.trim();
		if (line.length() == 0) {
			return false;
		}

		int columnCount = 1;
		for (int i = 0; i < line.length(); ++i) {
			if (line.charAt(i) == ',') {
				columnCount++;
			}
		}

		if (expectedColumns > 0 && columnCount != expectedColumns) {
			Serial.println("CSV parse error: inconsistent column count");
			return false;
		}

		row.resize(1, columnCount);
		int start = 0;
		for (int col = 0; col < columnCount; ++col) {
			int end = line.indexOf(',', start);
			if (end < 0) {
				end = line.length();
			}

			String token = line.substring(start, end);
			token.trim();
			if (token.length() == 0) {
				Serial.println("CSV parse error: empty value");
				return false;
			}

			const char *buffer = token.c_str();
			char *endPtr = NULL;
			float value = strtof(buffer, &endPtr);
			if (endPtr == buffer || *endPtr != '\0') {
				Serial.print("CSV parse error: invalid float '");
				Serial.print(token);
				Serial.println("'");
				return false;
			}

			row(0, col) = value;
			start = end + 1;
		}

		return true;
	}
}

bool PLSIO::loadMatrixFromCSV(
	Stream &stream,
	MatrixXf &matrix )
{
	matrix.resize(0, 0);
	int rowCount = 0;
	int expectedColumns = -1;

	while (stream.available()) {
		String line = stream.readStringUntil('\n');
		String trimmed = line;
		trimmed.trim();
		if (trimmed.length() == 0) {
			continue;
		}

		MatrixXf row;
		if (!parseLine(trimmed, expectedColumns, row)) {
			matrix.resize(0, 0);
			return false;
		}

		if (expectedColumns < 0) {
			expectedColumns = row.cols();
			matrix = row;
			rowCount = 1;
			continue;
		}

		matrix.conservativeResize(rowCount + 1, expectedColumns);
		matrix.row(rowCount) = row;
		rowCount++;
	}

	if (rowCount == 0) {
		Serial.println("CSV parse error: no data found");
		return false;
	}

	return true;
}

bool PLSIO::loadModelFromCSV(
	Stream &bStream,
	Stream &meanXStream,
	Stream &meanYStream,
	PLS &pls )
{
	MatrixXf B;
	MatrixXf meanX;
	MatrixXf meanY;

	if (!loadMatrixFromCSV(bStream, B)) {
		Serial.println("Failed to load B matrix");
		return false;
	}

	if (!loadMatrixFromCSV(meanXStream, meanX)) {
		Serial.println("Failed to load meanX matrix");
		return false;
	}

	if (!loadMatrixFromCSV(meanYStream, meanY)) {
		Serial.println("Failed to load meanY matrix");
		return false;
	}

	return pls.setModel(B, meanX, meanY);
}
