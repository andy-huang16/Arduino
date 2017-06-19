#include <iostream>
#include "bpnet.h"
using namespace std;

#define BPM_ITER	500000
#define FAST		1
#define	SLOW		0

#define BLACKL		215
#define BLACKR		190

#define WHITEL		245
#define WHITER		260
void main() {
	CBPNet bp;

	for (int i = 0; i<BPM_ITER; i++) {
		/*bp.Train(0, 0, 1, 1);
		bp.Train(0, 1, 0, 1);
		bp.Train(1, 0, 1, 0);
		bp.Train(1, 1, 1, 1);*/

		//Both sensors detect white: drive straight
		bp.Train(WHITEL, WHITER, FAST, FAST);

		//Left sensor detects white, right sensor detects black: turn right
		bp.Train(WHITEL, BLACKR, FAST, SLOW);

		//Left sensor detects black, right sensor detects white: turn left 
		bp.Train(BLACKL, WHITER, SLOW, FAST);

		//If both sensors detect black: drive straight
		//bp.Train(45, 165, FAST, FAST);
	}

	/*cout << "0,0 = " << bp.Run(0, 0) << "," << bp.Run2(0, 0) << endl;
	cout << "0,1 = " << bp.Run(0, 1) << "," << bp.Run2(0, 1) << endl;
	cout << "1,0 = " << bp.Run(1, 0) << "," << bp.Run2(1, 0) << endl;
	cout << "1,1 = " << bp.Run(1, 1) << "," << bp.Run2(1, 1) << endl;
*/
	cout << "67, 230 = " << bp.Run(WHITEL, WHITER) << ", " << bp.Run2(WHITEL, WHITER) << endl;
	cout << "67, 165 = " << bp.Run(WHITEL, BLACKR) << ", " << bp.Run2(WHITEL, BLACKR) << endl;
	cout << "45, 230 = " << bp.Run(BLACKL, WHITER) << ", " << bp.Run2(BLACKL, WHITER) << endl;
	//cout << "45, 165 = " << bp.Run(45, 165) << ", " << bp.Run2(45, 165) << endl << endl << endl;

	bp.print();
}