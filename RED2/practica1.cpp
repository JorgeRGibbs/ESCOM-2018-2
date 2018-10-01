/*
  Instituto Politecnico Nacional
  Escuela superior de computo

  Autor: Ricardo Naranjo Polit
  Email: ricardo8polit@gmail.com

*/

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
using namespace std;

#define PI 3.141592654

void * creaSociedad( void* );

double deg2rad(double valor);
void mutacion( vector< short > &hijo, int n );
void inicializa(double &valorvars,int &iteraciones,int &tamPob,int &max,int &min,int &prec);
double convierte( double valorvars, int seleccion );
int decimal( vector< short > crom );

class cromosoma{
	private:

		int aj;									//limite inferior de la variable
		int bj;									//limite superior de la variable
		int nj;									//# bits de precisi�n
		int mj;									//# de cromosomas
		vector< short > cromatida;
		double fenotipo;

	public:

		cromosoma( int a, int b, int n );
		cromosoma( vector< short > hijo, int a, int b, int n, int m );
		bool Poblar();
		void mostrar();
		double getFenotipo();
		double getDec();
		int getMJ();
		int getNJ();
		int getBJ();
		int getAJ();
		vector< short > getCroma();
};

class individuo{
	private:

		double z;
		vector< cromosoma > adn;

	public:

		individuo( vector< cromosoma > ad, double valorvars );
		individuo();
		vector< short > fucion();
		double cumple(double valorvars);
		double getZ();
		vector< cromosoma > getADN();

};

class poblacion{
	private:

		double sumZ;
		vector< double > zPor;
		vector< double > zAcum;
		vector< double > aleatorio;
		vector< int > Gan;
		vector< int > Perd;
		vector< int > cubeta;
		vector< individuo > indi;
		void sumar();
		void porcentaje();
		void acomula();
		void alea();
		int * padress;

	public:

		poblacion( vector< individuo > ind );
		void mostrarResultado( double valorvars ,int se );
		void limpiar();
		int * fuerte();
		double checador();
		vector< vector< cromosoma > > cruze(int * padres);
		vector< individuo > nueva( individuo hijo );

};



int main( ){

	int healt;
	int socNum = 6;
	int *semillas;

	pthread_t *hilos;
	semillas = (int *) malloc (socNum*sizeof(int ));
	hilos = (pthread_t *) malloc(sizeof(pthread_t)*socNum);

	for(int i = 0; i < socNum; i++){
		semillas[i] = i+10;
		healt = pthread_create(&hilos[i],NULL,creaSociedad,&semillas[i]);


		if(healt == -1){
			cout << "Error al crear el hilo: " << i << endl;
			exit(0);
		}
		//cout << "Hilo" << i <<"creado satisfactoriamente"<< endl;


	}

	for (int i = 0; i < socNum; i++) {
		pthread_join(hilos[i], NULL);
		//cout << "Join: " << i << endl;
	}

	return 0;
}

