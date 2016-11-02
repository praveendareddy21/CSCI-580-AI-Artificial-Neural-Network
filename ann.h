/*
 * ann.h
 *
 *  Created on: Oct 19, 2016
 *      Author: Praveen
 */

#ifndef ANN_H_
#define ANN_H_

#include<vector>
#include"matrix.h"
class Ann{
private:
	std::vector<int> structure;
	std::vector< std::vector<long double> > weightTable;
	std::vector<std::vector<long double> > output;
	std::vector<std::vector<long double> >error;
	std::vector<std::vector< int> > node;
	long double alpha;

	long double getEuclideanDistance(long double x1, long double y1, long double x2, long double y2);
	long double getEuclideanDistance(std::vector<long double> X, std::vector<long double> Y);
	void initweightTable();
	void initOutput();
	void initError();
	void initNode();
	long double getSigmoid(long double in);
	void updateWeights();
	void updateValuesInForwardPass();
	void updateErrorsInBackwardPass();
	void doForwardPassIteration();
	void doBackwardPassIteration();


public:
	Ann();
	void calculateValueAt(int layer, int nodeNum);
	void calculateErrorAt(int layer, int nodeNum);
	void calculateErrorAtOutputLayer(int layer, int nodeNum, long double output);



	void showOutput();
	void showError();
	void showNode();

};

#endif /* ANN_H_ */
