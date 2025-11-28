#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Noeud {
		public:
		    int  val;
		    Noeud* fg;
		    Noeud* fd;
		    Noeud* parent;
		    bool couleur; // 0=rouge, 1=noir
		
		    Noeud(int v, bool c, Noeud* p)
		        : val(v), fg(nullptr), fd(nullptr), parent(p), couleur(c) {}
		
		    bool isRed() const { return couleur == 0; }
		    bool isBlack() const { return couleur == 1; }
		    void setColor(bool c) { couleur = c; }
};

class ABR {
private:
    Noeud* racine;

    void afficherInfixe(Noeud* n, int& i) {
        if (!n) return;
        afficherInfixe(n->fg, i);
        cout << "Valeur " << i << " : " << n->val 
             << " (" << (n->isRed() ? "R" : "N") 
             << ") Parent: " << ( n->parent!=NULL ?to_string(n->parent->val): "--" ) << endl;
        i++;
        afficherInfixe(n->fd, i);
    }
    
    // Rotation Gauche (RG)
    void RG(Noeud* x) { 
        Noeud* y = x->fd;
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
    void RD(Noeud* x) { 
        Noeud* y = x->fg;
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
    ABR() : racine(nullptr) {}
    
    void insertBlackRed(int valeur, bool color) {
        Noeud* y = nullptr;
        Noeud* x = racine;

        // Recherche de la position d'insertion ABR
        while (x != nullptr) {
            y = x;
            if (valeur < x->val) x = x->fg;
            else if (valeur > x->val) x = x->fd;
            else return; // Valeur déjà présente
        }
        
        //Création du nouveau noeud
        Noeud* z = new Noeud(valeur, color, y);
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
            Noeud* p = z->parent;
            Noeud* gp = p->parent; // grand parent
      
	        if (gp == nullptr) break; 
            
            Noeud* u; 
            
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
    bool RechercheIte( int val){
		Noeud<T> * curent =racine;
		while(curent != NULL){
			 if( curent->val== val) return true;
			 else if( curent->val > val) curent=curent->fg;
			      else curent= curent->fd;
		}
		return false;
	 	
		
	}
    void afficher() {
        int i = 1;
        cout << "\n--- Affichage Infixe de l'Arbre R-B ---\n";
        afficherInfixe(racine, i);
    }
    
   
    ~ABR() {
       
    }
};

int main() {
    ABR a;

    a.insertBlackRed(19, 1);
    a.insertBlackRed(14, 1);
    a.insertBlackRed(1, 0);  
    a.insertBlackRed(16, 0);
    a.insertBlackRed(28, 1); 
    a.insertBlackRed(24, 0);
    a.insertBlackRed(25, 0); 
    a.insertBlackRed(48, 0); 
    a.afficher();
    return 0;
}