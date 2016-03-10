#include"waksman.h"
#include<stdlib.h>
#include<string.h>

size_t waksmanSwapCount(size_t n)
{
  if(n<=1) return 0;
  if(n==2) return 1;
  return n-1+waksmanSwapCount(n/2)+waksmanSwapCount((n+1)/2);
}

// Creates network. Output array lengths should be at least
// waksmanSwapCount(n). Returns this size waksmanSwapCount(n)
// If conventions here change, waksmanSwitches must also be changed
size_t waksmanNetwork(unsigned a[],unsigned b[],size_t n)
{
  size_t i,j=0,jd;
  if(n<=1) return 0;
  for(i=0;i<n-1;i+=2) 
  { a[j]=i;
    b[j]=i+1;
    j++;
  }
  // map1: 2*i -> i -> 2*i for i in [0,n/2]
  jd=waksmanNetwork(a+j,b+j,n/2);
  for(i=0;i<jd;++i) { a[i+j]*=2; b[i+j]*=2; }
  j+=jd;
  // map2: 2*i+1 -> i -> 2*i+1 for i in [0,n/2]
  //       n-1 ->  n/2  -> n-1
  jd=waksmanNetwork(a+j,b+j,(n+1)/2);
  for(i=0;i<jd;++i) 
  { if(a[i+j]!=n/2) a[i+j]=2*a[i+j]+1; else a[i+j]=n-1;
    if(b[i+j]!=n/2) b[i+j]=2*b[i+j]+1; else b[i+j]=n-1;
  }
  j+=jd;
  for(i=0;i<n-2;i+=2)
  { a[j]=i;
    b[j]=i+1;
    j++;
  }
  return j;
}

// Unfortunately, randomly choosing swaps does not seem to produce uniformly
// random permutation. So we do this off-the-protocol: map a given permutation
// to the corresponding waksmanNetwork switch.
// arr is a permutation of the numbers [0..n-1]
// output is of length waksmanSwapCount(n), tells us if gate i should swap
// If conventions here change, waksmanNetwork must also be changed
size_t waksmanSwitches(const unsigned arr[],unsigned n,bool output[])
{
  if(n<=1) return 0;
  unsigned *inv = malloc(n*sizeof(*arr));
  unsigned *arr1 = malloc((n/2)*sizeof(*arr));
  unsigned *arr2 = malloc(((n+1)/2)*sizeof(*arr));
  bool* outputTail = malloc(((n-1)/2)*sizeof(bool));
  bool* set = calloc(n,sizeof(bool));
  unsigned i,j,used=0,nxtj;
  for(i=0;i<n;++i) inv[arr[i]]=i;

  i=n;
  // output head length == n/2
  while(i-->0) if(!set[i])
  { j=i;
    do
    { unsigned prej=arr[j];
      set[j]=true;
      // go from prej to j through lower box
      if(prej/2<n/2) 
      { output[prej/2]=1-prej%2; // swap A if prej even
        used++;
      }
      arr2[j/2]=prej/2;
      if(j/2<(n-1)/2) outputTail[j/2]=1-j%2;  // swap B if j even

      if(n%2 && prej==n-1) break; // odd "open" case
      unsigned prenj=(prej^1);
      nxtj=inv[prenj];
      set[nxtj]=true;
      // go from prenj to nxtj through upper box
      // swap A already done (shared with above)
      arr1[nxtj/2]=prenj/2;
      if(nxtj/2<(n-1)/2) outputTail[nxtj/2]=nxtj%2; // swap B
      nxtj^=1;
      j=nxtj;
    }while(j/2!=i/2);
  }

  used+=waksmanSwitches(arr1,n/2,output+used);
  used+=waksmanSwitches(arr2,(n+1)/2,output+used);
  for(i=0;i<(n-1)/2;++i) output[used++]=outputTail[i];

  free(set);
  free(outputTail);
  free(arr1);
  free(arr2);
  free(inv);
  return used;
}

static inline unsigned max(unsigned a,unsigned b) { return a>b?a:b; }
// The number of "layers" in the circuit
size_t waksmanStrataCount(size_t n)
{
  if(n<=1) return 0;
  if(n==2) return 1;
  return 2 + max(waksmanStrataCount(n/2),waksmanStrataCount((n+1)/2));
}

// The above functions do not produce neat "layers" in the circuit
// This function assigns "levels" to each swap gate, so we know in which order
// to evaluate them. Levels range in [0,waksmanStrataCount(n))
// Output buffer should be of size waksmanSwapCount(n).
void waksmanStrataAssign(unsigned level[],
    const unsigned a[], const unsigned b[], size_t n)
{
  int i,sc = waksmanSwapCount(n);
  unsigned *dlevel = calloc(n,sizeof(*dlevel));
  memset(level,0,sc*sizeof(*level));
  for(i=0;i<sc;++i)
  { int l = max(dlevel[a[i]],dlevel[b[i]]);
    level[i] = l;
    dlevel[a[i]] = dlevel[b[i]] = l+1;
  }
  free(dlevel);
}

/*
   Permutes the array arr according to perm. i-th element is sent to perm[i].
   n - number of elements
   elt - size of each element, in bytes
   pdone - an array that will be used internally as a "done" flag.
           All values are expected to be pre-initialized to some 
           arbitrary constant. On return, all values will be incremented by 1.
   scratch - pointer to some memory of size elt, enough to hold a 
             single element
   */
void permute_in_place(char* arr,size_t n,size_t elt,const unsigned perm[],
    char pdone[],void* scratch)
{
  if(n==0) return;
  int undone = pdone[0];
  int i,j;
  for(i=0;i<n;++i) if(pdone[i]==undone)
  { for(j=i;perm[j]!=i;j=perm[j])
    { // swap perm[j] and i
      memcpy(scratch,arr+elt*perm[j],elt);
      memcpy(arr+elt*perm[j],arr+elt*i,elt);
      memcpy(arr+elt*i,scratch,elt);
      pdone[j]++;
    }
    pdone[j]++;
  }
}
// Rearranges them to create levels
void waksmanStratify(unsigned a[],unsigned b[],bool switches[],
                     size_t n,size_t strata_sizes[])
{
  int sc = waksmanSwapCount(n), lc = waksmanStrataCount(n);
  unsigned* level = malloc(sc*sizeof(unsigned));
  waksmanStrataAssign(level,a,b,n);
  unsigned* perm = malloc(sc*sizeof(unsigned));
  int i,j,cur,total=0;
  for(i=0;i<lc;++i) 
  { cur=0;
    for(j=0;j<sc;++j) if(level[j]==i) perm[j]=(total+ cur++);
    if(strata_sizes) strata_sizes[i]=cur;
    total+=cur;
  }
  char* pdone = calloc(sc,sizeof(char));
  unsigned temp;
  bool btemp;
  permute_in_place((void*)a,sc,sizeof(a[0]),perm,pdone,&temp);
  permute_in_place((void*)b,sc,sizeof(b[0]),perm,pdone,&temp);
  if(switches) 
    permute_in_place((void*)switches,sc,sizeof(switches[0]),perm,pdone,&btemp);
  free(pdone);
  free(perm);
  free(level);
}
