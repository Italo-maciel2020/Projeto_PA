#include "sculptor.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

using namespace std;

//Construtor da classe
Sculptor::Sculptor(int _nx, int _ny, int _nz){

  int i,j,k;

  nx = _nx;
  ny = _ny;
  nz = _nz;

  //Aloca a matriz 3D (Voxel);
  v = new Voxel**[nx];
  for(i=0;i<_nx;i++){
    v[i] = new Voxel*[ny];
    for(j=0;j<_ny;j++){
      v[i][j] = new Voxel[nz];
    }
  }
  for(i=0; i<_nx; i++){
    for(j=0; j<_ny; j++){
      for(k=0; k<_nz; k++){
        v[i][j][k].isOn = false;
      }
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
  this->r = r;
  this->g = g;
  this->b = b;
  a = alpha;
}

void Sculptor::putVoxel(int x, int y, int z)
{
  v[x][y][z].isOn = true;
  v[x][y][z].r = r;
  v[x][y][z].g = g;
  v[x][y][z].b = b;
  v[x][y][z].a = a;
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
  ofstream f_out;
  f_out.open(nome);
  cout<<"Entrou\n";

  if(! f_out.is_open())
  {
    cout << "Falha ao criar arquivo\n";
  }
  else
    cout << "Arquivo criado!\n";

  int totalDeElementos;
  totalDeElementos = 0;
  std::cout << "total = " << totalDeElementos << "\n";

  for(int i = 0; i<nx; i++) {
    for(int j = 0; j<ny; j++) {
      for(int k = 0; k<nz; k++)   {
        if(v[i][j][k].isOn == true)
        {
          totalDeElementos++;
          std::cout << "total = " << totalDeElementos << "\n";
        }
      }
    }
  }
  std::cout << "total = " << totalDeElementos << "\n";
  f_out << "OFF\n";
  f_out << (totalDeElementos*8) << " " << totalDeElementos*6 << " 0\n";

  std::cout << "OFF\n";
  std::cout << (totalDeElementos*8) << " " << totalDeElementos*6 << " 0\n";

  for(int i = 0; i<nx; i++)
  {
    for(int j = 0; j<ny; j++)
    {
      for(int k = 0; k<nz; k++)
      {
        if(v[i][j][k].isOn == true)
        {
          f_out << k-0.5 <<  " " << j+0.5 <<  " " << i-0.5 <<  "\n";
          f_out << k-0.5 <<  " " << j-0.5 <<  " " << i-0.5 <<  "\n";
          f_out << k+0.5 <<  " " << j-0.5 <<  " " << i-0.5 <<  "\n";
          f_out << k+0.5 <<  " " << j+0.5 <<  " " << i-0.5 <<  "\n";
          f_out << k-0.5 <<  " " << j+0.5 <<  " " << i+0.5 <<  "\n";
          f_out << k-0.5 <<  " " << j-0.5 <<  " " << i+0.5 <<  "\n";
          f_out << k+0.5 <<  " " << j-0.5 <<  " " << i+0.5 <<  "\n";
          f_out << k+0.5 <<  " " << j+0.5 <<  " " << i+0.5 <<  "\n";
        }
      }
    }
  }
  int cont = 0;
  for(int i = 0; i<nx; i++)
  {
    for(int j = 0; j<ny; j++)
    {
      for(int k = 0; k<nz; k++)
      {
        if(v[i][j][k].isOn == true)
        {
          int pos = 8*cont;
          f_out <<"4 " << pos << " " << pos+3 <<  " " << pos+2 <<  " " << pos+1 <<  " " << v[i][j][k].r <<  " " << v[i][j][k].g <<  " " << v[i][j][k].b <<  " " << v[i][j][k].a <<  "\n";
          f_out <<"4 " << pos+4 << " " << pos+5 <<  " " << pos+6 <<  " " << pos+7 <<  " " << v[i][j][k].r <<  " " << v[i][j][k].g <<  " " << v[i][j][k].b <<  " " << v[i][j][k].a <<  "\n";
          f_out <<"4 " << pos << " " << pos+1 <<  " " << pos+5 <<  " " << pos+4 <<  " " << v[i][j][k].r <<  " " << v[i][j][k].g <<  " " << v[i][j][k].b <<  " " << v[i][j][k].a <<  "\n";
          f_out <<"4 " << pos << " " << pos+4 <<  " " << pos+7 <<  " " << pos+3 <<  " " << v[i][j][k].r <<  " " << v[i][j][k].g <<  " " << v[i][j][k].b <<  " " << v[i][j][k].a <<  "\n";
          f_out <<"4 " << pos+3 <<  " " << pos+7 <<  " " << pos+6 <<  " " << pos+2 <<  " " << v[i][j][k].r <<  " " << v[i][j][k].g <<  " " << v[i][j][k].b <<  " " << v[i][j][k].a <<  "\n";
          f_out <<"4 " << pos+1 <<  " " << pos+2 <<  " " << pos+6 <<  " " << pos+5 <<  " " << v[i][j][k].r <<  " " << v[i][j][k].g <<  " " << v[i][j][k].b <<  " " << v[i][j][k].a <<  "\n";
          cont++;
        }
      }
    }
  }
  f_out.close();
}