void *creaSociedad(void *a){

	int *seed = (int *) a;
	srand ((*seed));
	double valorvars;
	int max;
	int min;
	int iteraciones;
	int tamPob;
	int prec;

	//Empieza: Leer la ecuacion

	inicializa(valorvars,iteraciones,tamPob,max,min,prec);

	//Termina: Leer la ecuacion


	vector<individuo> pob;
	int contador = 0;

	for(int j = 0;j<tamPob;j++){
		vector<cromosoma> crom;

		//Empieza: Generacion de cromosoma
			cromosoma aux = cromosoma(min,max,prec);

			aux.Poblar();
			aux.mostrar();
			crom.push_back(aux);

		//Termina: Generacion de cromosoma

		//Empieza: Crea el individuo

		individuo persona = individuo(crom,valorvars);
		pob.push_back(persona);

		//Termina: Crea el individuo

		//cout << "Creando primera poblacion hilo con semilla " << (*seed) << " :" << endl;
		//cout << ++contador << "/" << tamPob << endl;
	}

	//Inicia: Crea la poblacion

	poblacion pobla = poblacion(pob);

	//Termina: Crea la poblacion

	vector<vector<cromosoma> > hijos;
	vector<cromosoma> cromHijo;
	int * fuertes;
	vector<individuo> nuevaPob;

	individuo hijo = individuo();

	int iterra = iteraciones;
	int salida;

	//Empieza: Condicion de termino

	while((iteraciones--)>0){


	//Termina: condicion de termino

		//cout << "Iteraciones: " << endl;
		//cout << iterra-iteraciones << "/" << iterra << endl;
		salida = 0;
		do{

			//Funcion especial creada para quitar traba de generaciones

			if(salida>=100){
					for(int j = 0;j<tamPob;j++){
						vector<cromosoma> crom;
						cromosoma aux = cromosoma(min,max,prec);
						aux.Poblar();
						aux.mostrar();
						crom.push_back(aux);
						individuo persona = individuo(crom,valorvars);
						nuevaPob = pobla.nueva(persona);
					}

				pobla = poblacion(nuevaPob);
				salida = 0;
			}

			//Funcion especial creada para quitar traba de generaciones


			//Empieza: Selecciona los individuos mas fuertes y debiles

			fuertes = pobla.fuerte();

			//Termina: Selecciona los individuos mas fuertes y debiles

			//Empieza: cruze

			hijos = pobla.cruze( fuertes );
			individuo hijo1 = individuo(hijos[0],valorvars);
			individuo hijo2 = individuo(hijos[1],valorvars);

			if(hijo1.getZ()>=hijo2.getZ())
				cromHijo = hijo1.getADN();
			else
				cromHijo = hijo2.getADN();

			//Termina: cruze

			//Empieza: Crea los individuos

			hijo = individuo(cromHijo,valorvars);

			//Termina: Crea los individuos

			//Empieza: Reemplaza los individuos debiles

			nuevaPob = pobla.nueva(hijo);

			//Termina: Reemplaza los individuos debiles

			salida++;
			/**/
			//cout << "Z hijo:" << hijo.getZ() << endl;
			//cout << salida << endl;
		}while((hijo.cumple(hijo.getZ()))==0);

			//Empieza: Crea la nueva poblacion

			pobla = poblacion(nuevaPob);

			//Termina: Crea la nueva poblacion
	}

	pobla.mostrarResultado(valorvars,(*seed));

	pthread_exit(NULL);
}


void inicializa(double &valorvars,int &iteraciones,int &tamPob,int &max,int &min,int &prec){

	valorvars = 0;
  iteraciones = 3;
	tamPob = 2000;
	prec = 1;
  max = 90;
	min = 0;

}


double convierte(double valorvars, int seleccion ){

	if( seleccion == 1 ){

    if(4.2 >= valorvars && 3 < valorvars)
      return 1;
    else
		  return 0;

	}else if( seleccion == 0 ){

		return (((6.75)*(6.75))*sin(2*deg2rad(valorvars)))/9.82;

	}

	return -1;
}

double deg2rad(double valor){
  return valor * PI / 180;
}

int decimal( vector< short > crom ){

	int resultado = 0;
	int tam = crom.size() - 1;

	for(int i = tam; i >= 0; i-- ){

		if( crom[ i ] )
			resultado += pow( 2, tam - i ); //Convierte los valores de bits a decimal

	}

	return resultado;
}

cromosoma::cromosoma(int a, int b, int n ){

	double aux;

	aj = a;
	bj = b,
	nj = n;
	aux = ( log10( ( bj - aj ) * pow( 10, nj ) ) ) / ( log10( 2 ) );
	mj = ceil( aux );

}

cromosoma::cromosoma(vector<short> hijo,int a,int b, int n,int m){

	cromatida = hijo;
	aj = a;
	bj = b;
	nj = n;
	mj = m;

}

int cromosoma::getNJ(){

	return nj;

}

int cromosoma::getBJ(){

	return bj;

}

int cromosoma::getAJ(){

	return aj;

}

int cromosoma::getMJ(){

	return mj;

}

vector< short > cromosoma::getCroma(){

	return cromatida;

}

void cromosoma::mostrar(){
	/*int tam = cromatida.size();

	for(int i = 0; i < tam; i++ )
		//cout << cromatida[ i ] << " ";

	//cout << endl;*/

}

bool cromosoma::Poblar(){

	cromatida.clear();

	for(int i = 0; i < mj; i++ ){

		if( rand() % 2 )				//Llena de valores aleatorios los cromosomas, aqui se insertan las semillas, se tiene que cambiar la funcion rand()
			cromatida.push_back( 1 );
		else
			cromatida.push_back( 0 );

	}

	return true;
}

double cromosoma::getDec(){

	return decimal( cromatida );

}

