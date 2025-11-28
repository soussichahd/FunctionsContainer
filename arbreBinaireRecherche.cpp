#include <iostream>
#include <fstream> 
#include <algorithm>
#include <iomanip> 
#include <time.h>
#include <vector>
using namespace std;

template <typename T>
class Noeud {
protected:
    T val;
    Noeud<T>* fg; 
    Noeud<T>* fd;  
    int couleur;   

public:
    Noeud(T valeur) : val(valeur), fg(nullptr), fd(nullptr), couleur(32) {}

    template <typename U>
    friend class Tree;
    ~Noeud() {}
};

template <typename T>
class Tree {
private:
    Noeud<T>* racine;

 
    Noeud<T>* insertRec(T val, Noeud<T>* n) {
        if (n == nullptr) {
            return new Noeud<T>(val);
        }

        if (val < n->val)
            n->fg = insertRec(val, n->fg);
        else if (val > n->val)
            n->fd = insertRec(val, n->fd);
       

        return n;
    }
    
    // affichage infixe récursif
    void afficherInfixe(Noeud<T>* n, int& i) {
        if (n == nullptr) return;

        afficherInfixe(n->fg, i);
        cout << "Valeur " << i << " : " << n->val << endl;
         
        i++;
        
        afficherInfixe(n->fd, i);
    }
     bool RechercheRec(Noeud<T>* ne,T val){
     	if( ne==NULL) return false;
     	 if( ne->val==val){
     	 	return true;
		  }
		  else if( ne->val <val) return RechercheRec(ne->fd,val);
		    else return RechercheRec(ne->fg,val);
	 }
	 
		Noeud<T>* minValue(Noeud<T>* n) {
		    Noeud<T>* current = n;
		    while (current && current->fg != nullptr)
		        current = current->fg;
		    return current;
		}


Noeud<T>* supprimerRec(Noeud<T>* rac, T val) {
    if (rac == nullptr) return rac;

    if (val < rac->val)
        rac->fg = supprimerRec(rac->fg, val);
    else if (val > rac->val)
        rac->fd = supprimerRec(rac->fd, val);

    else {
        if (rac->fg == nullptr && rac->fd == nullptr) {
            delete rac;
            return nullptr;
        }
        else if (rac->fg == nullptr) {
            Noeud<T>* temp = rac->fd;
            delete rac;
            return temp;
        }
        else if (rac->fd == nullptr) {
            Noeud<T>* temp = rac->fg;
            delete rac;
            return temp;
        }

        Noeud<T>* temp = minValue(rac->fd);
        rac->val = temp->val;
        rac->fd = supprimerRec(rac->fd, temp->val);
    }
    return rac;
}

void deleteRec(Noeud<T>* n) {
        if (n == nullptr) return;
        deleteRec(n->fg);
        deleteRec(n->fd);
        delete n;
    }
    
public:
  Tree() : racine(nullptr) {}

    
    void insert(T val) {
        racine = insertRec(val, racine);
    }

  
    void afficher() {
        int i = 1;
        afficherInfixe(racine, i);
    }
    //insert par la methode iterative et ne c est le noeud a inserer
    void insertIter(Noeud<T>* ne ){
    	if (!racine) { racine = ne; return; }
    	Noeud<T> * x=racine;
    	Noeud<T> * y=NULL;
    	while (x!=NULL){
    		y=x;
    		
    		if( ne->val < x->val)
    			x=x->fg;
    	    else x=x->fd;
			}
		if(y==NULL)
		   racine=ne;
		else if(ne->val < y->val)
		      y->fg=ne;
	    else if(ne->val > y->val)
		        y->fd=ne;
		else { // Si la valeur existe déjà (ne pas insérer)
                delete ne; // Libérer le nœud non utilisé
                return;
            }
		        
	}
	
