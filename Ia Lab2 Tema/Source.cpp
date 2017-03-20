#include <iostream>
#include <stdlib.h>
#include <tuple>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>

#define baiat 1
#define fata 0


struct elev
{
	int clasa;
	int tip;
	int nr_matricol;
	elev(int cls, int tip,int nr) :clasa{ cls }, tip{ tip },nr_matricol{nr}{}
	elev()
	{
		clasa = 0;
		tip = fata;
		nr_matricol = 1;
	}

	bool operator==( const elev& b) {
		return (nr_matricol == b.nr_matricol && clasa == b.clasa && tip == b.tip);
	}
};



class problema
{
private:
	std::vector<std::pair<int, int>> clase;
	std::vector<elev> elevi;
	int total_elevi = 0;
	std::ofstream g;


public:
	problema() :g("Text.txt") {

		citire();
	}

	inline elev get_first_level(int nivel) {

		elev x;
		if (clase[nivel].first != 0)
			x.tip = fata;
		else
			x.tip = baiat;
		x.nr_matricol = 1;
		x.clasa = nivel;
		return x;
	}
	inline bool  get_next_elev(elev & x) {
		if (x.tip == fata)
			if (clase[x.clasa].second >= x.nr_matricol)
				x.tip = baiat;
			else
				if (clase[x.clasa].first > x.nr_matricol)
					x.nr_matricol++;
				else
					if (clase.size() == (x.clasa + 1))
						return false;
					else
						x = get_first_level(x.clasa + 1);
		else
			if (clase[x.clasa].first > x.nr_matricol) {
				x.nr_matricol++;
				x.tip = fata;
			}
			else
				if (clase[x.clasa].second > x.nr_matricol)
					x.nr_matricol++;
				else
					if (clase.size() == (x.clasa + 1))
						return false;
					else
						x = get_first_level(x.clasa + 1);
		return true;

	}

	void citire() {
		std::ifstream f("Data.txt");
		int x, y;
		while (f >> x >> y) {
			clase.emplace_back(x, y);
			total_elevi += x + y;
		}
		f.close();

		/*for (auto xz : clase) {
			std::cout << xz.first << " " << xz.second << std::endl;
		}*/


		/*elev elv;
		elv = get_first_level(0);
		g << elv.clasa << "<-clasa     " << elv.tip << " <-tip      " << elv.nr_matricol << " <- nr_matricol \n";
		bool ok = get_next_elev(elv);

		while(ok)
		{
			g << elv.clasa << "<-clasa     " << elv.tip << " <-tip      " << elv.nr_matricol << " <- nr_matricol \n";
			ok = get_next_elev(elv);
		}*/


	}
	bool consistent() {

		if (elevi.size() > 1 && elevi.back().clasa == (elevi.end() - 2)->clasa)
			return false;
		for (auto i = elevi.begin(); i != elevi.end() - 1; i++)
			if (*i == elevi.back())
				return false;

		if (elevi.size() > 1 && elevi.back().tip == (elevi.end() - 2)->tip)
			return false;
		
		if (elevi.size() == total_elevi)
			if (elevi.back().clasa == elevi.front().clasa || elevi.back().tip == elevi.front().tip)
				return false;
		return true;
	}

	bool solutie() {
		return elevi.size() == total_elevi;
	}

	void tiparire_solutie()
	{
		g << "\n \n \n \n O Solutie este : \n" << std::endl;
		for(auto x:elevi)
		{
			if (x.tip == 1)
				g << "\n" << " Clasa :" << x.clasa << " |    Tip : Baiat |    Nr de ordine al clasei : " << x.nr_matricol;
			else
				g << "\n" << " Clasa :" << x.clasa << " |    Tip : Fata  |    Nr de ordine al clasei : " << x.nr_matricol;
		}
	}


	inline	void backtracking()	{
		std::cout << "Solving ... :( ! Please wait ! \n";
		elevi.push_back(get_first_level(0));
		elevi.push_back(elev(0,baiat,0));
		while (elevi.size() >1)
		{
			auto choosed = false;
			while (!choosed && get_next_elev(elevi.back())){
				choosed =  consistent() ;
			}

			if (choosed)
				if (solutie())
					tiparire_solutie();
				else
					elevi.push_back(elev(0, baiat, 0));
			else
				elevi.pop_back();
		}

		std::cout << "i think i may found somethink...	\n";

	}
};







int main(){
	problema a;
	a.backtracking();
	std::cout << "\nPress enter to exit ! ";
	char xy[1];
	std::cin.get(xy,200) ;
}
