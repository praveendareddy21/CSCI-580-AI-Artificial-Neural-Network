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
using namespace std;

long double Ann::getEuclideanDistance(long double x1, long double y1, long double x2, long double y2)
{
	long double x = x1 - x2; //calculating number to square in next step
	long double y = y1 - y2;
	long double dist;

	dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
	dist = sqrt(dist);

	return dist;
}

long double Ann::getEuclideanDistance(vector<long double> X, vector<long double> Y)
{
	long double squareddist = 0.0;
	long double result=0.0;
	for(unsigned i=0; i<X.size();i++){
		squareddist += pow(X[i] - Y[i], 2);
	}
	result = sqrt(squareddist);
	return result;
}


long double Ann::getSigmoid(long double in){
	long double exp_value;
	long double return_value;
	exp_value = exp(-in);
	return_value = 1 / (1 + exp_value);
	 return return_value;
}

void Ann::initweightTable(){
	int nodes = 6;
	weightTable = vector<vector<long double> > (nodes, vector<long double>(nodes, 0) );

	weightTable[0][1]= 1;
	weightTable[0][2]= 1;

	weightTable[0][3]= 1;
	weightTable[1][3]= 1;
	weightTable[2][3]= 1;
	weightTable[0][4]= 1;
	weightTable[3][4]= 1;



	weightTable[0][5]= 1 ;
	weightTable[3][5]= 1;

	/*
	weightTable[4][5]= 0.03;
	weightTable[0][6]= 0.01;
	weightTable[3][6]= -0.01;
	weightTable[4][6]= 0.04;
	*/


}

void Ann::initOutput(){
	static int arr0[] = {2, 1, 2};
	vector<int > structv (arr0, arr0 + sizeof(arr0) / sizeof(arr0[0]) );


	std::vector<std::vector<long double> > out;
	std::vector <int > :: iterator struct_iter;
	structure= structv;

	for(struct_iter=structure.begin();struct_iter!=structure.end();struct_iter++){
		out.push_back(vector<long double>(*(struct_iter), 0));
	}
	output = out;


	output[0][0]= 0.2;
	output[0][1]= 0.8;

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
		cout<<" node : "<<input_node<<endl;
		matWeight.set(i+1,0, weightTable[input_node][node[layer][nodeNum]]); //setting w0
	}
	matOut.show();
	matWeight.show();

	Matrix matO1 = matOut.multiply(matWeight);
	matO1.show();

	output[layer][nodeNum] = getSigmoid(matO1.get(0,0));
	cout<<" setting output "<<layer<<" "<<nodeNum<<" : "<<endl;
	cout << showpoint << fixed << setprecision(12) << output[layer][nodeNum] << endl;
}

void Ann::calculateErrorAt(int layer, int nodeNum){

	Matrix matError(1, output[layer+1].size() );
	Matrix matWeight(output[layer+1].size(), 1);

	int input_node = 0;
	long double calculatedValue = output[layer][nodeNum];

	cout<<"####################----------------###################"<<endl;

	for(int i=0;i < output[layer+1].size();i++ ){
		matError.set(0,i, error[layer+1][i]);
		input_node = node[layer][nodeNum];
		cout<<" node : "<<input_node<<" to : "<<node[layer+1][i]<<endl;
		matWeight.set(i,0, weightTable[input_node][node[layer+1][i]]); //setting w0
	}


	matError.show();
	matWeight.show();

	Matrix matO1 = matError.multiply(matWeight);
	matO1.show();

	error[layer][nodeNum] = calculatedValue * (1-calculatedValue) * matO1.get(0,0);

	cout<<" setting error "<<layer<<" "<<nodeNum<<" with a value as "<< calculatedValue<< " : ";
	cout << showpoint << fixed << setprecision(12) << error[layer][nodeNum] << endl;

	cout<<"####################++++++++++++++++###################"<<endl;
}

void Ann::calculateErrorAtOutputLayer(int layer, int nodeNum, long double outputLayerValue){

	long double calculatedValue = output[layer][nodeNum];

	error[layer][nodeNum] =  calculatedValue * (1-calculatedValue) * (outputLayerValue - calculatedValue );

}

void Ann::updateErrorsInBackwardPass(){

	for(int j=structure.size()-2; j>=0;j--){
		for(int i=0;i<structure[j];i++){

			cout<<"invoking updateError for "<<node[j][i]<<endl;
			calculateErrorAt(j,i);
		}
	}
}

void Ann::updateValuesInForwardPass(){

	for(int j=1; j<structure.size();j++){
		for(int i=0;i<structure[j];i++){

			cout<<"invoking updateValue for "<<node[j][i]<<endl;
			calculateValueAt(j,i);
		}
	}
}

void Ann::updateWeights(){

	for(int j=0; j<structure.size();j++){
		vector<int> temp;
		for(int i=0;i<structure[j];i++){

			//cout<<"current node : "<<node[j][i]<<endl;
			weightTable[0][node[j][i]] =  weightTable[0][node[j][i]] + alpha * 1 * error[j][i] ;
			cout<<"setting  ["<<0<<"]["<<node[j][i]<<"] as : "<<weightTable[0][node[j][i]]<<endl;
		}
	}

	for(int j=0; j<structure.size()-1;j++){
		vector<int> temp;
		for(int i=0;i<structure[j];i++){


			for(int k=0; k< structure[j+1]; k++){

				weightTable[node[j][i]][node[j+1][k]] =  weightTable[node[j][i]][node[j+1][k]] + alpha * output[j][i] * error[j+1][k] ;

				cout<<"setting  ["<<node[j][i]<<"]["<<node[j+1][k]<<"] as : "<<weightTable[node[j][i]][node[j+1][k]]<<endl;
			}
		}
	}

}
void Ann::doForwardPassIteration(){

}
void Ann::doBackwardPassIteration(){

}


Ann::Ann(){

	alpha= 0.01;
	initweightTable();
	initOutput();
	initError();
	showOutput();
	showError();
	initNode();
	showNode();



	/*
	calculateValueAt(1,0);
	calculateValueAt(1,1);
	calculateValueAt(2,0);
	calculateValueAt(2,1);
	*/
	updateValuesInForwardPass();

	calculateErrorAtOutputLayer(2, 0, 0.1);
	calculateErrorAtOutputLayer(2, 1, 0.9);

	cout<<"#######################################"<<endl;

	/*
	calculateErrorAt(1,0);
	calculateErrorAt(1,1);
	calculateErrorAt(0,0);
	calculateErrorAt(0,1);
	*/
	updateErrorsInBackwardPass();

	showError();


	cout << showpoint << fixed << setprecision(12) << error[0][0] << endl;
	cout << showpoint << fixed << setprecision(12) << error[0][1] << endl;

	updateWeights();

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