	bool Recherche(T val){
		return RechercheRec(racine ,val);
	}
	//la recherche iterative
	bool RechercheIte(T val){
		Noeud<T> * curent =racine;
		while(curent != NULL){
			 if( curent->val== val) return true;
			 else if( curent->val > val) curent=curent->fg;
			      else curent= curent->fd;
		}
		return false;
	 	}
  void supprimer(T val) {
    racine = supprimerRec(racine, val);
}
//elle retourn true si est bient supprimer
bool supprimerIter(T delet_val) {
		    Noeud<T>* curent = racine;
		    Noeud<T>* parent = nullptr;
		//recherche
		    while (curent != nullptr && curent->val != delet_val) {
		        parent = curent;
		        if (delet_val < curent->val)
		            curent = curent->fg;
		        else
		            curent = curent->fd;
		    }
		
		    // Nœud introuvable
		    if (curent == nullptr) return false;
		
		    // le nœud est une feuille
		    if (curent->fg == nullptr && curent->fd == nullptr) {
		
		        // suppression de la racine
		        if (parent == nullptr) {
		            delete racine;
		            racine = nullptr;
		            return true;
		        }
		
		        if (parent->fg == curent)
		            parent->fg = nullptr;
		        else
		            parent->fd = nullptr;
		
		        delete curent;
		        return true;
		    }
		
		    //  un seul enfant ===
		    if (curent->fg == nullptr || curent->fd == nullptr) {
		        Noeud<T>* enfant = (curent->fg != nullptr) ? curent->fg : curent->fd;
		
		        if (parent == nullptr) {   //curent == racine
		            delete racine;
		            racine = enfant;
		            return true;
		        }
		
		        // rattacher l'enfant au parent
		        if (parent->fg == curent)
		            parent->fg = enfant;
		        else
		            parent->fd = enfant;
		
		        delete curent;
		        return true ;
		    }
		
		    //deux enfants
		    // On prend le successeur (min du sous-arbre droit)
		    
		    Noeud<T>* min = minValue(curent->fd);
		    
		
			// On retrouve le parent du min
			Noeud<T>* minParent = curent;
			Noeud<T>* tmp = curent->fd;
			
			while (tmp != nullptr && tmp != min) {
			    minParent = tmp;
			    tmp = tmp->fg;   
			}
			
			// Remplacer la valeur du nœud à supprimer
			curent->val = min->val;
			
			// Suppression du min
			if (minParent->fg == min)
			    minParent->fg = min->fd;   
			else
			    minParent->fd = min->fd;
			
			delete min;
			return true;
		}
	~Tree() {
        deleteRec(racine);
    }
		
		   
};
//on teste seulement lers methode iterative car les methode recursive se block avec les grand fichier
		int main() {
		clock_t debut, fin;
		double tInsertIter, tSearchIter,tDeletIter;
		
		string mot;
		Tree<string> ABR2;
		vector<string> valeursTest;
		
		ifstream fichier("C:\\Users\\core solutions\\Documents\\POO2\\Dictionnaire.txt");
		if (!fichier) { cerr << "Impossible d'ouvrir le fichier !" << endl; return 1; }
		
		debut = clock();
		while (fichier >> mot) {
		    if (mot.empty()) continue;
		   
		       
		        valeursTest.push_back(mot);  // sauvegarde pour tests
		        Noeud<string>* ne = new Noeud<string>(mot);
		        ABR2.insertIter(ne);
		   
		}
		fin = clock();
		tInsertIter = double(fin - debut) / CLOCKS_PER_SEC;
		fichier.close();
		
		// Mesure recherche sur toutes les valeurs
		debut = clock();
		int compteur = 0;
		for (string val : valeursTest) {
		    if (ABR2.RechercheIte(val)) compteur++;
		}
		fin = clock();
		tSearchIter = double(fin - debut) / CLOCKS_PER_SEC;
			debut = clock();
			//suppression
		int compteur2 = 0;
		for (string val : valeursTest) {
		    if (ABR2.supprimerIter(val)) compteur2++;
		}
		fin = clock();
		tDeletIter = double(fin - debut) / CLOCKS_PER_SEC;
		ABR2.afficher();
		cout << fixed << setprecision(7);
		cout << "\n-------- TEMPS D'EXECUTION --------\n";
		cout << "Insertion iterative : " << tInsertIter << " sec\n";
		cout << "Recherche iterative : " << tSearchIter << " sec\n";
		cout << "Nombres trouves : " << compteur << " / " << valeursTest.size() << endl;
		cout << "Supprimer iterative : " << tDeletIter<< " sec\n";
		cout << "Nombres supprimer : " << compteur2 << " / " << valeursTest.size() << endl;
		
		return 0;}