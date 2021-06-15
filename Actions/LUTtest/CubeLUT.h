#pragma once
#ifndef CubeLUT_H
#define CubeLUT_H

#include <string>
#include <vector>
#include <fstream>

// Credit of this parser code: Adobe Inc.
// Cube LUT Specification 1.0
// https://wwwimages2.adobe.com/content/dam/acom/en/products/speedgrade/cc/pdfs/cube-lut-specification-1.0.pdf

class CubeLUT {
public:
	typedef std::vector<float> tableRow;
	typedef std::vector<tableRow> table1D;
	typedef std::vector<table1D> table2D;
	typedef std::vector<table2D> table3D;

	enum LUTState { OK = 0, NotInitialized = 1, ReadError = 10, WriteError, PrematureEndOfFile, LineError, UnknownOrRepeatedKeyword = 20, TitleMissingQuote, DomainBoundsReversed, LUTSizeOutOfRange, CouldNotParseTableData };
	LUTState status;
	std::string title;
	tableRow domainMin;
	tableRow domainMax;
	table1D LUT1D;
	table3D LUT3D;

	CubeLUT(void)
	{
		status = NotInitialized;
	}

	LUTState LoadCubeFile(std::ifstream& infile);

private:
	std::string ReadLine(std::ifstream& infile, char lineSeparator);
	tableRow ParseTableRow(const std::string& lineOfText);
};

#endif