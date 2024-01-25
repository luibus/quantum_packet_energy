//no potential

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double V(double x){
	double f;
	f=0;
	return(f);
}
void write (int NX, int NZ, double temp[NX][NZ], int n);
int main () {
	int steps=100;
	int Tsteps=50;
	double Xmax=15;
	double Xmin=0;
	double x=Xmin;
	double deltaX=(Xmax-Xmin)/steps;
	double deltaT=pow((deltaX/2),2);
	double psr[steps][2];
	double psi[steps][2];
	double rho[steps][Tsteps-2];
	double previoaperder[steps]; //va a ser mi valor para rho mas antiguo
	double util;
	double util2;
	double sigmao=0.5;
	double k=0;//17*M_PI;
	double alfa=deltaT/pow(deltaX,2);
	printf("\n psr: %8.4f", deltaT);
	printf("\n psr: %8.4f", deltaX);
	printf("\n psr: %8.4f", alfa);
	for(int i=0;i<steps;i++){//inicializacion del packet para t=0 y t=deltaT/2
		util2=((x-Xmin)/sigmao);
		util=exp((-0.5*pow(util2,2)));

		psr[i][0]=util*cos(k*x);
		psi[i][0]=util*sin(k*x);
		x=x+deltaX;
		//printf("\n psr: %8.9f", psr[i][0]);
	}
	for(int cont=0;cont<Tsteps;cont++){

		x=Xmin;
	for(int i=1;i<steps-1;i++){//inicializacion del packet para t=0 y t=deltaT/2
		psr[i][1]=psr[i][0]+(2*alfa+V(x)*deltaT)*psi[i][0]-(alfa*(psi[i+1][0]+psi[i-1][0]));
		psi[i][1]=psr[i][0]+(2*alfa+V(x)*deltaT)*psr[i][1]-(alfa*(psr[i+1][1]+psr[i-1][1]));
		x=x+deltaX;
		printf("\n psr: %8.4f", psr[i][1]);
		if (cont>=1){
			rho[i-1][cont-1]=pow(psr[i][0],2)+(psi[i][1]*previoaperder[i]);
			rho[0][cont]=0;
			rho[steps-1][cont]=0;
		}
	}

	for(int i=0;i<steps;i++){//lo ponemos ahora como inicial
		previoaperder[i]=psi[i][0];
		psr[i][0]=psr[i][1];
		psi[i][0]=psi[i][1];
	}


	}







	write(steps,Tsteps-2,rho,0);

return(0);
}
void write (int NX,int NZ,double temp[NX][NZ], int n) {
    int i, j;
    FILE* fout;
    fout = fopen("output1_animation_temp.txt", "a");

    for (i=0; i<NX; i++) {
        for (j=0; j<NZ; j++) {
            fprintf(fout, "%.16f\t", temp[i][j]);
        }
        fprintf(fout, "\n");
    }

    fclose(fout);
}
