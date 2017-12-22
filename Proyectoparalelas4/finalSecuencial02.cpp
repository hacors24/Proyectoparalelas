#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "typeinfo"
#include <sstream>
#include <cmath>

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
	fstream fichero; 
	char linea[150]; 
	char separador = ';';
	int cont = 0;
	int i,j,k,n;
	int juega = 0;
	int juegaFecha = 0;
	int controlAsig = 0;	
	
	float puntos[3][NUMEQUIPO]; 

	// Abro para lectura 
	fichero.open("datos2.csv", ios::in); 
	// fichero >> linea;           // Leo una primera linea 
	
	ofstream salida;
	salida.open("salida.csv");
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
	    char cadequipo[50];
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
	
	
	int combinaciones[MATRIX][2];
	int fechas[ENFRENTAMIENTOS][PARTIDOSXFECHA][2];
	int fechasneg[ENFRENTAMIENTOS][PARTIDOSXFECHA][2]; 	
	
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
	
      for(i=0; i<ENFRENTAMIENTOS; i++)
      {
	sumaDistLocal = 0;
	sumaDistVisita = 0;
	
	for(j=0; j<PARTIDOSXFECHA; j++)
	{
	  local = fechas[i][j][0];
	  visita = fechas[i][j][1];	  
	  dondeEstoyLocal = (int)puntos[2][local];
	  dondeEstoyVisita = (int)puntos[2][visita];
	  
	 // cout << "F: " << i << " - P: " << j << " -- LOCAL: " << local << " || VISITA: " << visita << endl;
	  
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
	//cout << "sumaTotalVisita:" << sumaTotalVisita << endl;	
	
      }	
      
 	sumaTotalFecha = sumaTotalVisita + sumaTotalLocal;
	cout << "sumaTotalFecha:" << sumaTotalFecha << endl;	     
      
		
	
	for(i=0; i<ENFRENTAMIENTOS; i++)
	{
	  for(j=0; j<PARTIDOSXFECHA; j++)
	  { 
	      fechasneg[i][j][1] = fechas[i][j][0];
	      fechasneg[i][j][0] = fechas[i][j][1];
	  }   
	}

	
	
	
      sumaDistLocal = 0;
      sumaTotalLocal = 0;
      dondeEstoyLocal; 
      distVisita;
      sumaDistVisita = 0;
      sumaTotalVisita = 0;
      dondeEstoyVisita;   
      float sumaTotalFechaNeg = 0; 
      float sumaTotal = 0; 	
	
      for(i=0; i<ENFRENTAMIENTOS; i++)
      {
	sumaDistLocal = 0;
	sumaDistVisita = 0;
	
	for(j=0; j<PARTIDOSXFECHA; j++)
	{
	  local = fechasneg[i][j][0];
	  visita = fechasneg[i][j][1];	  
	  dondeEstoyLocal = (int)puntos[2][local];
	  dondeEstoyVisita = (int)puntos[2][visita];
	  
	  // cout << "F: " << i << " - P: " << j << " -- LOCAL: " << local << " || VISITA: " << visita << endl;
	  
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
	  
	  salida << (ENFRENTAMIENTOS+i+1) << ";" << (j+1) << ";" <<  local << ";" << visita << endl;
	}   
	sumaTotalLocal = sumaTotalLocal + sumaDistLocal;
	//cout << "sumaTotalLocal:" << sumaTotalLocal << endl;	
	
	sumaTotalVisita = sumaTotalVisita + sumaDistVisita;
	//cout << "sumaTotalVisita:" << sumaTotalVisita << endl;	
	
      }	
      
 	sumaTotalFechaNeg = sumaTotalVisita + sumaTotalLocal;
	cout << "sumaTotalFechaNeg:" << sumaTotalFechaNeg << endl;	

	sumaTotal = sumaTotalFecha + sumaTotalFechaNeg;
	cout << "sumaTotal:" << sumaTotal << endl;
	
    fichero.close();  
    salida.close();
    
    return 0;
}
