#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "typeinfo"
#include <sstream>
#include <cmath>
#include "mpi.h"

#define COMB_POSIBLES 32
#define NUMEQUIPO 16
#define ENFRENTAMIENTOS (NUMEQUIPO - 1)
#define PARTIDOSXFECHA (NUMEQUIPO / 2)
#define MATRIX ((NUMEQUIPO * NUMEQUIPO) - NUMEQUIPO)

using namespace std;

    float distancia(float xx1, float yy1, float xx2, float yy2)
    {
      return sqrt(((xx2 - xx1) * (xx2 - xx1))+((yy2 - yy1) * (yy2 - yy1)));
    }

    int jugaron(int realizados[ENFRENTAMIENTOS][PARTIDOSXFECHA][2], int l, int v)
    {
      int fi, fj;
      int resp = 0;
      
      for(fi=0; fi<=PARTIDOSXFECHA; fi++)
      {
	for(fj=0; fj<PARTIDOSXFECHA; fj++)
	{
	  // cout << "F: " << fi << " - P: " << fj << " ::: " << l << "==" << realizados[fi][fj][0] << "&&" << v << "==" << realizados[fi][fj][1] << "||" << l << "==" << realizados[fi][fj][1] << "&&" << v << "==" << realizados[fi][fj][0] << endl;
	  if((l == realizados[fi][fj][0] && v == realizados[fi][fj][1]) || (l == realizados[fi][fj][1] && v == realizados[fi][fj][0]))
	  {
	    resp = 1;
	  }
	}
      }  
      
      return resp;
    }
      
    int jugaronEnFecha(int realizados[PARTIDOSXFECHA][2], int l, int v)
    {
      int fj;
      int resp = 0;   

      for(fj=0; fj<PARTIDOSXFECHA; fj++)
      {
	//cout << l << " o " << v << " == " << realizados[fj][0] << " o " << realizados[fj][1] << endl;
	if(l == realizados[fj][0] || l == realizados[fj][1] || v == realizados[fj][1] || v == realizados[fj][0])
	{
	  resp = 1;
	}
	//cout << "resp: " << resp << endl;
      }
      
      return resp;
    }   
    
