#include "sculptor.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

using namespace std;

//Construtor da classe
Sculptor::Sculptor(int _nx, int _ny, int _nz){

int i,j;

nx = _nx;
ny = _ny;
nz = _nz;

v = new Voxel**[nx];
for(i=0;i<_nx;i++){
   v[i] = new Voxel*[ny];
    for(j=0;j<_ny;j++){                                            //Aloca a matriz 3D (Voxel);
       v[i][j] = new Voxel[nz];
    }
}

}

//Destrutor da classe
Sculptor::~Sculptor(){
    int i,j;
    for(i=0;i<nx;i++){
     for(j=0;j<ny;j++){
         delete[] v[i][j];
    }
     delete[] v[i];
    }
    delete [] v;
 cout << "Encerrado." << endl;
}

// Construtor com argumentos - Recebe as dimensões do Voxel e as coordenadas do mesmo.
void Sculptor::setColor(float r, float g, float b, float alpha){
    int i,j,k;
    for(i=0;i<nx;i++){
        for(j=0;j<ny;j++){
            for(k=0;k<nz;k++){
               v[i][j][k].r=r;
               v[i][j][k].g=g;
               v[i][j][k].b=b;
               v[i][j][k].a=alpha;  // Chamada da função da classe Sculptor,inserir cor na matriz 3D.
            }
        }
    }
}

void Sculptor::putVoxel(int x, int y, int z)
{
    v[x][y][z].isOn = true;
}

void Sculptor::cutVoxel(int x, int y, int z){
             v[x][y][z].isOn = false;
 }

//Ativa vários vóxels dentro dos intervalos
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
   int i, j, k;
   for(i=x0; i<=x1; i++){
      for(j=y0; j<=y1; j++){
         for(k=z0; k<=z1; k++){
             putVoxel(i,j,k);
         }
      }
   }

}

