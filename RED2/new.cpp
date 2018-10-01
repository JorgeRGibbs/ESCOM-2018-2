#include <vector>
#include <iostream>
#include <string>

class cromosoma{
private:
	int aj:
	int bj;
	int nj;
	int mj;
	vector<short> cromatida;
	double fenotipo;
public: 
	cromosoma(int a,int b, int n);
	cromosoma(vector<short> hijo int a,int b, int n, int m);
	
}

class individuo{

	private:
		double resultadoEcuacion;	//Se guarda el resultado de la ecuacion
		vector<cromosoma> adn;	  //sirve para obtener el valor de cada variable de la ecuacion
		vector<string> variables; //sirve para evaluar la ecuacion con la libreria
	public:
		individuo(vector<cromosoma> ad, string &expression_z,vector<string> &vars, vector <double> &valorvars);
		double getZ();
		vector <short> funcion();
		vector<string> getVar();	//get variables del ADN
		vector<cromosomas> getADN(); //conseguir ADN
		double cumple(string &expression_Z, vector<string> &expr, vector<string> &valorvars);

};

individuo::individuo(vector<cromosoma> ad,string &expression_Z,vector<string> &expr, vector<string> &vars,vector<double> &valorvars){
	adn = ad;
	variables = vars;
	for (int i = 0; i < adn.size; i++)
	{
		valorvars[i] = adn[i].getFenotipo()
	}
}

bool cromosoma::Poblar(){
	criomatida.clear();
	for (int i = 0; i < ; ++i)
	{
		rand() % 2;
	}
}

//cromosoma::Poblar = llenar la poblacion con numeros aleatorios para su evaluacion
//devuelve unos o ceros