
#define MAXSIZE 20000
#define MAXSIZE2 625
typedef struct element{
  int v;
}elt;

//CMT:
//Provide short description about each variable of struct
// eg: Its not clear whether you will store x or x+10000
//     in P and N.
// Usually when you start implmenting anything move all
// declarations of struct or methods into a ".h" file
// Make sure you write description related to each 
// variable in ".h" file.
// Also add description at the beginning of the file 
// which gives general understanding to reader or other programmer.
//    Questions: (a) What is the value of N[last]

typedef struct Set {
  int size;
  unsigned int A[MAXSIZE2];
  int P[MAXSIZE];
  int N[MAXSIZE];
}Set;

typedef struct SearchResult {
  int found;
  elt *val;
}SearchResult;

// ----------------- Set Methods ----------------------
Set* buildSet(elt* a[], int n);
int len(Set *s);

Set* put(elt *x, Set *S);
Set* rmv(elt *x, Set *S);

int isEmpty(Set* s);
SearchResult search(elt *x, Set *s);
SearchResult next(elt *x, Set *s);
SearchResult prev(elt *x, Set *s);
SearchResult last(Set *s);
SearchResult first(Set *s);
//int position(unsigned int x,int t);

// ---------------- INTERNAL METHODS -----------------
Set* _buildEmptySet();
int cmp(elt *e1, elt *e2);
int eltval(elt *e1);
elt *buildValue(int id);
//---------------------------------------------------

//malloc
//e->v = id
// ret e;

// precondition : n >= 0
// output : set s with all items of array a in it.
// postcondition : for all i, 0<=i<n, a[i] in s 
Set* buildSet(elt *a[], int n)
{
  Set *s = _buildEmptySet();
  int i = 0;
  while(i<n)
    {
      s = put(a[i],s);
      i = i + 1;
    }
  
  return s;
}

// output : size of the set s
int len(Set *s) {
  return s->size;
}

int isEmpty(Set *s)
{
  int k = 0;
  if(len(s) == 0) 
    k = 1;
  return k;
}

Set* put(elt *x, Set *s)                      
{                 
      assert(x != NULL && s!=NULL);                               
      SearchResult sr = search(x,s); 
      int id = eltval(x);          
      if(sr.found ==0)
      {        
             SearchResult f_sr = first(s); 
              int fst = eltval(f_sr.val) ;  
             SearchResult l_sr = last(s); 
             int lst = eltval(l_sr.val) ;
                   
                
             if(s->size==0)                        
             {
                 //CMT
                 //(1) Constants like 10000 or 32 always 
                 //    define it in #define or global constants.
                 //    This will help you to change only at one place
                 //    and not multiple places.
                 //(2) Whenever you are working on power of 
                 //    2 always use bitwise operator.
                 //(3) Give short description for each variable
                 //    it helps debugging. also try reducing variables
                 //    as much as possible.  
                  int q= (id+10000)/32;
	                int m = (id+10000)%32;
	                int arr_ele= s->A[q] ;
	                int z= 1<<(31-m) |  arr_ele;
	                s->A[q] = z;
                     // s = set_1(x,s);
	                  s->P[id+10000]=id;          
	                  s->N[id+10000]=id;
                    s->size = s->size + 1;

                }
                else if(fst>id)
                {
                  int q=(id+10000)/32;
	                int m = (id+10000)%32;
	                int arr_ele= s->A[q] ;
	                int z= 1<<(31-m) |  arr_ele;
	                s->A[q] = z;
                  // s = set_1(x,s);
	               s->P[fst+10000]=id;
	                s->N[id+10000]=fst-10000;
	                 s->P[id+10000]=id;
	                
	                s->size=s->size+1;
                }
            
                else if(lst<id)
                 {
                     int q= (id+10000)/32;
	                   int m = (id+10000)%32;
	                   int arr_ele= s->A[q] ;
	                   int z= 1<<(31-m) |  arr_ele;
	                   s->A[q] = z;
                    // s = set_1(x,s);
	                  s->P[id+10000]=lst-10000;
                    s->N[id+10000]=id;
	                  s->N[lst]=id;
	                  s->size=s->size+1;
                 }


                else if(fst<id && lst>id)
                {
                  int q= (id+10000)/32;
	                int m = (id+10000)%32;
	                int arr_ele= s->A[q] ;
	                int z= 1<<(31-m) |  arr_ele;
	                s->A[q] = z;
	  
                  //  s = set1(x,s);
	                 int y=fst;
                  //  int prev_x = fst;
		              while(s->N[y+10000]<id)
	                {  
	                     y = s->N[y+10000];
                  }
                  
	           s->N[id+10000]=s->N[y+10000];
	           s->N[y+10000]=id;
	           s->P[id+10000]=y;
	            s->P[(s->N[id+10000])+10000]=id;
	            s->size=s->size+1;
        }// CMT: See if You can reduce these multiple ifs ?                
       }
  return s;
}

