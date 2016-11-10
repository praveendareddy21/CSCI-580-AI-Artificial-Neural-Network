/*
 * main.cpp
 *
 *  Created on: Oct 2, 2016
 *      Author: Praveen
 */

#include<stdlib.h>
#include<iostream>
#include"ann.h"

using namespace std;

/**
Driver

takes argument input from command line

constructs ANN object
trains neural netork weight model
validates test

@param  command line argument
@return 0
*/
int main(int argc, char* argv[]){

  int iterations =0;
  Ann a(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
  iterations = atoi(argv[7]);
  a.trainWeightsModel(iterations);
  a.validateTestInput();
  //Ann a;
	return 0;
}
