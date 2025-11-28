Ce projet regroupe cinq implémentations différentes de contennaire en utilisant des templates en C++.
Ainsi qu’un module complet de benchmarking permettant de mesurer les performances de chaque contenaire lors du traitement d’un fichier contenant 1 millions de string.
Pour les 5 contenaire on a implementer les methode :
 ..supprimer 
 ..inserer 
 ..recherche 
 ..affichage_infixe( arbre )
 ..affichage( set, unordredset , map )
/////////////////////////////////////////////////////
La complexite des fonctions dans les moyens cas 
 Complexite de SetFunction:
   insertion :O(1)
   suppression: O(1)
   Recherche :O(1)
   affichage:O(n)

 Complexite de UnordredSetFunction:
  insertion :O(1)
  suppression: O(1)
  Recherche :O(1)
  affichage:O(n)

  Complexite de MapFunction:
   insertion :O(log n)
   suppression: O(log n)
   Recherche :O(log n)
    affichage:O(n)
 
  Complexite de ArbreBinaireRecherche:
   insertion :O(log n)
   suppression: O(log n)
   Recherche :O(log n)
   affichage:O(n)
  Complexite de BlackRedTree:
   rotation:O(1)
   insertion :O(log n)
   suppression: O(log n)
   Recherche :O(log n)
   affichage:O(n)
   minValue:O(log n)
   //////////////////////////////////////////////////////////
   insertion :
        Set: 2.1210000 sec
        UnorderedSet: 1.0990000 sec
        Map: 2.4600000 sec
        ABR: 2.2330000 sec
        BRT:  0.9500000 sec
  suppression (de 1 million string ):
        Set: 1.8860000 sec
        UnorderedSet: 0.7630000 sec
        Map: 1.8300000 sec
        ABR:  0.2160000 sec
        BRT:   0.2640000 sec
  Recherche( de 1 million string ):
        Set: 1.2900000 sec
        UnorderedSet: 0.5880000 sec
        Map:  1.2900000 sec
        ABR: 4.7050000 sec
        BRT:  0.6770000 sec
    Afficher :
      Set: 116.7910000 sec
      UnorderedSet: 133.6840000 sec
      Map: 423.9570000 sec
      ABR: 341.2520000 sec
       BRT: 341.2520000 sec
    
  

 
