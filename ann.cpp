/*
 * ann.cpp
 *
 *  Created on: Oct 19, 2016
 *      Author: Praveen
 */
#include"ann.h"
#include<iostream>
#include<math.h>
#include<iomanip>
#include<stdlib.h>
#include<fstream>
using namespace std;

/**
Matrix Default Constructor

*/
Matrix::Matrix(){

}
/**
Matrix Constructor


@param  std::vector<std::vector<long double> > m  2-d vector which stores matrix elements
@return Matrix matrix with 2-d vector as input
*/
Matrix::Matrix(std::vector<std::vector<long double> > m){
	_matrix=m;
}

/**
Constructor of Matrix
sets rows and cols , fills all elements as 0

@param  int rows rows to be set in matrix
@param  int cols columns to be set in matrix.
@return Matrix matrix of size row x cols
*/
Matrix::Matrix(int rows, int cols){
	std::vector<std::vector<long double> > m(rows, std::vector<long double>(cols,0));
	_matrix=m;
}


/**
Function for performing matrix multiplication

Multiplication n X n with n X 1 gives n X 1 matrix.

@param  Matrix & m1 matrix with which this matrix is multiplied with
@return Matrix matrix product of this matrix with matrix m1
*/
Matrix Matrix::multiply(Matrix & m1){
	std::vector<std::vector<long double> > A=_matrix;
	std::vector<std::vector<long double> >B=m1._matrix;
	std::vector<std::vector<long double> > C(B.size());

	if (A[0].size() != B.size())
	{
		std::cout<<"Size mismatch"<<std::endl;
		return C;
	}
	int col_no=0, out_row=0;
	long double row_sum=0.0;
	std::vector< std::vector <long double> >:: iterator it;
	std::vector <long double> :: iterator it_inner;

	for(it=A.begin();it!=A.end();it++){
		col_no=0;
		row_sum=0.0;
		for(it_inner=(*it).begin();it_inner!=(*it).end();it_inner++,col_no++){
			//std::cout<<"value " << (*it_inner) <<" "<<col_no <<" "<< B[col_no][0]<<std::endl;
			row_sum=row_sum+(*it_inner)*B[col_no][0];

		}
		C[out_row] = std::vector<long double>(1,row_sum);
		out_row++;

	}

	Matrix out(C);
	return out;
}

/**
Getter
Function for getting matrix element at given row and column

@param  int  row at which matrix element is required.
@param  int  col at which matrix element is required.
@return long double Matrix element
*/
long double Matrix::get(int row, int col){
	return _matrix[row][col];
}
/**
Setter
Function for setting matrix element at given rwo and column

@param  int  row at which matrix element is set.
@param  int  col at which matrix element is set.
@param  long double  matrix element to be set.
@return void
*/
void Matrix::set(int row, int col,long double value){
	_matrix[row][col]=value;
}

long double Ann::getEuclideanDistance(vector<long double> X, vector<long double> Y)
{
	long double X_test, Y_test;
	long double squareddist = 0.0;
	long double result=0.0;
	for(unsigned i=0; i<X.size();i++){
		X_test = X[i];
		Y_test = Y[i];
		squareddist += pow(X[i] - Y[i], 2);
	}
	result = sqrt(squareddist);
	return result;
}

int Ann::findDigit(){
	long double minDistance = -1;
	int minDigit = -1;
	long double tempDistance = 0.0;
	std::vector<long double> X;
	std::vector<long double> Y;


	for(int i=0; i < structure[structure.size() -1]; i++){
		X.push_back(output[structure.size() -1][i]);
	}
	for(int i=0; i < structure[structure.size() -1]; i++){
		Y.clear();
		for(int j=0; j < structure[structure.size() -1]; j++){
			Y.push_back(digit_encoding[i][j]);
		}
		tempDistance = getEuclideanDistance(X, Y);
		if(minDistance == -1){
			minDistance = tempDistance;
			minDigit = i;
		}
		else if(tempDistance < minDistance){
			minDistance = tempDistance;
			minDigit = i;
		}
	}

	return minDigit;
}

long double Ann::getSigmoid(long double in){
	long double exp_value;
	long double return_value;
	exp_value = exp(-in);
	return_value = 1 / (1 + exp_value);
	 return return_value;
}

