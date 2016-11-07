/*
 * ann.h
 *
 *  Created on: Oct 19, 2016
 *      Author: Praveen
 */

#ifndef ANN_H_
#define ANN_H_

#include<vector>
#include<iostream>

class Matrix{
private:
	std::vector<std::vector<long double> > _matrix;
public:
	Matrix(std::vector<std::vector<long double> > m);
	Matrix(int,int);
	Matrix();
	long double get(int row, int col);
	void set(int row, int col, long double value);
	Matrix multiply(Matrix& m2);
};




class Ann{
private:
	std::vector<int> structure;
	std::vector< std::vector<long double> > weightTable;
	std::vector<std::vector<long double> > output;
	std::vector<std::vector<long double> >error;
	std::vector<std::vector< int> > node;

	std::vector< std::vector<long double> > train_inputTable;
	std::vector< std::vector<long double> > test_inputTable;

	std::vector< int> train_output;
	std::vector< int> test_output;

	long double alpha;
	std::vector<std::vector<long double> > digit_encoding;

	long double getEuclideanDistance(long double x1, long double y1, long double x2, long double y2);
	long double getEuclideanDistance(std::vector<long double> X, std::vector<long double> Y);
	long double getSigmoid(long double in);

	void initStructure(char *);
	void initweightTable(char *);
	void initOutput();
	void initError();
	void initNode();
	void initDigitEncoding();
	void initTrainInput(char *);
	void initTrainOutput(char *);
	void initTestInput(char *);
	void initTestOutput(char *);


	void calculateValueAt(int layer, int nodeNum);
	void calculateErrorAt(int layer, int nodeNum);
	void calculateErrorAtOutputLayer(int layer, int nodeNum, long double output);
	void updateValuesInForwardPass();
	void updateErrorsInBackwardPass();
	void doForwardPassIteration(std::vector< std::vector<long double> > ,int);
	void doBackwardPassIteration(std::vector< int> , int);
	void updateWeights();
	int findDigit();


public:
	Ann();
	Ann( char *, char *, char *, char *, char *, char *);

	void trainWeightsModel();
	void validateTestInput();

	void showOutput();
	void showError();
	void showNode();
	void showWeight();

};

#endif /* ANN_H_ */
