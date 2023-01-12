#include <iostream>
#include "visualization.h"


int main(int argc, char** argv){
		srand(static_cast<unsigned>(time(0)));	
		visualization v = visualization(1500, 850);

		while(!v.isClosed()){
				v.run();
		}

		return 0;
}