void Ann::initStructure(char * filename){
	fstream inFile;   // input file
	int z;

	inFile.open(filename);
	if (!inFile)
	{
	   cout << "The input file could not be opened."<<endl;
	}

	while(true){
		inFile>>z;
		if(inFile.eof())
			break;
		structure.push_back(z);
		}
	inFile.close();
}

void Ann::initTrainInput(char * filename){

	vector<long double> temp;
	fstream inFile;   // input file
	long double z;

	inFile.open(filename);
	if (!inFile)
	{
	   cout << "The input file could not be opened."<<endl;
	}

	while(true){
		if(inFile.peek() == EOF){
			break;
		}
	    //while (inFile.peek() != '\n')
	    for(int k=0; k<structure[0]; k++)
		{
			inFile>>z;
			temp.push_back(z);
	    }
		if(inFile.peek() == EOF){
			break;
		}
	    train_inputTable.push_back(temp);
	    temp.clear();

		}
	inFile.close();


}

void Ann::initTrainOutput(char * filename){
	fstream inFile;   // input file
	int z;

	inFile.open(filename);
	if (!inFile)
	{
	   cout << "The input file could not be opened."<<endl;
	}

	while(true){
		inFile>>z;
		if(inFile.eof())
			break;
		train_output.push_back(z);
		}

inFile.close();

}

void Ann::initTestInput(char * filename){
	vector<long double> temp;
	fstream inFile;   // input file
	long double z;

	inFile.open(filename);
	if (!inFile)
	{
	   cout << "The input file could not be opened."<<endl;
	}

	while(true){
		if(inFile.peek() == EOF){
			break;
		}
	    for(int k=0; k<structure[0]; k++)
		{
			inFile>>z;
			temp.push_back(z);
	    }
		if(inFile.peek() == EOF){
			break;
		}
	    test_inputTable.push_back(temp);
	    temp.clear();


		}
inFile.close();


}

void Ann::initTestOutput(char * filename){
	fstream inFile;   // input file
	int z;

	inFile.open(filename);
	if (!inFile)
	{
	   cout << "The input file could not be opened."<<endl;
	}

	while(true){
		inFile>>z;
		if(inFile.eof())
			break;
		test_output.push_back(z);
		}

inFile.close();

}

void Ann::initweightTable(char * filename){

	int nodes = 1;
	fstream inFile;   // input file
	long double z;
	for(unsigned i=0;i<structure.size();i++){
		nodes += structure[i];
	}
	weightTable = vector<vector<long double> > (nodes, vector<long double>(nodes, 0) );

	inFile.open(filename);
	if (!inFile)
	{
	   cout << "The input file could not be opened."<<endl;
	}

	for(int j=0; j<structure.size()-1;j++){
		for(int i=0;i<structure[j];i++){
			for(int k=0; k< structure[j+1]; k++){
				inFile>>z;
				weightTable[node[j][i]][node[j+1][k]] = z;
				//cout<<"setting  ["<<node[j][i]<<"]["<<node[j+1][k]<<"] as : "<<z<<endl;//weightTable[node[j][i]][node[j+1][k]]<<endl;
			}
		}
	}
 inFile.close();

	for(int j=1; j<structure.size();j++){
		for(int i=0;i<structure[j];i++){
			//cout<<"initializing weightTable ["<<0<<"]["<<node[j][i]<<"] as : "<<0.01<<endl;
			weightTable[0][node[j][i]] = 0.01;  // weights from dummy to all nodes is 0.01
		}
	}
}

void Ann::initOutput(){
	std::vector<std::vector<long double> > out;
	std::vector <int > :: iterator struct_iter;

	for(struct_iter=structure.begin();struct_iter!=structure.end();struct_iter++){
		out.push_back(vector<long double>(*(struct_iter), 0));
	}
	output = out;
}

void Ann::initDigitEncoding(){

	std::vector<std::vector<long double> > out(10, std::vector<long double>(10, 0.9));
	std::vector <int > :: iterator struct_iter;

	for(int i=0;i<10;i++){
		out[i][i] = 0.1;
	}
	digit_encoding = out;

}