double cromosoma::getFenotipo(){

	fenotipo = aj + decimal( cromatida ) * ( ( bj - aj ) / ( pow( 2, mj ) - 1 ) );		//Obtiene el valor de las variables para usar en la ecuacion

	return fenotipo;
}

individuo::individuo(){

}

individuo::individuo( vector< cromosoma > ad, double valorvars ){

	adn = ad;
		valorvars = adn[ 0 ].getFenotipo();				//Guarda los valores de las variables


	z = convierte( valorvars, 0);		//Evalua la ecuacion con los valores de las variables

}


vector< cromosoma > individuo::getADN(){

	return adn;
}


//Funcion que devuelve en vector el adn completo del individuo
vector< short > individuo::fucion(){

	vector< short > adnCompleto;

	for(int i = 0; i < adn.size(); i++ ){

		vector< short > cromosomaAuxiliar = adn[ i ].getCroma();

		for(int j = 0; j < cromosomaAuxiliar.size(); j++ ){

			adnCompleto.push_back( cromosomaAuxiliar[ j ] );

		}

	}

	return adnCompleto;
}

double individuo::getZ(){

	return z;
}

//Funcion para ver si el individuo cumple con las restricciones dadas en la entrada
double individuo::cumple( double valorvars ){

	return convierte( valorvars, 1);
}

poblacion::poblacion(vector<individuo> ind){

	indi = ind;
}

void poblacion::limpiar(){

	zPor.clear();
	zAcum.clear();
	aleatorio.clear();
	Gan.clear();
	indi.clear();
	Perd.clear();
	cubeta.clear();
	sumZ = 0;

}


//Obtiene el ganador de la poblacion e imprime los valores
void poblacion::mostrarResultado( double valorvars ,int se){

	int zMaximo;
	int ganador;
	std::ofstream salida;
	vector<cromosoma> adnGanador;

	zMaximo = 0;

	//Obtiene el maximo individuo que cumpla con las restricciones

	for(int i = 0; i < indi.size(); i++ ){
		vector<cromosoma> auxADN = indi[i].getADN();
		individuo aux = individuo(auxADN,valorvars);
		if( aux.getZ() > zMaximo && (aux.cumple(aux.getZ()))==1){

			zMaximo = aux.getZ();
			ganador = i;

		}

	}

  string aut;
  std::ostringstream convert;
  convert << se-9;
  aut = convert.str();

	//Imprime los valores del maximo individuo en el archivo 'salida.txt'
	string nombreArchivo = "salida"+aut+".txt";
	individuo individuoGanador = indi[ ganador ];
	salida.open( nombreArchivo.c_str());
	salida << "Z: " << individuoGanador.getZ() << "| ";
	adnGanador = individuoGanador.getADN();

	for(int i = 0; i < adnGanador.size(); i++ ){

		salida << "| " << "a" << ": " << adnGanador[i].getFenotipo();

	}

	salida << endl;
	salida.close();
}

//inicia una nueva poblacion, reemplazando los individuos mas debiles por los hijos del curze

vector<individuo> poblacion::nueva( individuo hijo ){

	vector<individuo> nuevaPoblacion;

	nuevaPoblacion = indi;

	for(int i = 0; i < nuevaPoblacion.size(); i++ )
		nuevaPoblacion[ i ] = indi[ Gan[i] ];			//Se mantienen los individuos mas fuertes

	for(int i = 0; i < Perd.size(); i++ )
		nuevaPoblacion[ Perd[ i ] ] = hijo;				// Se reemplazan los debiles por los hijos

	return nuevaPoblacion;
}

//Se cruzan los padres mas fuertes y se obtienen dos hijos de este cruzamiento

