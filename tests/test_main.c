#include "test_generic.h"

double lap;

void ocTestUtilTcpOrDie(ProtocolDesc* pd,bool isServer,const char* port)
{
	if(isServer)
	{ if(protocolAcceptTcp2P(pd,port)!=0)
		{ fprintf(stderr,"TCP accept failed\n");
			exit(1);
		}
	}
	else 
		if(protocolConnectTcp2P(pd,remote_host,port)!=0) 
		{ fprintf(stderr,"TCP connect failed\n");
			exit(1);
		}
}

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

	lap = (double)current_timestamp()/1000000;
	fprintf(stderr,"Executing test: %s\n", testName());
	fprintf(stderr,"Role: %s\n", (party==1?"1/Server":"2/Client"));
	execYaoProtocol(&pd,testMain,0);
	fprintf(stderr,"Total time: %lf s\n",(double)current_timestamp()/1000000-lap);
	cleanupProtocol(&pd);
	return 0;
}