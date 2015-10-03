#include<obliv.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#include"util.h"
#include"montgomery.h"

double lap;

int main(int argc,char* argv[])
{ 
  ProtocolDesc pd;
  protocolIO io;

  if(argc<4)
  {
    if(argc<2) fprintf(stderr,"Port number missing\n");
    else if(argc<3) fprintf(stderr,"Party missing\n");
    else fprintf(stderr,"string missing\n");
    fprintf(stderr,"Usage: %s <port> <1|2> <string>\n",argv[0]);
    fprintf(stderr,"  Party 1 provides key in hex\n");
    fprintf(stderr,"  Party 2 provides plaintext in hex\n");
    return 1;
  }

  int i, party = (argv[2][0]=='1'?1:2);

  //protocolUseStdio(&pd);
  ocTestUtilTcpOrDie(&pd,party==1,argv[1]);
  if(party==1) {
    unsigned int xint = atoi(argv[3]);
    unsigned int mint = atoi(argv[4]);
    for (int ii = 0; ii < BYTES; ii ++) {
      io.x[ii] = xint;
      io.m[ii] = mint;
      xint = xint >> 8;
      mint = mint >> 8;
    }
  } else {
    unsigned int nint = atoi(argv[3]);
    for (int ii = 0; ii < BYTES; ii ++) {
      io.n[ii] = nint;
      nint = nint >> 8;
    }
  }
  setCurrentParty(&pd,party);

  lap = wallClock();
  execYaoProtocol(&pd,montgomeryMain,&io);
  fprintf(stderr,"Total time: %lf s\n",wallClock()-lap);
  cleanupProtocol(&pd);
  fprintf(stderr,"Result: ");
  unsigned int result = 0;
  for (int ii = BYTES - 1; ii >= 0; ii --) {
    result = result << 8;
    result += io.result[ii] & 0xff;
  }
  fprintf(stderr,"%u",result);
  fprintf(stderr,"\n");
  return 0;
}
