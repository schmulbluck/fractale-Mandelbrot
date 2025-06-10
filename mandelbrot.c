#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "dessin.h"
#include "mandelbrot.h"

void sauvegarder(const char *fichier, bool **img, int h, int l){
    FILE *file;
    int val;
    
    // ce qui suit sera vu plus tard dans l'année
    file = fopen("toto.ppm", "w");
    fprintf(file, "P3\n%d %d\n%d\n", l, h, 1);
    for(int j=0; j<h; j++){
        for(int i=0; i<l; i++){
            val = img[i][j] ? 0 : 1;
            fprintf(file, "%d %d %d ", val, val, val);
        }
        fprintf(file, "\n");
    }    
    fclose(file);
        
    // ce qui suit est complètement hors programme
    if(fork()==0){
        execl("/usr/bin/convert", "convert", "toto.ppm", fichier, NULL);
    }
    wait(NULL);
}

void point_suivant(double x, double y, double xc, double yc, double* x1, double* y1){
  *x1=x*x-y*y+xc;
  *y1=2*x*y+yc;
}


double norme_carre(double x, double y){
  return x*x+y*y;
}

bool suite_bornee(double xc, double yc){
  bool bornee = true ;
  double x=0; double y=0;
  for (int i=0; i<100; i=i+1){
    if (norme_carre(x,y)>=4){
      bornee = false;
    }
    point_suivant(x,y,xc,yc,&x,&y);
  }
  return bornee;
}

bool** mandelbrot(double l, double h){
  bool** mandel=(bool**)malloc(l*sizeof(bool*));
  for (int i=0; i<l; i=i+1){
    mandel[i]=(bool*)malloc(h*sizeof(bool));
  }
  
  for (int x=0 ;x<l/2; x=x+1){
    for (int y=0; y<h/2; y=y+1){
      mandel[x][y]=suite_bornee((0.5)-(x*2/l),(1)-(y*2/h));
    }
    for (int y=h/2; y<h; y=y+1){
      mandel[x][y]=suite_bornee((0.5)-(x*2/l),(-1)+(y*2/h));
    }
  }
  for (int x=l/2 ;x<l; x=x+1){
    for (int y=0; y<h/2; y=y+1){
      mandel[x][y]=suite_bornee((0.5)-(x*2/l),(1)-(y*2/h));
    }
    for (int y=h/2; y<h; y=y+1){
      mandel[x][y]=suite_bornee(0.5-(x*2/l),(-1)+(y*2/h));
    }
  }
  return mandel;
}

void main(){
  sauvegarder("image.png", mandelbrot(500,500), 500,500);
}

