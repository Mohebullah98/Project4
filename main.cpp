#include <iostream>
#include<fstream>
#include<cmath>
using namespace std;
class image{
  public:
  int numImgRows;
  int numImgCols;
  int imgMin;
  int imgMax;
  int numStructRows;
  int numStructCols;
  int structMin;
  int structMax;
  int rowOrigin;
  int colOrigin;
  int rowFrameSize;
  int colFrameSize;
  int extraRows;
  int extraCols;
  int ** zeroFramedAry;
  int ** morphAry;
  int ** structAry;
  int ** morph2Ary;
  int ** morph3Ary;

  void loadImg(ifstream & imgFile, int ** zeroFramedArray){
    for(int i=rowOrigin;i<numImgRows+rowOrigin;i++){
      for(int j=colOrigin;j<numImgCols+colOrigin;j++){
        imgFile>>zeroFramedArray[i][j];
      }
    }
  }
  void loadStruct(ifstream& structFile, int ** structAry){
    for(int i=0;i<numStructRows;i++){
      for(int j=0;j<numStructCols;j++){
        structFile>>structAry[i][j];
      }
    }
  }
  void zero2dArray(int ** Ary,int rows, int cols){
    for(int i=0;i<rows;i++){
      for(int j=0;j<cols;j++){
        Ary[i][j] =0;
      }
    }
  }
  void computeDilation(){
    for( int i=rowOrigin;i<numImgRows+rowOrigin;i++){
      for(int j=colOrigin;j<numImgCols+colOrigin;j++){
        if (zeroFramedAry[i][j]>0) dilation(i,j);     
         }
    }
  }
  void computeErosion(){
    for( int i=rowOrigin;i<numImgRows+rowOrigin;i++){
      for(int j=colOrigin;j<numImgCols+colOrigin;j++){
        if (zeroFramedAry[i][j]>0) erosion(i,j);     
         }
    }
  }
  void computeOpening(){
   opening();
      }
  
  void computeClosing(){
     closing();
       }
    
  
  void dilation(int i, int j){
    int count = 0;
    int count2=0;
    for(int a=i-rowOrigin;a<i+(numStructRows-rowOrigin);a++){
      for(int b=j-colOrigin;b<j+(numStructCols-colOrigin);b++){
        if (structAry[count][count2]==1) {
          morphAry[a][b] = structAry[count][count2];
           morph3Ary[a][b] = structAry[count][count2];
        }
        count2++;
        }
        count2 = 0;
        count++;

    }
  }
  void erosion(int i, int j){
    int count=0;
    int count2=0;
    int sweep=0;
    for(int a=i-rowOrigin;a<i+(numStructRows-rowOrigin);a++){
      for(int b= j-colOrigin;b<j+(numStructCols-colOrigin);b++){
        if(structAry[count][count2]==1 && zeroFramedAry[a][b]==0){ 
          morphAry[i][j] = 0;
          morph2Ary[i][j] =0;
          sweep =1;
          break;  
        }         
        count2++;
      }
      count2=0;
      count++;
    }
    if (sweep ==0){
     morphAry[i][j] = zeroFramedAry[i][j];
     morph2Ary[i][j] = zeroFramedAry[i][j];
    }
  }
  void erosion2(int i, int j){
    int count=0;
    int count2=0;
    int sweep=0;
    for(int a=i-rowOrigin;a<i+(numStructRows-rowOrigin);a++){
      for(int b= j-colOrigin;b<j+(numStructCols-colOrigin);b++){
        if(structAry[count][count2]>0 && morph3Ary[a][b]==0){ 
          morphAry[i][j] = 0;
          morph2Ary[i][j] =0;
          sweep =1;
          break;
          
        }        
        
        count2++;
      }
      count2=0;
      count++;
    }
    if (sweep ==0){
     morphAry[i][j] = morph3Ary[i][j];
     morph2Ary[i][j] = morph3Ary[i][j];
    }

  }

  void opening(){
    for( int i=rowOrigin;i<numImgRows+rowOrigin;i++){
      for(int j=colOrigin;j<numImgCols+colOrigin;j++){
        if (zeroFramedAry[i][j]>0) erosion(i,j);     
         }
    }
    for( int a=rowOrigin;a<numImgRows+rowOrigin;a++){
      for(int b=colOrigin;b<numImgCols+colOrigin;b++){
        if (morph2Ary[a][b]>0) dilation(a,b);     
         }
    }
  }
  void closing(){
    for( int a=rowOrigin;a<numImgRows+rowOrigin;a++){
      for(int b=colOrigin;b<numImgCols+colOrigin;b++){
        if (zeroFramedAry[a][b]>0) dilation(a,b);     
         }
    }
    for( int i=rowOrigin;i<numImgRows+rowOrigin;i++){
      for(int j=colOrigin;j<numImgCols+colOrigin;j++){
        if (morph3Ary[i][j]>0) erosion2(i,j);     
         }
    }

  }

