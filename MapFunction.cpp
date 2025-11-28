#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include <ctime>

using namespace std;

template <typename Key, typename Value>
class MapFunction {
private:
	   map<Key, Value> table; // utilisation de unordered_map
		public:
		MapFunction() = default;
		~MapFunction() = default;
		
		void insert(const Key& key, const Value& val) {
		    table[key] = val; // insérer ou mettre à jour
		}
		
		bool Recherche(const Key& key) const {
		    return table.count(key) > 0;
		}
		
		void supprimer(const Key& key) {
		    table.erase(key);
		}
		
		void afficher() const {
		    cout << "{ ";
		    for (const auto& pair : table) {
		        cout << "[" << pair.first << " : " << pair.second << "] ";
		    }
		    cout << "}" << endl;
		}
		
		};

int main() {
    clock_t debut, fin;
	double tInsert, tSearch, tDelete;
		
	MapFunction<string, int> monMap;
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
		        monMap.insert(mot, 1); // valeur arbitraire 1
		        valeursTest.push_back(mot);
		        count++;
		    }
		}
		
		fin = clock();
		tInsert = double(fin - debut) / CLOCKS_PER_SEC;
		fichier.close();
		
		cout << "Nombre d'insertion: " << count << endl;
		//recherche
		debut = clock();
		int trouvee = 0;
		for (const string& v : valeursTest) {
		    if (monMap.Recherche(v)) trouvee++;
		}
		fin = clock();
		tSearch = double(fin - debut) / CLOCKS_PER_SEC;
		cout << "Nombre de recherches trouvées : " << trouvee << endl;
		
		// Test de suppression
		debut = clock();
		for (const string& v : valeursTest) {
		    monMap.supprimer(v);
		}
		fin = clock();
		tDelete = double(fin - debut) / CLOCKS_PER_SEC;
		
		monMap.afficher();
		
		cout << fixed << setprecision(7);
		cout << "\n-------- TEMPS D'EXECUTION (map) --------\n";
		cout << "Insertion (" << count << " elements) : " << tInsert << " sec\n";
		cout << "Recherche (" << valeursTest.size() << " tests) : " << tSearch << " sec\n";
		cout << "Suppression (" << valeursTest.size() << " tests) : " << tDelete << " sec\n";
		
		return 0;
		

}
