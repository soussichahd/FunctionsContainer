#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 
#include <time.h>
#include <fstream> 

using namespace std;

 template <typename T> class Noeud {
		public:
		    T val;
		    Noeud* fg;
		    Noeud* fd;
		    Noeud* parent;
		    bool couleur; // 0=rouge, 1=noir
		
		    Noeud(T v, bool c, Noeud* p)
		        : val(v), fg(nullptr), fd(nullptr), parent(p), couleur(c) {}
		
		    bool isRed() const { return couleur == 0; }
		    bool isBlack() const { return couleur == 1; }
		    void setColor(bool c) { couleur = c; }
};

 template <typename T> class BRT{
private:
    Noeud<T>* racine;

    void afficherInfixe(Noeud<T>* n, int& i) {
        if (!n) return;
        afficherInfixe(n->fg, i);
        cout << "Valeur " << i << " : " << n->val 
             << " (" << (n->isRed() ? "R" : "N") 
             << endl;
        i++;
        afficherInfixe(n->fd, i);
    }
    //retourner le noeud min d un sous arbre 
    Noeud<T>* minValue(Noeud<T>* n) {
		    Noeud<T>* current = n;
		    while (current && current->fg != nullptr)
		        current = current->fg;
		    return current;
		}
    
    // Rotation Gauche (RG)
    void RG(Noeud<T>* x) { 
        Noeud<T>* y = x->fd;
        x->fd = y->fg;
        if (y->fg) y->fg->parent = x;
        y->parent = x->parent;
        
        if (!x->parent) racine = y;
        else if (x == x->parent->fg) x->parent->fg = y;
        else x->parent->fd = y;
        
        y->fg = x;
        x->parent = y;
    }

    // Rotation Droite (RD)
    void RD(Noeud<T>* x) { 
        Noeud<T>* y = x->fg;
        x->fg = y->fd;
        if (y->fd) y->fd->parent = x;
        y->parent = x->parent;
        
        if (!x->parent) racine = y;
        else if (x == x->parent->fg) x->parent->fg = y;
        else x->parent->fd = y;
        
        y->fd = x;
        x->parent = y;
    }

public:
    BRT() : racine(nullptr) {}
    
    void insertBlackRed(T valeur, bool color) {
        Noeud<T>* y = nullptr;
        Noeud<T>* x = racine;

        // Recherche de la position d'insertion ABR
        while (x != nullptr) {
            y = x;
            if (valeur < x->val) x = x->fg;
            else if (valeur > x->val) x = x->fd;
            else return; // Valeur déjà présente
        }
        
        //Création du nouveau noeud
        Noeud<T>* z = new Noeud<T>(valeur, color, y);
        if (!y) racine = z;
        else if (valeur < y->val) y->fg = z;
        else y->fd = z;
        //si z est noire ou racine on sortie
        if (z->isBlack() || z == racine) { 
            if (racine) racine->setColor(1); 
            return;
        }

        //P=RED Z=RED
        while (z->parent && z->parent->isRed()) {
            Noeud<T>* p = z->parent;
           Noeud<T>* gp = p->parent; // grand parent
      
	        if (gp == nullptr) break; 
            
            Noeud<T>* u; 
            
            if (p == gp->fg) { // P=fg
                u = gp->fd;
                if (u && u->isRed()) {//P=RED Z=RED U=Red
                    p->setColor(1);
                    u->setColor(1);
                    gp->setColor(0);
                    z = gp; // Continuer la vérification au niveau du GP
                } else { // //P=RED Z=RED U=Black
                    if (z == p->fd) { // p=fg, z=fd 
                        z = p;
                        RG(z); 
                        p = z->parent; 
                        gp = p->parent; // GP est l'ancien P
                    }
                    // Ligne (p=fg, z=fg)
                    p->setColor(1);
                    gp->setColor(0);
                    RD(gp); 
                }
            } else { // p=fd
                u = gp->fg;
                if (u && u->isRed()) { ////P=RED Z=RED U=REd
                    p->setColor(1);
                    u->setColor(1);
                    gp->setColor(0);
                    z = gp;
                } else { //P=RED Z=RED U=black
                    if (z == p->fg) { // (p=fd, z=fg)
                        z = p;
                        RD(z); // Rotation sur P
                        p = z->parent;
                        gp = p->parent;
                    }
                    // Cas 3 : Ligne (p=fd, z=fd)
                    p->setColor(1);
                    gp->setColor(0);
                    RG(gp);
                }
            }
        }

        if (racine) racine->setColor(1); // Assure que la racine reste noire
    }
   
    void afficher() {
        int i = 1;
        cout << "\n--- Affichage Infixe de l'Arbre R-B ---\n";
        afficherInfixe(racine, i);
    }
    
    	
    
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
    ~BRT() {
       
    }
};

int main() {
		clock_t debut, fin;
		double tInsertIter, tSearchIter,tDeletIter;
		
		string mot;
	    BRT<string> A;
		vector<string> valeursTest;
		
		ifstream fichier("C:\\Users\\core solutions\\Documents\\POO2\\Dictionnaire.txt");
		if (!fichier) { cerr << "Impossible d'ouvrir le fichier !" << endl; return 1; }
		
		debut = clock();
		while (fichier >> mot) {
		    if (mot.empty()) continue;
		   
		       
		        valeursTest.push_back(mot);  // sauvegarde pour tests
		        A.insertBlackRed(mot,0);//inserer tous les mot avec rouge 
		   
		}
		fin = clock();
		tInsertIter = double(fin - debut) / CLOCKS_PER_SEC;
		fichier.close();
		
		// Mesure recherche sur toutes les valeurs
		debut = clock();
		int compteur = 0;
		for (string val : valeursTest) {
		    if (A.RechercheIte(val)) compteur++;
		}
		fin = clock();
		tSearchIter = double(fin - debut) / CLOCKS_PER_SEC;
			debut = clock();
			//suppression
		int compteur2 = 0;
		for (string val : valeursTest) {
		    if (A.supprimerIter(val)) compteur2++;
		}
		fin = clock();
		tDeletIter = double(fin - debut) / CLOCKS_PER_SEC;
		A.afficher();
		cout << fixed << setprecision(7);
		cout << "\n-------- TEMPS D'EXECUTION --------\n";
		cout << "Insertion iterative : " << tInsertIter << " sec\n";
		cout << "Recherche iterative : " << tSearchIter << " sec\n";
		cout << "Nombres trouves : " << compteur << " / " << valeursTest.size() << endl;
		cout << "Supprimer iterative : " << tDeletIter<< " sec\n";
		cout << "Nombres supprimer : " << compteur2 << " / " << valeursTest.size() << endl;
		
		return 0;
}