void Ann::initError(){

	std::vector<std::vector<long double> > out;
	std::vector <int > :: iterator struct_iter;

	for(struct_iter=structure.begin();struct_iter!=structure.end();struct_iter++){
		out.push_back(vector<long double>(*(struct_iter), 0));
	}
	error = out;
}

void Ann::initNode(){

	std::vector<std::vector< int> > out;
	std::vector <int > :: iterator struct_iter;
	int nodenum=1;
	for(struct_iter=structure.begin();struct_iter!=structure.end();struct_iter++){
		vector<int> temp;
		for(int i=0;i<*(struct_iter);i++){
			temp.push_back(nodenum);
			nodenum++;
		}
		out.push_back(temp);
	}
	node = out;
}

void Ann::calculateValueAt(int layer, int nodeNum){

	Matrix matOut(1, output[layer-1].size()+1  );
	Matrix matWeight(output[layer-1].size()+1 , 1);
	int input_node = 0;

	matOut.set(0,0,1); //setting a0 as 1
	matWeight.set(0,0, weightTable[0][node[layer][nodeNum]]); //setting w0

	for(int i=0;i < output[layer-1].size();i++ ){
		matOut.set(0,i+1, output[layer-1][i]);
		input_node = node[layer-1][i];
		//cout<<" node : "<<input_node<<endl;
		matWeight.set(i+1,0, weightTable[input_node][node[layer][nodeNum]]); //setting w0
	}
	//matOut.show();
	//matWeight.show();

	Matrix matO1 = matOut.multiply(matWeight);
	//matO1.show();

	output[layer][nodeNum] = getSigmoid(matO1.get(0,0));
	//cout<<" setting output "<<layer<<" "<<nodeNum<<" : "<<endl;
	//cout << showpoint << fixed << setprecision(12) << output[layer][nodeNum] << endl;
}

void Ann::calculateErrorAt(int layer, int nodeNum){

	Matrix matError(1, output[layer+1].size() );
	Matrix matWeight(output[layer+1].size(), 1);

	int input_node = 0;
	long double calculatedValue = output[layer][nodeNum];


	for(int i=0;i < output[layer+1].size();i++ ){
		matError.set(0,i, error[layer+1][i]);
		input_node = node[layer][nodeNum];
		//cout<<" node : "<<input_node<<" to : "<<node[layer+1][i]<<endl;
		matWeight.set(i,0, weightTable[input_node][node[layer+1][i]]); //setting w0
	}
	//matError.show();
	//matWeight.show();
	Matrix matO1 = matError.multiply(matWeight);
	//matO1.show();

	error[layer][nodeNum] = calculatedValue * (1-calculatedValue) * matO1.get(0,0);

	//cout<<" setting error "<<layer<<" "<<nodeNum<<" with a value as "<< calculatedValue<< " : ";
	//cout << showpoint << fixed << setprecision(12) << error[layer][nodeNum] << endl;

}

void Ann::calculateErrorAtOutputLayer(int layer, int nodeNum, long double outputLayerValue){

	long double calculatedValue = output[layer][nodeNum];
	error[layer][nodeNum] =  calculatedValue * (1-calculatedValue) * (outputLayerValue - calculatedValue );
}

void Ann::updateErrorsInBackwardPass(){

	for(int j=structure.size()-2; j>=0;j--){
		for(int i=0;i<structure[j];i++){
			//cout<<"invoking updateError for "<<node[j][i]<<endl;
			calculateErrorAt(j,i);
		}
	}
}

void Ann::updateValuesInForwardPass(){

	for(int j=1; j<structure.size();j++){
		for(int i=0;i<structure[j];i++){
			//cout<<"invoking updateValue for "<<node[j][i]<<endl;
			calculateValueAt(j,i);
		}
	}
}

