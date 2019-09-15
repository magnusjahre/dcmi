//#pragma once

#include <math.h>
//#include "hls_stream.h"
#include <cmath>
#include <stdio.h>
#include <iostream>
#include "coefs2D.h"

using namespace std;

const int patternD = 1; // patternD = 2 means a 5 point pattern
const int patternSize = 2 * patternD + 1;
//const int inputSize = 60;
const int iterations = 6;

//double testInput[inputSize];
//double testOutput[inputSize];

//***********************************************************
//***********************************************************
//***********************************************************

const int partialInputSize = 4;

const int completedPartialResultsSize = 10;

#if partialInputSize-2*patternD*iterations > 0
const int directResultsSize = partialInputSize - 2 * patternD*iterations;
#else
const int directResultsSize = 0;
#endif
const int partialResultsRowSize = 2 * patternD*iterations + partialInputSize; // some of this results are calculated and go out directly
																			  //some of them stay to complete their calculation after new inputs fetched
const int partialResultsClmnSize = 2 * patternD*iterations + 1;

const int noOfeffectedResults = 2 * patternD*iterations + 1;



void test_revCone2D9P(double arrPartialIn[partialInputSize], double arrOut[partialInputSize])
{
#pragma HLS PIPELINE II=15
	static double partialResults[partialResultsRowSize][partialResultsClmnSize] = { 0 };
	//#pragma HLS RESOURCE variable=partialResults core=FAddSub_nodsp
	static bool firstTimeFlag = true;

revCone1D_label1:for (int i = 0; i < partialInputSize; i++)
{
revCone1D_label0:for (int j = 0; j < noOfeffectedResults; j++)
{
	for (int k = 0; k<noOfeffectedResults; k++)
		partialResults[i + j][k] += arrPartialIn[i] * coefficients2D[j][k];
}
}
				 for (int i = 0; i < partialInputSize; i++)
				 {

					 arrOut[i] = partialResults[i][noOfeffectedResults - 1];

				 }
				 /*
				 for (int k=0 ; k< noOfeffectedResults;k++)
				 {
				 revCone1D_label2:for (int i = 0; i < partialResultsRowSize-partialInputSize; i++)
				 {

				 partialResults[i][k][0] = partialResults[i + partialInputSize][k][0];

				 }
				 }
				 */
				 for (int i = partialResultsRowSize - partialInputSize; i < partialResultsRowSize; i++)
				 {

					 partialResults[i][noOfeffectedResults - 1] = 0;

				 }
}
