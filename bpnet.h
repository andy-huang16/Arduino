/* ========================================== *
* Filename:	bpnet.h                       *
* Author:		James Matthews.               *
*											  *
* Description:								  *
* This is a tiny neural network that uses	  *
* back propagation for weight adjustment.	  *
* ========================================== */

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

#define BP_LEARNING	(float)(.25)	// The learning coefficient.
#define MAXL 300
#define MINL 0
#define MAXR 300
#define MINR 0
class CBPNet {
public:
	CBPNet();
	~CBPNet() {};

	float Train(float, float, float, float);
	float Run(float, float);
	float Run2(float, float);
	void print();

private:
	float m_fWeights[3][4];		// Weights for the 3 neurons.

	float Sigmoid(float);		// The sigmoid function.
};

CBPNet::CBPNet() {
	srand((unsigned)(time(NULL)));

	for (int i = 0; i<3; i++) {
		for (int j = 0; j<4; j++) {
			// For some reason, the Microsoft rand() function
			// generates a random integer. So, I divide by the
			// number by MAXINT/2, to get a num between 0 and 2,
			// the subtract one to get a num between -1 and 1.
			m_fWeights[i][j] = (float)(rand()) / (32767 / 2) - 1;
		}
	}
}

float CBPNet::Train(float i1, float i2, float d, float d2) {
	// These are all the main variables used in the 
	// routine. Seems easier to group them all here.

	float net1, net2, i3, i4, out, out2;

	/*float average = (70 + 40) / 2;
	float range = (70 - 40) / 2;

	float average2 = (250 + 150) / 2;
	float range2 = (250 - 150) / 2;*/

	i1 = (i1 - MINL) / (MAXL - MINL) ;
	i2 = (i2 - MINR) / (MAXR - MINR);

	// Calculate the net values for the hidden layer neurons.
	net1 = 1 * m_fWeights[0][0] + i1 * m_fWeights[1][0] + i2 * m_fWeights[2][0];
	net2 = 1 * m_fWeights[0][1] + i1 * m_fWeights[1][1] + i2 * m_fWeights[2][1];

	// Use the hardlimiter function - the Sigmoid.
	i3 = Sigmoid(net1);
	i4 = Sigmoid(net2);

	// Now, calculate the net for the final output layer.
	net1 = 1 * m_fWeights[0][2] + i3 * m_fWeights[1][2] + i4 * m_fWeights[2][2];
	out = Sigmoid(net1);

	net2 = 1 * m_fWeights[0][3] + i3 * m_fWeights[1][3] + i4 * m_fWeights[2][3];
	out2 = Sigmoid(net2);

	// We have to calculate the deltas for the two layers.
	// Remember, we have to calculate the errors backwards
	// from the output layer to the hidden layer (thus the
	// name 'BACK-propagation').
	float deltas[3], deltas2[3];

	deltas[2] = out*(1 - out)*(d - out);
	deltas[1] = i4*(1 - i4)*(m_fWeights[2][2])*(deltas[2]);
	deltas[0] = i3*(1 - i3)*(m_fWeights[1][2])*(deltas[2]);

	deltas2[2] = out2*(1 - out2)*(d2 - out2);
	deltas2[1] = i4*(1 - i4)*(m_fWeights[2][3])*(deltas2[2]);
	deltas2[0] = i3*(1 - i3)*(m_fWeights[1][3])*(deltas2[2]);

	// Now, alter the weights accordingly.
	float v1 = i1, v2 = i2;
	for (int i = 0; i<3; i++) {
		// Change the values for the output layer, if necessary.
		if (i == 2) {
			v1 = i3;
			v2 = i4;
		}

		m_fWeights[0][i] += BP_LEARNING * 1 * deltas[i];
		m_fWeights[1][i] += BP_LEARNING * v1 *deltas[i];
		m_fWeights[2][i] += BP_LEARNING * v2 *deltas[i];

	}

	m_fWeights[0][3] += BP_LEARNING * 1 * deltas2[2];
	m_fWeights[1][3] += BP_LEARNING * i3 *deltas2[2];
	m_fWeights[2][3] += BP_LEARNING * i4 *deltas2[2];

	/*if (out != d)
	{
		deltas[0] = BP_LEARNING*(d - out) * 1;
		m_fWeights[0][2] += deltas[0];

		deltas[1] = BP_LEARNING*(d - out) * i1;
		m_fWeights[1][2] += deltas[1];

		deltas[2] = BP_LEARNING*(d - out) * i2;
		m_fWeights[2][2] += deltas[2];
	}*/

	/*if (out2 != d2)
	{
		deltas2[0] = BP_LEARNING*(d2 - out2) * 1;
		m_fWeights[0][3] += deltas2[0];

		deltas2[1] = BP_LEARNING*(d2 - out2) * i1;
		m_fWeights[1][3] += deltas2[1];

		deltas2[2] = BP_LEARNING*(d2 - out2) * i2;
		m_fWeights[2][3] += deltas2[2];
	}*/

	return out;
}