//Desativa vários vóxels dentro do intervalo
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
   int i, j, k;
   for(i=x0; i<=x1; i++){
      for(j=y0; j<=y1; j++){
         for(k=z0; k<=z1; k++){
         cutVoxel(i,j,k);
         }
      }
   }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    for(int i=0; i< xcenter; i++){
        for(int j=0; j< ycenter; j++){
            for(int k=0; k< zcenter; k++){
                //equacao da esfera
                if (((i-xcenter)*(i-xcenter)) + ((j-ycenter)*(j-ycenter)) + ((k-zcenter)*(k-zcenter)) <= ((radius)*(radius))){
                    putVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
   for(int i=0; i< xcenter; i++){
           for(int j=0; j< ycenter; j++){
               for(int k=0; k< zcenter; k++){
                   //equacao da esfera
                   if (((i-xcenter)*(i-xcenter)) + ((j-ycenter)*(j-ycenter)) + ((k-zcenter)*(k-zcenter)) <= ((radius)*(radius))){
                       cutVoxel(i,j,k);
                   }
               }
           }
       }
   }


void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
   for(int i=-xcenter; i< xcenter; i++){
        for(int j=-ycenter; j< ycenter; j++){
            for(int k=-zcenter; k< zcenter; k++){
                //equacao da esfera
                if ((((i-xcenter)*(i-xcenter))/((float)((rx)*(rx)))) + ((((j-ycenter)*(j-ycenter)))/((float)((ry)*(ry)))) + ((((k-zcenter)*(k-zcenter)))/((float)((rz)*(rz)))) <=1.0){
                   putVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    for(int i=xcenter; i< xcenter; i++){
        for(int j=ycenter; j< ycenter; j++){
            for(int k=zcenter; k< zcenter; k++){
                //equacao da esfera
                if ((((i-xcenter)*(i-xcenter))/(((rx)*(rx)))) + ((((j-ycenter)*(j-ycenter)))/(((ry)*(ry)))) + ((((k-zcenter)*(k-zcenter)))/(((rz)*(rz)))) <=1.0){
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::writeOFF(char* nome){
    string tr;
    ofstream f_out;
    f_out.open(nome);
    cout<<"Entrou\n";

    if(! f_out.good())
    {
        cout << "Falha ao criar arquivo\n";
    }
    else
        cout << "Arquivo criado!\n";

    int totalDeElementos = nx*ny*nz;

    for(int i = 0; i<nz; i++)
    {
        for(int j = 0; j<ny; j++)
        {
            for(int k = 0; k<nx; k++)
            {
                if(v[i][j][k].isOn == false)
                {
                    totalDeElementos--;
                }
            }
        }
    }
    tr += "OFF\n";
    tr += to_string(totalDeElementos*8) + " " + to_string(totalDeElementos*6) + " " + "0\n";
    for(int i = 0; i<nz; i++)
    {
        for(int j = 0; j<ny; j++)
        {
            for(int k = 0; k<nx; k++)
            {
                if(v[i][j][k].isOn == true)
                {
                    tr += to_string(k-0.5) + " " + to_string(j+0.5) + " " + to_string(i-0.5) + "\n";
                    tr += to_string(k-0.5) + " " + to_string(j-0.5) + " " + to_string(i-0.5) + "\n";
                    tr += to_string(k+0.5) + " " + to_string(j-0.5) + " " + to_string(i-0.5) + "\n";
                    tr += to_string(k+0.5) + " " + to_string(j+0.5) + " " + to_string(i-0.5) + "\n";
                    tr += to_string(k-0.5) + " " + to_string(j+0.5) + " " + to_string(i+0.5) + "\n";
                    tr += to_string(k-0.5) + " " + to_string(j-0.5) + " " + to_string(i+0.5) + "\n";
                    tr += to_string(k+0.5) + " " + to_string(j-0.5) + " " + to_string(i+0.5) + "\n";
                    tr += to_string(k+0.5) + " " + to_string(j+0.5) + " " + to_string(i+0.5) + "\n";
                }
            }
        }
    }
    int cont = 0;
    for(int i = 0; i<nz; i++)
    {
        for(int j = 0; j<ny; j++)
        {
            for(int k = 0; k<nx; k++)
            {
                if(v[i][j][k].isOn == true)
                {
                    int pos = 8*cont;
                    tr += "4 " + to_string(pos) + " " + to_string(pos+3) + " " + to_string(pos+2) + " " + to_string(pos+1) + " " + to_string(v[i][j][k].r) + " " + to_string(v[i][j][k].g) + " " + to_string(v[i][j][k].b) + " " + to_string(v[i][j][k].a) + "\n";
                    tr += "4 " + to_string(pos+4) + " " + to_string(pos+5) + " " + to_string(pos+6) + " " + to_string(pos+7) + " " + to_string(v[i][j][k].r) + " " + to_string(v[i][j][k].g) + " " + to_string(v[i][j][k].b) + " " + to_string(v[i][j][k].a) + "\n";
                    tr += "4 " + to_string(pos) + " " + to_string(pos+1) + " " + to_string(pos+5) + " " + to_string(pos+4) + " " + to_string(v[i][j][k].r) + " " + to_string(v[i][j][k].g) + " " + to_string(v[i][j][k].b) + " " + to_string(v[i][j][k].a) + "\n";
                    tr += "4 " + to_string(pos) + " " + to_string(pos+4) + " " + to_string(pos+7) + " " + to_string(pos+3) + " " + to_string(v[i][j][k].r) + " " + to_string(v[i][j][k].g) + " " + to_string(v[i][j][k].b) + " " + to_string(v[i][j][k].a) + "\n";
                    tr += "4 " + to_string(pos+3) + " " + to_string(pos+7) + " " + to_string(pos+6) + " " + to_string(pos+2) + " " + to_string(v[i][j][k].r) + " " + to_string(v[i][j][k].g) + " " + to_string(v[i][j][k].b) + " " + to_string(v[i][j][k].a) + "\n";
                    tr += "4 " + to_string(pos+1) + " " + to_string(pos+2) + " " + to_string(pos+6) + " " + to_string(pos+5) + " " + to_string(v[i][j][k].r) + " " + to_string(v[i][j][k].g) + " " + to_string(v[i][j][k].b) + " " + to_string(v[i][j][k].a) + "\n";
                    cont++;
                }
            }
        }
    }
    f_out << tr;
    f_out.close();
}
