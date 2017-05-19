#include <iostream>
#include <vector>
#include "jitd.h"
#include "jitd.cpp"
#include "crackPolicy.h"
#include "crackPolicy.cpp"

using namespace std;

int main() {
	crackPolicy<int>* p = new crackPolicy<int>(3);
	jitd<int> myJitd(p);
	int list[] = {5,2,7,3,9,4,2,3};
	myJitd.insert(list, 8);
	vector<int> result = myJitd.scan(3,6);
    for(int i = 0; i<result.size(); i++){
        cout << result[i] << endl;
    }
	return 0;
}