//CMT: Before submission, remove ghost code.
Set set1(int x,Set *s)
{
      int q= (x+10000)/32;
      int m = (x+10000)%32;
      s->A[q]= 1<<(31-m) |  s->A[q];
            
	   return *s;
}


// output : set after remeoval of x from s
// postcondition : search(x,s) should return found as 0

Set* rmv(elt *x,Set *s)
{
  
  SearchResult r = search(x,s);

  if(r.found == 1)
    {
      // index of value x in array
      SearchResult f_sr = first(s); 
      int fst = eltval(f_sr.val) ;     
      SearchResult l_sr = last(s); 
      int lst = eltval(l_sr.val) ;
                   
      int id = eltval(x);
      // CMT: You already have values in P and N arrays regarding
      // prev and next why cant you use that ?
      // No need of using first and last. Looking at P and N you can
      // find what changes need to make.
      // One general observation : Apart from precond and postcond
      //  also write what will be state of each variable of
      //  struct. Eg. P[first] will have what value. It is not clear
      //  currently P[first] will have what values.
      if(fst < id  && lst > id)
	{

	
	  int q= (id+10000)/32;
	  int m = (id+10000)%32;
	  int arr_ele= s->A[q] ;
	  int z= 1<<(31-m) ^  arr_ele;
	  s->A[q] = z;
      //  s = reset_1(x,s);
	  s->P[(s->N[id+10000])+10000]=s->P[id+10000];
	  s->N[(s->P[id+10000])+10000]=s->N[id+10000];
	  s->P[id+10000]=0;
	  s->N[id+10000]=0;
	  s->size=s->size-1;
        }
      else if(id == fst)
	  {    
        int q= (id+10000)/32;
        int m = (id+10000)%32;
	    int arr_ele = s->A[q] ;
	    int z= 1<<(31-m) ^  arr_ele;
	    s->A[q] = z;
        //  s = reset_1(x,s);
	    s->P[(s->N[id+10000])+10000]= s->N[id+10000];
	    s->N[id+10000]=0;
	    s->P[id+10000]=0;
	    s->size=s->size-1;
	}
      else if(id== lst)
	{       
	  int q= (id+10000)/32;
	  int m =(id+10000)%32;
	  int arr_ele= s->A[q] ;
	  int z= 1<<(31-m) ^  arr_ele;
	  s->A[q] = z;
      //  s = reset_1(x,s);
	  s->N[(s->P[id+10000])+10000]=s->P[id+10000];
	  s->size=s->size-1;
	}
    }
  return s;
}
//CMT: Remove ghost code.
Set reset_1(int x,Set s)   // x: number which bit is reset 
{
      int q= (x+10000)/32;
      int m = (x+10000)%32;
      s.A[q]= 1<<(31-m) ^  s.A[q];
            
      return s;
}

// output : r, r.found == 1 if element is there in set
//         otherwise 0
SearchResult search(elt *x,Set *s)
{
  SearchResult r;
  r.found = 0;
  r.val = buildValue(10000);
  int id = eltval(x);
  int q= (id+10000)/32;
  int m = (id+10000)%32;
  int arr_ele= s->A[q] ;
  int z= 1<<(31-m) &  arr_ele;
     
  if( z != 0) 
    {
      r.found = 1;
      r.val = buildValue(id);
    }
  return r;
}


