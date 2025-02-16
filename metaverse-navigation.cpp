#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <limits>

constexpr unsigned int infini = std::numeric_limits<unsigned int>::max();

// sommet
struct Etat {
    unsigned int x, y, couleur, cout, cout_heuristique;

    bool operator>(const Etat& autre) const {
        return cout_heuristique > autre.cout_heuristique;
    }
};


struct EtatPrecedent {
    int x, y, couleur;
    std::string action;
};

class Univers {
    unsigned int N;  // Nombre de ligne et nombre de colonnes
    unsigned int C;  // Nombre de couleur
    std::vector<std::vector<unsigned int>> universMatrice;

public:
    Univers() {}
    ~Univers() {}

    unsigned int heuristique(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
        return std::abs((int)x1 - (int)x2) + std::abs((int)y1 - (int)y2);
    }


    void plusCourtChemin(unsigned int x_depart, unsigned int y_depart, 
                             unsigned int couleur_depart, 
                             unsigned int x_destination, unsigned int y_destination) {

    // Initialisation des variables 
	const int dx[] = {0, 0, -1, 1};  
    const int dy[] = {-1, 1, 0, 0};
    const char action_tab[] = {'h', 'b', 'g', 'd'};

    std::vector<std::vector<std::vector<unsigned int>>> distances(
        N, std::vector<std::vector<unsigned int>>(
            N, std::vector<unsigned int>(C, infini)));

    
    Etat etat_depart = {x_depart, y_depart, couleur_depart, 0, 0};

    std::vector<std::vector<std::vector<EtatPrecedent>>> parents(
        N, std::vector<std::vector<EtatPrecedent>>(
            N, std::vector<EtatPrecedent>(C, {-1, -1, -1, ""})));

    
    distances[etat_depart.x][etat_depart.y][etat_depart.couleur] = 0;
    parents[etat_depart.x][etat_depart.y][etat_depart.couleur].action = "";

    std::priority_queue<Etat, std::vector<Etat>, std::greater<Etat>> file;
    etat_depart.cout_heuristique = etat_depart.cout + heuristique(x_depart, y_depart, x_destination, y_destination);
    file.push(etat_depart);

    file.push(etat_depart);
    while (!file.empty()) {
        Etat etat_min = file.top();
        file.pop();

        if (etat_min.cout > distances[etat_min.x][etat_min.y][etat_min.couleur]) continue;

        for (int i = 0; i < 4; i++) {
            unsigned int voisin_x = etat_min.x + dx[i];
            unsigned int voisin_y = etat_min.y + dy[i];

            if (voisin_x < N && voisin_y < N) {
                unsigned int couleur_cellule = universMatrice[voisin_y][voisin_x];

                if (couleur_cellule != etat_min.couleur) {

                    unsigned int nouveau_cout = distances[etat_min.x][etat_min.y][etat_min.couleur] + 1;
                    Etat voisin = {voisin_x, voisin_y, etat_min.couleur, nouveau_cout, 0};

                    std::string &couleur_parent = parents[etat_min.x][etat_min.y][etat_min.couleur].action;

                    if (nouveau_cout < distances[voisin_x][voisin_y][voisin.couleur]) {
                        distances[voisin.x][voisin.y][voisin.couleur] = nouveau_cout;
                        parents[voisin_x][voisin_y][voisin.couleur].action = couleur_parent + action_tab[i] + " ";
                        voisin.cout_heuristique = nouveau_cout + heuristique(voisin_x, voisin_y, x_destination, y_destination);
                        file.push({voisin});
                    }
                }
            

                Etat etat_apres_deplacement = {etat_min.x, etat_min.y, universMatrice[etat_min.y]
                                [etat_min.x],couleur_cellule, 0};

                unsigned int cout_apres_changement = distances[etat_min.x][etat_min.y][etat_min.couleur] + 10;

                unsigned int &distances_courant = distances[etat_apres_deplacement.x]
                                                [etat_apres_deplacement.y][etat_apres_deplacement.couleur];

                if (cout_apres_changement < distances_courant) {
                    distances_courant = cout_apres_changement;
                    std::string &parent_action = parents[etat_apres_deplacement.x]
                                [etat_apres_deplacement.y][etat_apres_deplacement.couleur].action;

                    parent_action = parents[etat_min.x][etat_min.y][etat_min.couleur].action + "c ";
                    file.push(etat_apres_deplacement);

                    if (couleur_cellule != etat_apres_deplacement.couleur) {
                        Etat voisin = {voisin_x, voisin_y, etat_apres_deplacement.couleur, couleur_cellule, 0};
                        unsigned int cout_total = cout_apres_changement + 1;

                        if (cout_total < distances[voisin.x][voisin.y][etat_apres_deplacement.couleur]) {
                            distances[voisin.x][voisin.y][voisin.couleur] = cout_total;
                            parents[voisin_x][voisin_y][voisin.couleur].action = parent_action + action_tab[i] + " ";
                            etat_apres_deplacement.cout_heuristique = cout_apres_changement + heuristique(etat_apres_deplacement.x, etat_apres_deplacement.y, x_destination, y_destination);
                            file.push({voisin});
                        }
                    } 
                }

            }
        }
    }

    unsigned int cout_min = infini;
    std::string meilleur_chemin;

    for (unsigned int c = 0; c < C; c++) {
        Etat dest = {x_destination, y_destination, c, distances[x_destination][y_destination][c], 0};
        if (distances[dest.x][dest.y][dest.couleur] < cout_min) {
            cout_min = distances[dest.x][dest.y][dest.couleur];
            meilleur_chemin = parents[dest.x][dest.y][dest.couleur].action;
        }
    }

    if (cout_min == infini) {
        std::cout << "Impossible" << std::endl;
    } else {
        std::cout << meilleur_chemin << cout_min << std::endl;
    }

}

    friend std::istream& operator>>(std::istream& is, Univers& univers);
};

std::istream& operator >> (std::istream& is, Univers& univers) {

	is >> univers.N; 		// Nombre de ligne et de colonnes
	is >> univers.C; 		// Nombre de couleurs

	assert(univers.N > 0);
	assert(univers.C > 0);
	univers.universMatrice.resize(univers.N, std::vector<unsigned int>(univers.N));

	for(unsigned int y = 0; y<univers.N; y++) {
		for(unsigned int x = 0; x<univers.N; x++) {
			unsigned int couleur;
			is >> couleur;
			univers.universMatrice[y][x] = couleur;
		}
	}
	return is;
}


int main(int argc, char const *argv[])
{
	if(argc != 7) {
		std::cerr << "Utilisation : " << argv[0] << " x_depart y_depart couleur_depart x_destination y_destination" << std::endl;
		return -1;
	}

	std::ifstream entree = std::ifstream(argv[1]);

	Univers univers;
	entree >> univers;

	unsigned int x_depart = atoi(argv[2]);
	unsigned int y_depart = atoi(argv[3]);
	unsigned int couleur_depart = atoi(argv[4]);
	unsigned int x_destination = atoi(argv[5]);
	unsigned int y_destination = atoi(argv[6]);

	univers.plusCourtChemin( x_depart, y_depart, couleur_depart, x_destination, y_destination );

	return 0;
}