  void aryToFile(int ** Ary, ofstream & outFile){
    outFile<<numImgRows<<" "<<numImgCols<<" "<<imgMin<<" "<<imgMax<<endl;
     for(int i=rowOrigin;i<numImgRows+rowOrigin;i++){
      for(int j=colOrigin;j<numImgCols+colOrigin;j++){
        outFile<<Ary[i][j]<<" ";

        }
      outFile<<endl;
     }
  }
  void prettyPrint(int **Ary, ofstream& outFile,int rows, int cols){
    
  for(int i=rowOrigin;i<rows;i++){
      for(int j=colOrigin;j<cols;j++){
        if(Ary[i][j]==0) outFile<<"."<< " ";
        else outFile<<Ary[i][j]<<" ";

        }
      outFile<<endl;
     }
     outFile<<endl;
    }


void prettyPrint2(int **Ary, ofstream& outFile,int rows, int cols){
    
  for(int i=0;i<rows;i++){
      for(int j=0;j<cols;j++){
        if(Ary[i][j]==0) outFile<<"."<< " ";
        else outFile<<Ary[i][j]<<" ";

        }
      outFile<<endl;
     }
     outFile<<endl;
    }

};

int main(int argc, char* argv[]) {
  ifstream imgFile;
  ifstream structFile;
  imgFile.open(argv[1]);
  structFile.open(argv[2]);
  ofstream dilateOutFile;
  ofstream erodeOutFile;
  ofstream openingOutFile;
  ofstream closingOutFile;
  ofstream prettyPrintFile;
  dilateOutFile.open(argv[3]);
  erodeOutFile.open(argv[4]);
  openingOutFile.open(argv[5]);
  closingOutFile.open(argv[6]);
  prettyPrintFile.open(argv[7]);
  image im;

  imgFile>>im.numImgRows>>im.numImgCols>>im.imgMin>>im.imgMax;
  structFile>>im.numStructRows>>im.numStructCols>>im.structMin>>im.structMax;
  structFile>>im.rowOrigin>>im.colOrigin;

  im.rowFrameSize = im.numStructRows/2;
  im.colFrameSize = im.numStructCols/2;
  im.extraRows = im.rowFrameSize*2;
  im.extraCols = im.colFrameSize*2;
  
  im.zeroFramedAry = new int * [im.numImgRows+im.extraRows]();
  im.morphAry = new int * [im.numImgRows+im.extraRows]();
  im.morph2Ary = new int * [im.numImgRows+im.extraRows]();
  im.morph3Ary = new int * [im.numImgRows+im.extraRows]();
  for(int i=0;i<im.numImgRows+im.extraRows;i++){
    im.zeroFramedAry[i] = new int [im.numImgCols + im.extraCols]();
    im.morphAry[i] = new int [im.numImgCols+im.extraCols]();
    im.morph2Ary[i] = new int [im.numImgCols+im.extraCols]();
     im.morph3Ary[i] = new int [im.numImgCols+im.extraCols]();
  }
  im.structAry = new int * [im.numStructRows]();
  for(int i=0;i < im.numStructRows;i++){
    im.structAry[i] = new int [im.numStructCols]();
  }
  im.zero2dArray(im.zeroFramedAry,im.numImgRows+im.extraRows,im.numImgCols+im.extraCols);
  

  im.loadImg(imgFile,im.zeroFramedAry);
  im.prettyPrint(im.zeroFramedAry, prettyPrintFile, im.numImgRows+im.rowOrigin,im.numImgCols+im.colOrigin);
  im.zero2dArray(im.morph2Ary,im.numImgRows+im.extraRows,im.numImgCols+im.extraCols);
  im.zero2dArray(im.morphAry,im.numImgRows+im.extraRows,im.numImgCols+im.extraCols);
  im.loadStruct(structFile,im.structAry);
  im.prettyPrint2(im.structAry,prettyPrintFile, im.numStructRows,im.numStructCols);
  

  im.zero2dArray(im.morphAry,im.numImgRows+im.extraRows,im.numImgCols+im.extraCols);
  im.computeDilation();
  im.aryToFile(im.morphAry,dilateOutFile);
  im.prettyPrint(im.morphAry,prettyPrintFile,im.numImgRows+im.rowOrigin,im.numImgCols+im.colOrigin);

  im.zero2dArray(im.morphAry,im.numImgRows+im.extraRows,im.numImgCols+im.extraCols);
  im.computeErosion();
  im.aryToFile(im.morphAry, erodeOutFile);
  im.prettyPrint(im.morphAry,prettyPrintFile,im.numImgRows+im.rowOrigin,im.numImgCols+im.colOrigin);

  im.zero2dArray(im.morphAry,im.numImgRows+im.extraRows,im.numImgCols+im.extraCols);
  im.computeOpening();
  im.aryToFile(im.morphAry,openingOutFile);
  im.prettyPrint(im.morphAry,prettyPrintFile,im.numImgRows+im.rowOrigin,im.numImgCols+im.colOrigin);

  im.zero2dArray(im.morphAry,im.numImgRows+im.extraRows,im.numImgCols+im.extraCols);
  im.zero2dArray(im.morph3Ary,im.numImgRows+im.extraRows,im.numImgCols+im.extraCols);
  im.computeClosing();
  im.aryToFile(im.morphAry, closingOutFile);
  im.prettyPrint(im.morphAry, prettyPrintFile,im.numImgRows+im.rowOrigin,im.numImgCols+im.colOrigin);

  imgFile.close();
  structFile.close();
  dilateOutFile.close();
  erodeOutFile.close();
  openingOutFile.close();
  closingOutFile.close();
  prettyPrintFile.close();
  
  
  
}