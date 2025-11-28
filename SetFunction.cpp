
#include <iostream>
#include <fstream> 
#include <algorithm>
#include <iomanip> 
#include <time.h>
#include <set>
#include<vector>
using namespace std;
template <typename T> class SetFunction {
	private :
		std::set<T> table;
		double taille;
	public:
		SetFunction() = default;
        ~SetFunction() = default;
        
		void insert(const T& val) {
             table.insert(val);
         }
         //retourn 1 si la vale existe 
         bool Recherche(const T& val) const {
        // La fonction count() de std::set retourne 1 si l'élément existe, 0 sinon.
         return table.count(val) > 0;
        }
        //supprimer
        void supprimer(const T& val) {
        // La fonction erase() de std::set ne fait rien si l'élément n'existe pas.
        table.erase(val);
    }
    void afficher() const {
        std::cout << "{ ";
        // ds le set Les éléments sont déjà triés.
        for (const T& val : table) {
            std::cout << val << " ";
        }
        std::cout << "}" << std::endl;
    }
         
    
		
};
int main() {
   
    clock_t debut, fin;
    double tInsert, tSearch, tDelete;
    SetFunction<string> monSet;
    string mot;
    vector<string> valeursTest;
    

    ifstream fichier("C:\\Users\\core solutions\\Documents\\POO2\\Dictionnaire.txt"); 
    
    if (!fichier.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier 'Dictionnaire.txt'. Verifiez le chemin." << endl;
        return 1;
    }
    
    int count = 0;
    debut = clock();
    
    while (fichier >> mot) {
        if (!mot.empty()){
            
                monSet.insert(mot);
                
                // Stocker les 500 premières valeurs pour les tests de recherche/suppression
                
                    valeursTest.push_back(mot);
                
                count++;
        }
    }
    
    // Fin de la mesure de l'insertion
    fin = clock();
    tInsert = double(fin - debut) / CLOCKS_PER_SEC;
    fichier.close();

    cout << "Nombre d insertion: " << count << endl;


    // On teste la recherche sur les valeurs stockées
    debut = clock();
    int trouvee=0;
    for (string v : valeursTest) {
        if( monSet.Recherche(v)==1) trouvee++ ;
    }
    
    fin = clock();
    tSearch = double(fin - debut) / CLOCKS_PER_SEC;
    cout << "Nombre de recherches trouvee : " << trouvee << endl;

   
    // On teste la suppression sur les mêmes valeurs
    debut = clock();
    
    for (string v : valeursTest) {
        monSet.supprimer(v);
    }
    
    fin = clock();
    tDelete = double(fin - debut) / CLOCKS_PER_SEC;

   
    monSet.afficher();
    cout << fixed << setprecision(7);
    
    cout << "\n -------- TEMPS D'EXECUTION (std::set) -------- \n";
    cout << "Insertion (" << count << " elements) : " << tInsert << " sec\n";
    cout << "Recherche (" << valeursTest.size() << " tests) : " << tSearch << " sec\n";
    cout << "Suppression (" << valeursTest.size() << " tests) : " << tDelete << " sec\n";

    return 0;
}