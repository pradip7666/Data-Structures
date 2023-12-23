#include<stdio.h>
#define MAXSIZE 20000
typedef struct Set {
    int size;
    int A[MAXSIZE];
    int P[MAXSIZE];
    int N[MAXSIZE];
    int first;
    int last;
}Set;

typedef struct SearchResult {
    int found;
    int val;
}SearchResult;

// ----------------- Set Methods ----------------------
Set buildSet(int a[], int n);
int len(Set s);

Set put(int x, Set S);
Set rmv(int x, Set S);

int isEmpty(Set s);
SearchResult search(int x, Set S);
/*
int prev(int x, Set s)
int next(int x, Set s);
int first(Set s);
int last(Set s);
*/

// ---------------- INTERNAL METHODS -----------------
Set _buildEmptySet();
SearchResult _search(int x, Set s);

//---------------------------------------------------


// precondition : n >= 0
// output : set s with all items of array a in it.
// postcondition : for all i, 0<=i<n, a[i] in s 
Set buildSet(int a[], int n)
{
    Set s = _buildEmptySet();
    int i = 0;
    while(i<n)
    {
        s = put(a[i],s);
        i = i + 1;
    }
    return s;
}

// output : size of the set s
int len(Set s) {
    return s.size;
}

// output : set after putting element in s
// postcondition : search(x,s) should return found as 1
Set put(int x, Set s)
{
    SearchResult r = _search(x,s);
    if(r.found==0)
    {
       s.A[x+10000]=1;
       if(s.size==0)
       {
         	    
          s.A[(x+10000)] = 1;
	  s.first=x;
	  s.last=x;
	  s.P[x+10000]=x;
	  s.N[x+10000]=x;
          s.size = s.size + 1;
       }
       else if(s.first>x){
	       s.A[x+10000]=1;
	       s.P[(s.first) + 10000]=x;
	       s.N[x+10000]=s.first;
	       s.P[x+10000]=x;
	       s.first=x;
	       s.size=s.size+1;
	    }
       else if(s.last<x){
              s.A[x+10000]=1;
	      s.P[x+10000]=s.last;
              s.N[x+10000]=x;
	      s.N[(s.last)+10000]=x;
	      s.last=x;
	      s.size=s.size+1;
       
       }
       else if(s.first<x && s.last>x)
       {
            s.A[x+10000]=1;
	  
	    if((s.last-x) <= (x-s.first))
           {
		   int i=x+1;
		   while(i<=s.last)
		   {
			   if(s.A[i+10000] == 1)
	                   {
				  s.N[x+10000]=i;
				  s.P[x+10000]=s.P[i+10000];
				  s.N[(s.P[i+10000])+10000];
			          s.P[i+10000]=x;
				  
			   }
			   i=i+1;
		   
		   }
		   s.size=s.size+1;
	   }
	    else
	    {
		    int i=x-1;
		    while(i>=s.first)
		   {
			   if(s.A[i+10000]==1)
			   {
				   s.P[x+10000]=i;
				   s.N[x+10000]=s.N[i+10000];
				   s.N[i+10000]=x;
				   s.P[(s.N[x+10000])+10000]=x;
                                 
			   }
			   i=i-1;
		   } 
		    s.size=s.size+1;

	    
       
       }
    }
    }
 
    
    return s;
}

// output : set after remeoval of x from s
// postcondition : search(x,s) should return found as 0

Set rmv(int x,Set s)
{
    SearchResult r = _search(x,s);
    if(r.found == 1)
    {
        // index of value x in array 
	if(s.first < x  && s.last>x)
	{

	
	    s.A[x+10000]=0;
	    s.P[(s.N[x+10000])+10000]=s.P[x+10000];
	    s.N[(s.P[x+10000])+10000]=s.N[x+10000];
	    s.P[x+10000]=0;
	    s.N[x+10000]=0;
	    s.size=s.size-1;
        }
	else if(x==s.first)
	{     s.A[x+10000]=0;
	      s.P[(s.N[x+10000])+10000]= s.N[x+10000];
	      s.first=s.N[x+10000];
	      s.N[x+10000]=0;
	      s.P[x+10000]=0;
	      s.size=s.size-1;
	}
	else if(x==s.last)
	{       
		s.A[x+10000]=0;
		s.N[(s.P[x+10000])+10000]=s.P[x+10000];
		s.last=s.P[x+10000];
		s.size=s.size-1;

	}
    
    }

    return s;
}

// output : 1 if set is empty otherwise 0
int isEmpty(Set s)
{
    int k = 1;
    if(len(s) == 0) 
        k = 0;
    return k;
}

// output : r, r.found == 1 if element is there in set
//         otherwise 0
SearchResult search(int x,Set s)
{
    SearchResult r;
    r.found = 0;
   // SearchResult idx = _search(x,s);
    if(s.A[x+10000] == 1) 
    {
        r.found = 1;
        r.val = x;
    }
    return r;
}

// next element of x when all elements of set 
// are put in non-decreasing order
// output : r, r.found will be 1 if x exists and has next element
//          otherwise 0
int next(int x,Set s)
{  SearchResult r= _search(x,s);
     int nxt = s.last;
     if(r.found==1){	
	if(x != s.last)
        {
		nxt=s.N[x+10000];
	}
     }	
	return nxt;
}       
// previous element of x when all elements of set 
// are put in non-decreasing order
// output : r, r.found will be 1 if x exists and has previous element
//          otherwise 0
int prev(int x , Set s){
	SearchResult r = _search(x,s);
	int previous = s.first;
      	if(r.found == 1){
	if(x != s.first ){
	
		previous = s.P[x+10000];
	}
	}
     return previous;
}


// first element of s when all elements of s are put in order
// output : r.found will be 1 if minimum is there otherwise 0
int first(Set s) {
    return s.first;
}

int last(Set s){
   return s.last;
}


//END of Set Methods
//---------------------------------------------------

// output : set with no items in it
// postcondition : len(s) == 0
Set _buildEmptySet() {
    Set s;
    s.size = 0;
    return s;
}

// precondition : s.size >= 0
// output : r
// postcondition : if x is in s then r.found == 1 
//                 and r.val = index of x in array
//                 otherwise r.found == 0
SearchResult _search(int x, Set s) {
    SearchResult r;
    r.found = 0;

        if(s.A[(x+10000)] == 1) {
            r.found = 1;
            r.val = x; // postion of that element in array
        }
      
    return r;
}

//END of Internal methods
//---------------------------------------------------


int main(void) {
  
  // use the methods  

  return 0;
}
