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
constructs robot object
print the result for each sensor input in a loop


@param  command line argument
@return 0
*/
int main(int argc, char* argv[]){

  Ann a(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
  a.trainWeightsModel();
  a.validateTestInput();
  //Ann a;
	return 0;
}