float CBPNet::Sigmoid(float num) {
	//return log(1 + exp(num));
	return (float)(1 / (1 + exp(-num)));
}

float CBPNet::Run(float i1, float i2) {
	// I just copied and pasted the code from the Train() function,
	// so see there for the necessary documentation.

	float net1, net2, i3, i4;

	//float average = (70 + 40) / 2;
	//float range = (70 - 40) / 2;

	//float average2 = (250 + 150) / 2;
	//float range2 = (250 - 150) / 2;

	i1 = (i1 - MINL) / (MAXL - MINL);
	i2 = (i2 - MINR) / (MAXR - MINR);

	net1 = 1 * m_fWeights[0][0] + i1 * m_fWeights[1][0] +
		i2 * m_fWeights[2][0];
	net2 = 1 * m_fWeights[0][1] + i1 * m_fWeights[1][1] +
		i2 * m_fWeights[2][1];

	i3 = Sigmoid(net1);
	i4 = Sigmoid(net2);

	net1 = 1 * m_fWeights[0][2] + i3 * m_fWeights[1][2] +
		i4 * m_fWeights[2][2];
	return Sigmoid(net1);
}

float CBPNet::Run2(float i1, float i2) {
	// I just copied and pasted the code from the Train() function,
	// so see there for the necessary documentation.

	float net1, net2, i3, i4;

	i1 = (i1 - MINL) / (MAXL - MINL);
	i2 = (i2 - MINR) / (MAXR - MINR);

	net1 = 1 * m_fWeights[0][0] + i1 * m_fWeights[1][0] +
		i2 * m_fWeights[2][0];
	net2 = 1 * m_fWeights[0][1] + i1 * m_fWeights[1][1] +
		i2 * m_fWeights[2][1];

	i3 = Sigmoid(net1);
	i4 = Sigmoid(net2);

	net2 = 1 * m_fWeights[0][3] + i3 * m_fWeights[1][3] + i4 * m_fWeights[2][3];
	return Sigmoid(net2);
}

void CBPNet::print()
{
	cout << "m_fWeights[0][0]: " << m_fWeights[0][0] << endl;
	cout << "m_fWeights[1][0]: " << m_fWeights[1][0] << endl;
	cout << "m_fWeights[2][0]: " << m_fWeights[2][0] << endl << endl;

	cout << "m_fWeights[0][1]: " << m_fWeights[0][1] << endl;
	cout << "m_fWeights[1][1]: " << m_fWeights[1][1] << endl;
	cout << "m_fWeights[2][1]: " << m_fWeights[2][1] << endl << endl;

	cout << "m_fWeights[0][2]: " << m_fWeights[0][2] << endl;
	cout << "m_fWeights[1][2]: " << m_fWeights[1][2] << endl;
	cout << "m_fWeights[2][2]: " << m_fWeights[2][2] << endl << endl;
	
	cout << "m_fWeights[0][3]: " << m_fWeights[0][3] << endl;
	cout << "m_fWeights[1][3]: " << m_fWeights[1][3] << endl;
	cout << "m_fWeights[2][3]: " << m_fWeights[2][3] << endl;

}
#pragma once