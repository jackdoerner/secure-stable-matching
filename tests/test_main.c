#include <obliv.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "util.h"
#include "test_generic.h"

double lap;

int main(int argc,char* argv[])
{ 
	ProtocolDesc pd;

	if(argc<3)
	{
		if(argc<2) fprintf(stderr,"Port number missing\n");
		else fprintf(stderr,"Party missing\n");
		fprintf(stderr,"Usage: %s <port> <1|2>\n",argv[0]);
		return 1;
	}

	int party = (argv[2][0]=='1'?1:2);

	ocTestUtilTcpOrDie(&pd,party==1,argv[1]);

	setCurrentParty(&pd,party);

	srand(time(0));

	lap = wallClock();
	fprintf(stderr,"Executing test: %s\n", testName());
	fprintf(stderr,"Role: %s\n", (party==1?"1/Server":"2/Client"));
	execYaoProtocol(&pd,testMain,0);
	fprintf(stderr,"Total time: %lf s\n",wallClock()-lap);
	cleanupProtocol(&pd);
	return 0;
}