// next element of x when all elements of set 
// are put in non-decreasing order
// output : r, r.found will be 1 if x exists and has next element
//          otherwise 0
SearchResult next(elt *x,Set *s)
{
  assert(x!=NULL && s!=NULL);
  
  SearchResult rr= search(x,s);
  SearchResult r;          
  SearchResult l_sr = last(s); 
  int lst = eltval(l_sr.val) ;
                   
  r.found = 0;
  if(s->size >1 && rr.found==1 && eltval(x) != lst){ 
    int id = eltval(x);
    r.val=buildValue(s->N[id+10000]);
    r.found=1;
  }
  
  return r;
}  

// previous element of x when all elements of set 
// are put in non-decreasing order
// output : r, r.found will be 1 if x exists and has previous element
//          otherwise 0
SearchResult prev(elt *x , Set *s){
  assert(x!=NULL && s!=NULL);
  SearchResult rr = search(x,s);
  SearchResult r;
  r.found = 0;
  SearchResult f_sr = first(s); 
  int fst = eltval(f_sr.val) ;     
          
  if(s->size > 1 && rr.found == 1 && eltval(x)!=fst)
    {
      int id = eltval(x);
      r.found=1;
      r.val = buildValue(s->P[id+10000]);
    }
  return r;
}

SearchResult first(Set *s) {
  SearchResult r;
  r.found=0;
       if(s->size >0)
       {
           r.found=1;

	   int i=0,idx=0,pos=0;
       // CMT: Do not use constants in code
       // use #define or global variables
            while (s->A[i]==0 && i<625)
           {
          
               i=i+1;
	       idx = i;
           }
           unsigned int k = s->A[idx];
           int j =31 ;
	   unsigned int b[32];
	while(j>=0)
	{
		unsigned int q;
		q= k & 1;
		k=k>>1;
		b[j]=q;
                j=j-1 ;
         }
          i=0;
          while(i<32)
          {
             if(b[i]==1)
            {
                pos=i;
                i=32;
            }
            i=i+1;
        }
           r.val=buildValue((idx*32)+pos-10000);   
       }
    return r;
}

SearchResult last(Set *s){
  SearchResult r;
  r.found=0;
  if(s->size >0)
    {
      r.found=1;
             int i=MAXSIZE2-1,idx;
             // to find the index and element of s.a[]
             while (s->A[i]==0)
             {
               i=i-1;
	       idx=i;
             }
            unsigned int k = s->A[i];
             int pos;
             int j =0;
	    unsigned int b[32];
	    while(j<32)
	{
		unsigned int q;
		q= k &1;
		k=k>>1;
		b[j]=q;
                j=j+1 ;
         }
           i=0;
          while(i<32)
          {
             if(b[i]==1)
            {
                pos=i;
                i=32;
            }
            i=i+1;
          }
           r.val=buildValue(idx*32+pos-10000);  
        }
  return r;
}

Set*  _buildEmptySet() {
  Set* s = (Set *)malloc(sizeof(Set));
  s->size = 0;
  int i = 0;
  while(i<MAXSIZE2){
    s->A[i] = 0;
    i = i+1;
  }
  return s;
}


/*
 *   cmp ---> Takes 2 elements and compares values
 *            if e1 > e2 returns positive integer
 *            if e1 < e2 returns negative integer
 *            if e1 ==e2 return 0
 */
int cmp(elt *e1, elt *e2) {
  assert(e1!=NULL && e2 != NULL);
  // As its internal method
  // e1 and e2 should get checked in caller.
  int k = eltval(e1) - eltval(e2);
  return k;
}
// CMT: Good to see you have used eltval everywhere
// Always follow this. User data should be access from
// only one place.
int eltval(elt *e1){
  assert(e1!=NULL);
  return e1->v;
}

elt *buildValue(int id){
  elt *e = (elt *)malloc(sizeof(elt));
  e->v = id;
  return e;
}
