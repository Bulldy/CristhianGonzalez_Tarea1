#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "omp.h"
#define N 64
#define b 1.0
#define dt 0.005
#define PI 3.14159265358979323846

double xn0(int n);
double F(double *xi,int n);
double Ek(double *xnt, double *vnt, int k, int Nobs);

int main(int argc, char **argv){
  clock_t begin = clock();

  int proc;
  proc=atoi(argv[1]);
  omp_set_num_threads(proc);

  double T;
  T=5*pow(N,2);

  int Np,Nt;
  Np=N;
  Nt=T/dt;
  double *pos1,*pos2,*vel1,*vel2;
  pos1=malloc(Np*sizeof(double));
  pos2=malloc(Np*sizeof(double));
  vel1=malloc(Np*sizeof(double));
  vel2=malloc(Np*sizeof(double));

  int i,n;
#pragma omp parallel for shared(pos1,vel1)
  for(n=0;n<Np;n++){
    pos1[n]=xn0(n);
    vel1[n]=0;
  }


  int i_file;
  i_file=Nt/1000;

  pos2[0]=0;
  pos2[Np-1]=0;
  vel2[0]=0;
  vel2[Np-1]=0;

  FILE *file1;
  char buf[10];
  sprintf(buf,"proc%d.txt",proc);
  file1=fopen(buf,"w");

  double v12;
  for(i=0;i<Nt;i++){
#pragma omp parallel for shared(pos1,pos2,vel1) private(v12)
    for(n=1;n<Np-1;n++){
      v12=vel1[n]+0.5*dt*F(pos1,n);
      pos2[n]=pos1[n]+dt*v12;
    }

#pragma omp parallel for shared(pos1,pos2,vel1,vel2) private(v12)
    for(n=1;n<Np-1;n++){
      v12=vel1[n]+0.5*dt*F(pos1,n);
      vel2[n]=v12+0.5*dt*F(pos2,n);
    }

    if(i%i_file==0){
      double E1,E2,E3;
      E1=Ek(pos1,vel1,1,Np);
      E2=Ek(pos1,vel1,2,Np);
      E3=Ek(pos1,vel1,3,Np);
      fprintf(file1,"%f %f %f \n",E1,E2,E3);
    }

#pragma omp parallel for shared(pos1,pos2,vel1,vel2)
    for(n=1;n<Np-1;n++){
      pos1[n]=pos2[n];
      vel1[n]=vel2[n];
    }
  }
  fclose(file1);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  FILE *file_time;
  char baf[10];
  sprintf(baf,"time%d.txt",proc);
  file_time=fopen(baf,"w");
  fprintf(file_time,"%f \n",time_spent);
  fclose(file_time);

  return 0;
}



double xn0(int n){
  double arg,xi;
  arg=PI*n/(N-1);
  xi=sin(arg);
  return xi;
}

double F(double *xi,int n){
  double Fn;
  Fn=(xi[n+1]-2*xi[n]+xi[n-1])+b*(pow(xi[n+1]-xi[n],2)-pow(xi[n]-xi[n-1],2));
  return Fn;
}

double Ek(double *xnt, double *vnt, int k, int Nobs){
  int j;
  double Ak, Akp,wk2,Ekk;
  Ak=0;
  Akp=0;
  wk2=4*sin(k*PI/(2*Nobs+2))*sin(k*PI/(2*Nobs+2));
#pragma omp parallel for shared(Ak,Akp,Nobs)
  for(j=0;j<Nobs;j++){
    Ak+=sqrt((2.0/(Nobs+1)))*xnt[j]*sin(j*k*PI/(Nobs+1));
    Akp+=sqrt((2.0/(Nobs+1)))*vnt[j]*sin(j*k*PI/(Nobs+1));
  }
  Ekk=0.5*(pow(Akp,2)+wk2*pow(Ak,2));
  return Ekk;
}
