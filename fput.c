#include <stdio.h>
#include <stdlib.h>
//#include <mpi.h>
#include <math.h>
#include <string.h>
#define N 64
#define b 1.0
#define dt 0.005
#define PI 3.14159265358979323846

double xn0(int n);
double F(double *xi,int n);

int main(int argc, char **rgv){
  /**int rank,size, source, destination, in_number, out_number;
  MPI_Request send_request, recv_request;
  MPI_Status status;

  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);


  MPI_Finalize();**/
  int Np,Nt;
  Np=N;
  Nt=100*N;
  double *pos1,*pos2,*vel1,*vel2;
  pos1=malloc(Np*sizeof(double));
  pos2=malloc(Np*sizeof(double));
  vel1=malloc(Np*sizeof(double));
  vel2=malloc(Np*sizeof(double));

  int i,n;
  for(n=0;n<Np;n++){
    pos1[n]=xn0(n);
    vel1[n]=0;
  }

  
  double v12;
  for(i=0;i<Nt;i++){
    for(n=1;n<Np-1;n++){
      v12=vel1[n]+0.5*dt*F(pos1,n);
      pos2[n]=pos1[n]+dt*v12;
    }

    for(n=1;n<Np-1;n++){
      v12=vel1[n]+0.5*dt*F(pos1,n);
      vel2[n]=v12+0.5*dt*F(pos2,n);
    }

    for(n=1;n<Np-1;n++){
      pos1[n]=pos2[n];
      vel1[n]=vel2[n];
    }
  }

  return 0;
}

double xn0(int n){
  double arg,xi;
  arg=2*PI*n/(N-1);
  xi=sin(arg);
  return xi;
}

double F(double *xi,int n){
  double Fn;
  Fn=(xi[n+1]-2*xi[n]+xi[n-1])+b*(pow(xi[n+1]-xi[n],3)-pow(xi[n]-xi[n-1],3));
  return Fn;
}
