#include "stdafx.h"
#include <windows.h>
#include <iostream.h>

typedef struct{
	float x,y,z;
}svector;

typedef struct{
	int  x,y,z;
}ivector;

class CFVector{

  public:
      float x,y,z;
      CFVector() { x=0;y=0;z=0; };
	  
	  void out(){ 
                CString s;
		s.Format("x= %2.2f y= %2.2f z= %2.2f",x,y,z);
		AfxMessageBox(s); 
	  }
			
      friend CFVector operator +(CFVector& t1,CFVector& t2){
		  CFVector a;
		  a.x=t1.x+t2.x;
		  a.y=t1.y+t2.y;
		  a.z=t1.z+t2.z;
		  return a;
	  }

	  friend CFVector operator -(CFVector& t1,CFVector& t2){
		  CFVector a;
		  a.x=t1.x-t2.x;
		  a.y=t1.y-t2.y;
		  a.z=t1.z-t2.z;
		  return a;
	  }


      friend CFVector operator *(float& f,CFVector& t1){
		  CFVector a;
		  a.x=f*t1.x;
		  a.y=f*t1.y;
		  a.z=f*t1.z;
		  return a;
	  }
	
	  friend float operator *(CFVector& t1,CFVector& t2){
		  float a;
		  a=t1.x*t2.x+t1.y*t2.y+t1.z*t2.z;
		  return a;
	  }


};

class CIVector{

  public:
      int x,y,z;
      CIVector() { x=0;y=0;z=0; };
	  
	  void out(){ 
	        CString s;
		s.Format("x= %4d y= %4d z= %4d",x,y,z);
		AfxMessageBox(s); 
	  }
			
      friend CIVector operator +(CIVector& t1,CIVector& t2){
		  CIVector a;
		  a.x=t1.x+t2.x;
		  a.y=t1.y+t2.y;
		  a.z=t1.z+t2.z;
		  return a;
	  }

	  friend CIVector operator -(CIVector& t1,CIVector& t2){
		  CIVector a;
		  a.x=t1.x-t2.x;
		  a.y=t1.y-t2.y;
		  a.z=t1.z-t2.z;
		  return a;
	  }


      friend CIVector operator *(float& f,CIVector& t1){
		  CIVector a;
		  a.x=f*t1.x;
		  a.y=f*t1.y;
		  a.z=f*t1.z;
		  return a;
	  }
	
	  friend int operator *(CIVector& t1,CIVector& t2){
		  int a;
		  a=t1.x*t2.x+t1.y*t2.y+t1.z*t2.z;
		  return a;
	  }

};


