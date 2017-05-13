#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <string>
#include "math.h"
#include <ctime>

using namespace std;

class Chambre
{
	public:
		Chambre();
		~Chambre();

		void value(string id);
		void timeStampToReadable(double seconde);
		void display();
		int nbJourMois(int mois,int annee);
	private:
		string contenu;

		int CO2;
		int FALL; 
		
		string MTH02;
		float temp;
		int hum;

		bool OVEN;
		string TIME;
		string TV;
		string USER;

}; 