vector< vector< cromosoma > > poblacion::cruze(int * padres){

	vector< vector< cromosoma > > hijos;



	vector<short> auxiliar;
	vector<short> auxiliar2;


	vector<short> papa = indi[padres[0]].fucion();					//Se obtiene el adn completo de los padres para poder realizar el cruzamiento

	vector<short> mama = indi[padres[1]].fucion();


	vector<cromosoma> aux1 = indi[padres[1]].getADN();

	int pivo = rand() % papa.size();						//Pivote aleatorio donde se cruzaran los adns

	//Se curzan los adn de los padres, se obtienen dos adn por cruzamiento

	for(int i = 0 ; i < pivo; i++)
		auxiliar.push_back(papa[i]);
	for(int i = pivo ; i < mama.size(); i++)
		auxiliar.push_back(mama[i]);
	for(int i = 0 ; i < pivo; i++)
		auxiliar2.push_back(mama[i]);
	for(int i = pivo ; i < papa.size(); i++)
		auxiliar2.push_back(papa[i]);

	//Se mutan los adn recientemente cruzados

	mutacion(auxiliar2,papa.size());
	mutacion(auxiliar,papa.size());
	int cont = 0;
	vector<cromosoma> hijo;
	vector<cromosoma> hijo2;

	//Se crean los cromosomas para cada adn de los dos hijos

	for(int i = 0; i < aux1.size(); i++){
		int tamCrom = aux1[i].getMJ();
		int a = aux1[i].getAJ();
		int b = aux1[i].getBJ();
		int n = aux1[i].getNJ();
		vector<short> auxCroma;
		vector<short> auxCroma2;
		for(int j = 0; j < tamCrom; j++){
			auxCroma.push_back(auxiliar[cont]);
			auxCroma2.push_back(auxiliar2[cont++]);
		}
		cromosoma cromHijo = cromosoma(auxCroma,a,b,n,tamCrom);
		cromosoma cromHijo2 = cromosoma(auxCroma2,a,b,n,tamCrom);
		hijo.push_back(cromHijo);
		hijo2.push_back(cromHijo2);
	}
	//Se guardan los adn de los hijos

	hijos.push_back(hijo);
	hijos.push_back(hijo2);


	//Se regresan los adn de los hijos
	return hijos;
}


//Funcion que muta el adn

void mutacion(vector<short> &hijo,int n){
	int posicion = rand() % n;				//Aleatoriamente se elige un gen para ser mutado
	if(hijo[posicion]==0)
		hijo[posicion] = 1;
	else
		hijo[posicion] = 0;
}


//Funcion que obtiene los individuos mas fuertes y debiles de la poblacion

int * poblacion::fuerte(){
	sumar();
	porcentaje();
	acomula();
	alea();
	Gan.clear();

	//Se obtienen los ganadores de la poblacion
	for(int i = 0; i < indi.size(); i++){
		for(int j = 0; j < indi.size(); j++){
			if(aleatorio[i]<=zAcum[j]){
				Gan.push_back(j);
				break;
			}
		}
	}


	//Se obtienen los padres para ser cruzados (los mas fuertes)
	int tama = Gan.size();
	cubeta.clear();
	int auxMax = 0;
	padress = (int *) malloc(2*sizeof(int));

	padress[0] = -1;
	padress[1] = -1;

	for(int i = 0; i < indi.size(); i++)
		cubeta.push_back(0);

	for(int i = 0; i < tama; i++){
		cubeta[Gan[i]]++;

	}



	for(int i = 0; i < indi.size(); i++){
		if(cubeta[i]>auxMax)
			auxMax = cubeta[i];
	}

	bool bandera1;
	int ina = 0;


	for(int j = auxMax; j > 0; j--){

		bandera1 = false;
		for(int z = 0; z < indi.size(); z++){

			if(cubeta[z] == j&&ina<=1){
				padress[ina++] = z;
				bandera1 = true;
			}
		}
		if(bandera1&&ina>1)
			break;
	}
	if(padress[1]==-1)
		padress[1]=padress[0];


	//Se obtienen los perdedores de la poblacion
	for(int z = 0; z < indi.size(); z++){
		if(cubeta[z] == 0){
			Perd.push_back(z);
		}
	}

	return padress;

}

void poblacion::alea(){
	double r;
	aleatorio.clear();

	for(int i = 0; i < indi.size(); i++){

		r = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX)+1);
		aleatorio.push_back(r);

	}

}

void poblacion::acomula(){
	double acom = 0.0;
	zAcum.clear();

	for(int i = 0; i < zPor.size(); i++){
		zAcum.push_back(zPor[i]+acom);

		acom += zPor[i];
	}

}
double poblacion::checador(){
	sumZ = 0;
	for(int i = 0; i < indi.size(); i++){
		sumZ += indi[i].getZ();
	}
	return sumZ;
}

void poblacion::porcentaje(){
	double aux;
	zPor.clear();

	for(int i = 0; i < indi.size(); i++){
		aux = (indi[i].getZ())/sumZ;
		zPor.push_back(aux);

	}

}

void poblacion::sumar(){
	sumZ = 0;

	for(int i = 0; i < indi.size(); i++){
		sumZ += indi[i].getZ();

	}

}