int main(int argc, char *argv[] )
{ 
      MPI_Status estado;
      int rank,num_procs;

      MPI_Init(&argc, &argv); // Inicializamos la comunicacion de los procesos
      MPI_Comm_size(MPI_COMM_WORLD, &num_procs);	// Número de procesos
      MPI_Comm_rank(MPI_COMM_WORLD, &rank);		// Número proceso 
  
	fstream fichero; 
	ofstream salida;
	char linea[150]; 
	char separador = ';';
	int cont = 0;
	int i,j,k,n,l;
	int juega = 0;
	int juegaFecha = 0;
	int controlAsig = 0;	
	
	float puntos[3][NUMEQUIPO]; 
	int combinaciones[MATRIX][2];
	int fechas[ENFRENTAMIENTOS][PARTIDOSXFECHA][2];
	int fechasneg[ENFRENTAMIENTOS][PARTIDOSXFECHA][2]; 	    
	int temp[ENFRENTAMIENTOS][PARTIDOSXFECHA];
	int temp2[ENFRENTAMIENTOS][PARTIDOSXFECHA];	
	
	// HAGO LECTURA DE LOS FICHEROS EN EL PROCESO "0"
	if(rank == 0)
	{
	      // Abro para lectura 
	      fichero.open("datos2.csv", ios::in); 
	      // fichero >> linea;           // Leo una primera linea 	  
	      
	      salida.open("salidaPara.csv");
	      salida << "FECHA" << ";" << "PARTIDO" << ";" <<  "LOCAL" << ";" << "VISITA" << endl;
	      
	      if(fichero.fail())
	      cerr << "Error al abrir el archivo dato.csv" << endl;
	      else
	      while(!fichero.eof())
	      {
		  fichero.getline(linea, sizeof(linea));
		  //cout << linea << endl;
		  
		  std::stringstream sst;
		  sst.str (linea);
		  std::string s = sst.str();
		  //std::cout << "s: "  << s << '\n';	    
		  std::size_t pos = s.find(separador);  
		  //std::cout << "pos: "  << pos << '\n';	  
		  
		  std::string cad1 = s.substr(0,pos);
		  //std::cout << "cad1: " << cad1 << '\n'; 	
		  stringstream geekequipo(cad1);
		  char cadequipo = 0;
		  geekequipo >> cadequipo;	    

		  std::string s2 = s.substr(pos+1); 
		  //std::cout << "s2: "  << s2 << '\n';      
		  std::size_t pos2 = s2.find(separador);   
		  //std::cout << "pos2: "  << pos2 << '\n'; 
		  
		  std::string cad2 = s2.substr(0,pos2);
		  //std::cout << "cad2: " << cad2 << '\n';  	
		  stringstream geekestadio(cad2);
		  char cadestadio = 0;
		  geekestadio >> cadestadio;	    

		  std::string s3 = s2.substr(pos2+1); 
		  // std::cout << "s2: "  << s2 << '\n';      
		  std::size_t pos3 = s3.find(separador);   
		  // std::cout << "pos3: "  << pos3 << '\n'; 
		  
		  std::string cad3 = s3.substr(0,pos3);
		  //std::cout << "cad3: " << cad3 << '\n';  
		  stringstream geekx(cad3);
		  float cadx = 0;
		  geekx >> cadx;		    

		  std::string s4 = s3.substr(pos3+1); 
		  // std::cout << "s3: "  << s3 << '\n';      
		  std::size_t pos4 = s4.find(separador);   
		  // std::cout << "pos4: "  << pos4 << '\n'; 
		  
		  std::string cad4 = s4.substr(0,pos4);
		  //std::cout << "cad4: " << cad4 << '\n';  
		  stringstream geeky(cad4);
		  float cady = 0;
		  geeky >> cady;	 
		  
		  puntos[0][cont] = cadx;
		  puntos[1][cont] = cady;
		  
		  // Donde estoy
		  puntos[2][cont] = cont;
		  
		  cont++;
	      }
	      
	      
	
	      
	      cont = 0;
	      for(i=0; i<NUMEQUIPO; i++)
	      {
		for(j=0; j<NUMEQUIPO; j++)
		{
		  if(i != j)
		  {
		    combinaciones[cont][0]= i;
		    combinaciones[cont][1]= j;
		    
		    cont++;
		  }
		}   
	      }
	      
	      
      /*      
	      for(i=0; i<MATRIX; i++)
	      {
		cout << "LOCAL: " << combinaciones[i][0] << endl;
		cout << "VISITA: " << combinaciones[i][1] << endl; 
		cout << endl; 
	      }
      */     


	      
	      for(i=0; i<ENFRENTAMIENTOS; i++)
	      {
		for(j=0; j<PARTIDOSXFECHA; j++)
		{
		    fechas[i][j][0] = -1;
		    fechas[i][j][1] = -1;
		}   
	      } 	
	      
	    
	    for(i=0; i<ENFRENTAMIENTOS; i++)
	    {
	      //cout << " I: " << i << endl;
		  
	      for(j=0; j<PARTIDOSXFECHA; j++)
	      {
		//cout << " J: " << j << endl;
		  
		controlAsig = 0;
		for(n=0; n<MATRIX; n++)
		{
		  //cout << " N: " << n << endl << endl;
		  
		  juega = jugaron(fechas, combinaciones[n][0], combinaciones[n][1]);
		  juegaFecha = jugaronEnFecha(fechas[i], combinaciones[n][0], combinaciones[n][1]);

		  //cout << "F: " << i << " - P: " << j << " -- LOCAL: " << combinaciones[n][0] << " || VISITA: " << combinaciones[n][1] << " - J: " << juega << endl;
		  //cout << "F: " << i << " - P: " << j << " -- LOCAL: " << combinaciones[n][0] << " || VISITA: " << combinaciones[n][1] << " - JF: " << juegaFecha << endl;
		  
		  if(juega == 0 && juegaFecha == 0 && controlAsig == 0)
		  {
		    fechas[i][j][0] = combinaciones[n][0];
		    fechas[i][j][1] = combinaciones[n][1];	  
		    controlAsig = 1;
		    //cout << "Asigno:: F: " << i << " - P: " << j << " -- LOCAL: " << combinaciones[n][0] << " || VISITA: " << combinaciones[n][1] << endl;
		    
		  }  
		  //cout << endl << endl;
		}
	      }   
	    }	

	    
	    for(int k=0; k<ENFRENTAMIENTOS; k++)
	    {
	      for(int l=0; l<PARTIDOSXFECHA; l++)
	      {	      
		temp[k][l] = fechas[k][l][0];
		temp2[k][l] = fechas[k][l][1];
	      }
	    }
	    
	    
		// ENVÍO MENSAJE DE PROCESO "0" A LOS DEMAS PROCESOS
		for(int pr=1; pr<num_procs; pr++)
		{  		  
		  for(int k=0; k<ENFRENTAMIENTOS; k++)
		  {
		    MPI_Send(&temp[k], PARTIDOSXFECHA, MPI_INT, pr, k, MPI_COMM_WORLD);
		  }
		  
		  for(int k2=0; k2<ENFRENTAMIENTOS; k2++)
		  {
		    MPI_Send(&temp2[k2], PARTIDOSXFECHA, MPI_FLOAT, pr, ENFRENTAMIENTOS+k2, MPI_COMM_WORLD);
		  }
		  
		  for(int k3=0; k3<3; k3++)
		  {
		    MPI_Send(&puntos[k3], 3, MPI_FLOAT, pr, ENFRENTAMIENTOS+ENFRENTAMIENTOS+k3, MPI_COMM_WORLD);
		  }
		  
		}
	
	
	}
	else
	{
		  int fechas[ENFRENTAMIENTOS][PARTIDOSXFECHA][2];
		  int fechasneg[ENFRENTAMIENTOS][PARTIDOSXFECHA][2];
	  
		  for(int k=0; k<ENFRENTAMIENTOS; k++)
		  {
		    MPI_Recv(&temp[k],PARTIDOSXFECHA,MPI_INT,0,k,MPI_COMM_WORLD,&estado);
		  }
		  
		  for(int k2=0; k2<ENFRENTAMIENTOS; k2++)
		  {
		    MPI_Recv(&temp2[k2],PARTIDOSXFECHA,MPI_INT,0,ENFRENTAMIENTOS+k2,MPI_COMM_WORLD,&estado);
		  }
		  
		  for(int k3=0; k3<3; k3++)
		  {
		    MPI_Recv(&puntos[k3],PARTIDOSXFECHA,MPI_INT,0,ENFRENTAMIENTOS+ENFRENTAMIENTOS+k3,MPI_COMM_WORLD,&estado);
		  }
	  
		  for(int k=0; k<ENFRENTAMIENTOS; k++)
		  {
		    for(int l=0; l<PARTIDOSXFECHA; l++)
		    {	      
		      fechas[k][l][0] = temp[k][l];
		      fechas[k][l][1] = temp2[k][l];
		    }
		  }
	  
	
		  // DEFINO LOS MÁXIMOS Y MÍNIMOS DE CADA PROCESO PARA CÁLCULAR PERIMETROS		  
		  if(num_procs > 1)
		  {
		    l = ENFRENTAMIENTOS / (num_procs - 1);
		  }
		  else
		  {
		    l = ENFRENTAMIENTOS / num_procs;
		  }	
		
		  int min = (rank-1)*l;
		  int max;
		  
		  if(rank == (num_procs - 1))
		  {	    
		    max = ENFRENTAMIENTOS;
		  }
		  else
		  {
		    max = (rank*l)-1;
		  }	

		  int local, visita;
		  float distLocal;
		  float sumaDistLocal = 0;
		  float sumaTotalLocal = 0;
		  int dondeEstoyLocal; 
		  float distVisita;
		  float sumaDistVisita = 0;
		  float sumaTotalVisita = 0;
		  int dondeEstoyVisita;   
		  float sumaTotalFecha = 0;   
		    
		  for(i=min; i<max; i++)
		  {
		    sumaDistLocal = 0;
		    sumaDistVisita = 0;
		    
		    for(j=0; j<PARTIDOSXFECHA; j++)
		    {
		      local = fechas[i][j][0];
		      visita = fechas[i][j][1];	  
		      dondeEstoyLocal = (int)puntos[2][local];
		      dondeEstoyVisita = (int)puntos[2][visita];
		      
		     cout << "F: " << i << " - P: " << j << " -- LOCAL: " << local << " || VISITA: " << visita << endl;
		      
		      //cout << "puntos[" << local << "][" << 0 << "]: " << puntos[0][local] << endl;	
		      //cout << "puntos[" << local << "][" << 1 << "]: " << puntos[1][local] << endl;
		      //cout << "puntos[" << local << "][" << 2 << "]: " << puntos[2][local] << endl;
		      //cout << "puntos[" << visita << "][" << 0 << "]: " << puntos[0][visita] << endl;	
		      //cout << "puntos[" << visita << "][" << 1 << "]: " << puntos[1][visita] << endl;
		      //cout << "puntos[" << visita << "][" << 2 << "]: " << puntos[2][visita] << endl;	  
		      
		      
		      distLocal = distancia((float)puntos[0][dondeEstoyLocal], (float)puntos[1][dondeEstoyLocal], (float)puntos[0][visita], (float)puntos[1][visita]);
		      //cout << "distanciaLocal:" << distLocal << endl;	    
		      
		      distVisita = distancia((float)puntos[0][dondeEstoyVisita], (float)puntos[1][dondeEstoyVisita], (float)puntos[0][local], (float)puntos[1][local]);
		      //cout << "distanciaVisita:" << distVisita << endl;	  
			
		      sumaDistLocal = sumaDistLocal + distLocal;
		      //cout << "sumaDistLocal:" << sumaDistLocal << endl;	
		      
		      sumaDistVisita = sumaDistVisita + distVisita;
		      //cout << "sumaDistVisita:" << sumaDistVisita << endl;	
		      
		      puntos[2][local] = visita;
		      puntos[2][visita] = local;
		      
		      salida << (i+1) << ";" << (j+1) << ";" <<  local << ";" << visita << endl;
		    }   
		    sumaTotalLocal = sumaTotalLocal + sumaDistLocal;
		    //cout << "sumaTotalLocal:" << sumaTotalLocal << endl;	
		    
		    sumaTotalVisita = sumaTotalVisita + sumaDistVisita;
		    cout << "sumaTotalVisita:" << sumaTotalVisita << endl;	
		    
		  }	
		  
		    sumaTotalFecha = sumaTotalVisita + sumaTotalLocal;
		    cout << "sumaTotalFecha:" << sumaTotalFecha << endl;	     
	}
		
	
    fichero.close();  
    salida.close();
    
    MPI_Finalize();
    
    return 0;
}
