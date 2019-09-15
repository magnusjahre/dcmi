// Win32Project1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
    return 0;
}

//#pragma once

#include <math.h>
//#include "hls_stream.h"
#include <cmath>
#include <stdio.h>
#include <iostream>

using namespace std;

const int patternD = 1; // patternD = 2 means a 5 point pattern
const int patternSize = 2 * patternD + 1;
const int inputSize = 22;
const int iterations = 10;
/*double testInput[inputSize];
double testOutput[inputSize];
*/
const double pattern[patternSize][patternSize] = { { 0.2351,0.32412,.7823 },
{ 0.4451,0.36612,.89723 }
,{ 0.1126351,0.7021312,.0602723 } };

void stencil2D9P(double arrIn[inputSize][inputSize], double arrOut[inputSize][inputSize])//, int iterations)
{
#pragma HLS PIPELINE II=30
	double arrTmp1[inputSize][inputSize];
	double arrTmp2[inputSize][inputSize];
	double sumTmp = 0;
	double tmp2;
	for (int i = 0; i < inputSize; i++)
		for (int j = 0; j<inputSize; j++)
		{
			arrTmp1[i][j] = arrIn[i][j];
			arrTmp2[i][j] = 0;
		}
	for (int itr = 1; itr <= iterations; itr++)

	{
		for (int i = 0 + patternD * itr; i < inputSize - patternD*itr; i++)
		{
		stencil1D_label2:for (int j = 0 + patternD*itr; j < inputSize - patternD*itr; j++)
		{
			sumTmp = 0;

		stencil1D_label1:for (int p = -patternD; p <= patternD; p++)
		{
			for (int q = -patternD; q <= patternD; q++)
			{
				tmp2 = arrTmp1[i + p][j + q] * pattern[p + patternD][q + patternD];
				sumTmp = sumTmp + tmp2;
			}
		}

						 arrTmp2[i][j] = sumTmp;
		}

		}
		for (int i = 0; i< inputSize; i++)
			for (int j = 0; j < inputSize; j++)
				arrTmp1[i][j] = arrTmp2[i][j];// assign temp2 to temp1 to start next iteration


	}
	for (int i = 0; i< inputSize; i++)
		for (int j = 0; j < inputSize; j++)
			arrOut[i][j] = arrTmp2[i][j];// assign elements of the output
}

//***********************************************************
//***********************************************************
//***********************************************************
