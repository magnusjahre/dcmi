
#include <math.h>
#include "hls_stream.h"
#include <cmath>
#include <stdio.h>
#include <iostream>
#include "coefs.h"

using namespace std;

const int patternD = 2; // patternD = 2 means a 5 point pattern
const int patternSize = 2 * patternD + 1;
//const int inputSize = 60;
const int iterations = 40;

//double testInput[inputSize];
//double testOutput[inputSize];

//***********************************************************
//***********************************************************
//***********************************************************

const int partialInputSize = 20;
const int partialResultsSize = 2* patternD*iterations+partialInputSize; // some of this results are calculated and go out directly
//some of them stay to complete their calculation after new inputs fetched
const int noOfeffectedResults = 2 * patternD*iterations + 1;


void Stencil1D_RevCone101(double arrPartialIn[partialInputSize], double arrOut[partialInputSize])
{
#pragma HLS ARRAY_PARTITION variable=arrOut complete dim=1
#pragma HLS ARRAY_PARTITION variable=arrPartialIn complete dim=1
#pragma HLS PIPELINE II=20
	static double partialResults[partialResultsSize][2] = { 0 };
#pragma HLS RESOURCE variable=partialResults core=RAM_T2P_BRAM
#pragma HLS ARRAY_PARTITION variable=partialResults complete dim=0

	revCone1D_label1:for (int i = 0; i < partialInputSize; i++)
	{

		revCone1D_label0:for (int j = 0; j < noOfeffectedResults; j++)
		{
			partialResults[i + j][0] += arrPartialIn[i] * coefficients[j];
		}
	}

	for (int i = 0; i < partialInputSize; i++)
	{

		arrOut[i] = partialResults[i][0];

	}
	revCone1D_label2:for (int i = 0; i < partialResultsSize-partialInputSize; i++)
	{


		partialResults[i][0] = partialResults[i + partialInputSize][0];

	}
	Stencil1D_RevCone101_label0:for (int i = partialResultsSize - partialInputSize; i < partialResultsSize; i++)
	{


		partialResults[i][0] = 0;

	}
}
