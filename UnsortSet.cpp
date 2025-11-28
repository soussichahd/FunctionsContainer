#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <iomanip>
#include <ctime>
using namespace std;

template <typename T>
class UnsortSetFunction {
		private:
		unordered_set<T> table; 
		public:
		UnsortSetFunction() = default;
		~UnsortSetFunction() = default;
		
		
		void insert(const T& val) {
		    table.insert(val);
		}
		
		// retourne true si la valeur existe
		bool Recherche(const T& val) const {
		    return table.count(val) > 0;
		}
		
		// supprimer
		void supprimer(const T& val) {
		    table.erase(val);
		}
		
		void afficher() const {
		    cout << "{ ";
		    for (const T& val : table) {
		        cout << val << " ";
		    }
		    cout << "}" << endl;
		}
		

};

int main() {
	clock_t debut, fin;
	double tInsert, tSearch, tDelete;
	UnsortSetFunction<string> monSet;
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
			    if (!mot.empty()) {
			        monSet.insert(mot);
			        valeursTest.push_back(mot); // stocker toutes les valeurs pour test
			        count++;
			    }
			}
			
			fin = clock();
			tInsert = double(fin - debut) / CLOCKS_PER_SEC;
			fichier.close();
			
			cout << "Nombre d'insertion: " << count << endl;
			
			// Test de recherche
			debut = clock();
			int trouvee = 0;
			for (const string& v : valeursTest) {
			    if (monSet.Recherche(v)) trouvee++;
			}
			fin = clock();
			tSearch = double(fin - debut) / CLOCKS_PER_SEC;
			cout << "Nombre de recherches trouvées : " << trouvee << endl;
			
			// Test de suppression
			debut = clock();
			for (const string& v : valeursTest) {
			    monSet.supprimer(v);
			}
			fin = clock();
			tDelete = double(fin - debut) / CLOCKS_PER_SEC;
			
			monSet.afficher();
			
			cout << fixed << setprecision(7);
			cout << "\n-------- TEMPS D'EXECUTION (std::unordered_set) --------\n";
			cout << "Insertion (" << count << " éléments) : " << tInsert << " sec\n";
			cout << "Recherche (" << valeursTest.size() << " tests) : " << tSearch << " sec\n";
			cout << "Suppression (" << valeursTest.size() << " tests) : " << tDelete << " sec\n";
			
			return 0;
			

}
