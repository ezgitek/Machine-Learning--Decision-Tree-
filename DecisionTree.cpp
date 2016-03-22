#include <iostream>
#include <fstream>
#include <string>
#include "DecisionTree.h"
#include "DataPoint.h"
using namespace std;

DecisionTree::DecisionTree(){
	DIM = 0;
	NUM_DATA_POINT = 0;
	samples = NULL;
}

DecisionTree::~DecisionTree(){
	for (int i = 0; i < DIM; i++)
	    {
	        delete samples[i]; //deletes pointers
	    }
}

DecisionTree::DecisionTree(const DecisionTree& dt){
	NUM_DATA_POINT = dt.NUM_DATA_POINT;
	samples = new DataPoint*[dt.NUM_DATA_POINT];
	DIM = dt.DIM;
	copy(dt->samples, dt->samples + NUM_DATA_POINT, this->samples);
} 
	
DecisionTree& DecisionTree::operator = (const DecisionTree& dt){
	if (this == &dt)
		return *this;
	NUM_DATA_POINT = dt.NUM_DATA_POINT;
		samples = new DataPoint*[dt.NUM_DATA_POINT];
		DIM = dt.DIM;
			copy(dt->samples, dt->samples + NUM_DATA_POINT, this->samples);
	return *this;
} 

void DecisionTree::importData(char* infileName){
	ifstream in (infileName); //gets input in a word by word fashion
	in>>DIM>>NUM_DATA_POINT;
	samples = new DataPoint*[NUM_DATA_POINT];

	for (int i=0; i<NUM_DATA_POINT; i++){ //gets the data points (horizontal)

		int int_cl = 0; //integer value of class label (0 or 1)
		in>>int_cl;
		bool cl = true; //boolean value of class label (true or false)
		if(int_cl == 0)
			cl = false;

		double* _feat = new double[DIM]; //holds features for one data point

		for (int j=0; j<DIM; j++){ //gets features
			double temp_feat = 0;
			in>>temp_feat;
			_feat[j] = temp_feat;
		}

		samples[i] = new DataPoint(cl, DIM, _feat);
	}
}


void DecisionTree::runDecisionTreeAlgorithm(char* outfileName){
	int min_misc_rate = NUM_DATA_POINT;
	int min_feature = 0; //the feature which has min misc rate

	for(int i=0; i<DIM; i++){ //visits features one by one (vertical)
		int min_indiv_rate = NUM_DATA_POINT; //min miscalculation rate of only one feature (indiv=individual)
			for(int j=0; j<NUM_DATA_POINT; j++){
				int temp = 0; //miscalculation rate for each data point
					for(int k=0; k<NUM_DATA_POINT; k++){
				/*example for the if:
				* suppose classLabel = 1 and feature = 20
				* if the second data point has cl = 1 and is smaller than 20
				* or cl = 0 and is greater than 20
				* it may be a misclassification*/
						if((samples[k]->classLabel == samples[j]->classLabel &&
								samples[k]->features[i] < samples[j]->features[i]) ||
								(samples[k]->classLabel != samples[j]->classLabel
										&& samples[k]->features[i] >= samples[j]->features[i])){
							temp++;
						}
					}
					/*...or, if the above situation is correct
					 * suppose the reverse situation is misclassified
					 * the misc rate should be 0.02, not 0.98 for example */
						if(temp > NUM_DATA_POINT/2){
							temp = NUM_DATA_POINT - temp;
						}

					if(temp<min_indiv_rate)
						min_indiv_rate = temp;

			}
			if(min_indiv_rate<min_misc_rate){
				min_misc_rate=min_indiv_rate;
				min_feature = i;
			}
	}

	ofstream out (outfileName);
	out << min_feature << " " << (double) min_misc_rate / NUM_DATA_POINT ;

}