void Ann::updateWeights(){

	for(int j=1; j<structure.size();j++){
		vector<int> temp;
		for(int i=0;i<structure[j];i++){

			//cout<<"current node : "<<node[j][i]<<endl;
			weightTable[0][node[j][i]] =  weightTable[0][node[j][i]] + alpha * 1 * error[j][i] ;
			//cout<<"setting  ["<<0<<"]["<<node[j][i]<<"] as : "<<weightTable[0][node[j][i]]<<endl;
		}
	}

	for(int j=0; j<structure.size()-1;j++){
		vector<int> temp;
		for(int i=0;i<structure[j];i++){

			for(int k=0; k< structure[j+1]; k++){

				weightTable[node[j][i]][node[j+1][k]] =  weightTable[node[j][i]][node[j+1][k]] + alpha * output[j][i] * error[j+1][k] ;

				//cout<<"setting  ["<<node[j][i]<<"]["<<node[j+1][k]<<"] as : "<<weightTable[node[j][i]][node[j+1][k]]<<endl;
			}
		}
	}

}

void Ann::doForwardPassIteration(std::vector< std::vector<long double> > inputlayer, int number){

	for(int j=0; j<structure[0];j++){
		output[0][j] = inputlayer[number][j];
	}
	updateValuesInForwardPass();

}

void Ann::doBackwardPassIteration(std::vector< int> outputlayer,int number){
	int digit = outputlayer[number];

	for(int j=0; j<structure[structure.size()-1];j++){
		calculateErrorAtOutputLayer(structure.size()-1, j, digit_encoding[digit][j]);
	}
	updateErrorsInBackwardPass();

}

void Ann::validateTestInput(){
	int total_tests = test_inputTable.size(), digit = -1;
	int correctly_validated = 0;
	long double accuracy = 0.0;
	for(int i=0;i<total_tests;i++){
		doForwardPassIteration(test_inputTable,i);
		digit = findDigit();
		cout<<digit<<endl;

		if(digit == test_output[i]){
			correctly_validated++;
		}
	}
	accuracy = ((long double) correctly_validated  )/ total_tests;

	//cout<<"total : "<<total_tests<<" validated : "<<correctly_validated<<endl;
	//cout<<"accuracy : ";
	cout << showpoint << fixed << setprecision(12) << accuracy << endl;

}

void Ann::trainWeightsModel(int iteration){

	for(int j=0;j<iteration;j++){

		for(int i=0;i<train_inputTable.size();i++){
			doForwardPassIteration(train_inputTable,i);
			//showOutput();
			doBackwardPassIteration(train_output,i);
			//showError();
			updateWeights();
			//showWeight();
		}
	}

	//std::cout<<"Weight matrix"<<std::endl;

	for(unsigned i=0;i<structure[1];i++){
		cout << showpoint << fixed << setprecision(12) << weightTable[1][node[1][i]] <<" ";
	}
	std::cout<<endl;

}


Ann::Ann(  char * train_input_file, char *train_output_file, char * test_input_file, char *test_output_file,
		char * structure_file, char * weight_file){

	alpha= 0.01;
	initStructure(structure_file);
	initDigitEncoding();
	initNode();
	initOutput();
	initError();


	initTrainInput(train_input_file);
	initTrainOutput(train_output_file);
	initTestInput(test_input_file);
	initTestOutput(test_output_file);
	initweightTable(weight_file);

	//cout<<"Sizes : "<<structure.size()<<": "<<train_inputTable.size()<<" : "<<train_output.size() <<" : "<< test_inputTable.size() <<" : "<<test_output.size()<<endl;
}




void Ann::showOutput(){
	std::cout<<"output matrix"<<std::endl;
	for(unsigned i=0;i<output.size();i++){
		for(unsigned j=0;j<output[i].size();j++){
			std::cout<<output[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"--------------"<<std::endl;
}

void Ann::showError(){
	std::cout<<"Error matrix"<<std::endl;
	for(unsigned i=0;i<error.size();i++){
		for(unsigned j=0;j<error[i].size();j++){
			std::cout<<error[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"--------------"<<std::endl;

}

void Ann::showNode(){
	std::cout<<"Node matrix"<<std::endl;
	for(unsigned i=0;i<node.size();i++){
		for(unsigned j=0;j<node[i].size();j++){
			std::cout<<node[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"--------------"<<std::endl;
}

void Ann::showWeight(){
	std::cout<<"Weight matrix"<<std::endl;
	for(unsigned i=0;i<weightTable.size();i++){
		for(unsigned j=0;j<weightTable[i].size();j++){
			std::cout<<weightTable[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"--------------"<<std::endl;
}
