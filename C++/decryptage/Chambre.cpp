#include "Chambre.hpp"

Chambre::Chambre()
{
	ifstream fichier("test.txt", ios::in);  // on ouvre le fichier en lecture

 	if(fichier)  // si l'ouverture a réussi
	{       
		getline(fichier, contenu);  // on met dans "contenu" la ligne
		//cout << contenu << endl;  // on affiche la ligne
		fichier.close();  // on ferme le fichier
	}
	else  // sinon
		cerr << "Impossible d'ouvrir le fichier !" << endl;

	// Obtention des valeurs

  value("CO2");
  value("FALL");
  value("MTH02");
  value("USER");
  value("OVEN");
  value("TIME");
  value("TV");
  value("USER");
  
  display(); // Affichage des données
}

Chambre::~Chambre()
{
  
}

void Chambre::value(string id)
{
    int id_pos = contenu.find(id); // position dans le string du début nom de la valeur recherché
    int begin = contenu.find(':',id_pos); // Position du début de la valeur pour l'id qui correspond
    int finish = contenu.find(',', begin);// Position de fin de la valeur pour l'id qui correspond

    string value = contenu.substr(begin+1,(finish-begin)-1); // On extrait alors la valeur de l'id grâce au valeur précédente

  	if ( id == "CO2")
  	{
  		CO2 = atoi(value.c_str()); // C'est un int, un atoi() suffit à extraire la valeur
  	}
  	else if( id == "FALL")
  	{
      FALL = atoi(value.c_str()); // Idem que pour CO2
  	}
  	else if( id == "MTH02")
  	{
      value = value.substr(1,24);
      string temp_bin = value.substr(0,16); // On prend le binaire de la temp

      int puissance = 15;

      for(int i=0; i<16; i++) // Transformation du binaire en décimal
      {
        if(temp_bin[i] == '1')
        {
          temp = temp + pow(2,puissance);
        }
        puissance--;  
      }

      string deci_bin = value.substr(16,8); // on fait pareille pour l'humidité
      puissance = 7;

      for(int j=0; j<8; j++)
      {
        if(deci_bin[j] == '1')
        {
          hum = hum + pow(2,puissance);
        }
        puissance--;  
      }

      temp = (temp - 400) *(0.1);
  	}
  	else if( id =="OVEN")
  	{
      if(value == "true")
      {
        OVEN = true;
      }
      else
      {
        OVEN = false;
      }
  	}
  	else if( id =="TIME")
  	{
      
      // Extraction du timestamp
      string integer = value.substr(0, value.length() - 3); 
      string decimal = value.substr(10,3);
      double seconde = atof(integer.c_str());
      seconde = seconde + atof(decimal.c_str()) * (pow(10,-3));

      timeStampToReadable(seconde); // conversion du timestamp à une valeur lisible
  	}
  	else if ( id == "TV")
    {
      TV = value.substr(1, value.length() -2); // Extration de la valeur de TV
    }
    else if ( id == "USER")
  	{
      USER = value.substr(1, value.length() -3); // Idem que TV
  	}
}

void Chambre::display()
{
  cout << "CO2 : " << CO2 << endl << "FALL : " << FALL << endl << "TEMP : " 
    << temp << endl << "HUM : " << hum << endl << "OVEN : " 
    << OVEN << endl << fixed << "TIME : " << TIME << endl << "TV : " 
    << TV << endl << "USER : " << USER << endl;
}

void Chambre::timeStampToReadable(double seconde)
{
  
  // La fonction du génie qui marche pas. J'ai pas la bonne heure... problème de précision je sais pas où

  int nb_seconde_annee = 31557600; // Nombre de seconde dans une année
  int nb_seconde_jour = 86400; // Nombre de seconde dans un jour

  int nb_annee_ecoule = round(seconde/nb_seconde_annee); 
  int annee = nb_annee_ecoule + 1970;
  
  double seconde_annee_rest = seconde - (nb_annee_ecoule*nb_seconde_annee);
  int nb_jour = round( seconde_annee_rest/nb_seconde_jour); 

  int jour = nb_jour;
  int mois;

  for(int i=1;i<=12;i++)
  {
    if(jour >= nbJourMois(i,annee))
      jour = jour - nbJourMois(i,annee);
    else
    {
      mois = i;
      break;
    }
  }

  TIME = to_string(jour) + "/" + to_string(mois) + "/" + to_string(annee);

  double seconde_jour_rest = seconde_annee_rest - ((nb_jour-1)*nb_seconde_jour);

  cout << seconde_jour_rest << endl;

}

int Chambre::nbJourMois(int mois,int annee)
{
  switch(mois)
  {
    case 1:
      return 31;
    break;
    case 2:
      if (( annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0))
        return 29;
      else
        return 28;
    break;
    case 3:
      return 31;
    break;
    case 4:
      return 30;
    break;
    case 5:
      return 31;
    break;
    case 6:
      return 30;
    break;
    case 7:
      return 31;
    break;
    case 8:
      return 31;
    break;
    case 9:
      return 30;
    break;
    case 10:
      return 31;
    break;
    case 11:
      return 30;
    break;
    case 12:
      return 31;
    break;
  }  
}