#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WYMIAR 8
void inicjalizacja(int tab[WYMIAR + 4][WYMIAR + 4]);
void plansza(int tab[WYMIAR + 4][WYMIAR + 4]);
int mozliwosci(int tab[WYMIAR + 4][WYMIAR + 4], int litera, int numer);
int warunek(int tab[WYMIAR + 4][WYMIAR + 4], int litera, int numer, int stary_numer, int stara_litera, char c, int s);
void clear();
int main(void) {
	int litera = 0, numer = 0;
	int stary_numer, stara_litera, ruch, s;
	char c = 0;
	int tab[WYMIAR + 4][WYMIAR + 4];//tablica o wiekszych wymiarach aby umozliwic sprawdzanie czy dostepny jest ruch w prosty sposob
	printf("Dane autora:Adam Narozniak grupa srody godzina 14:15-16:00\nProjekt Konik szachowy do skakania po szachownicy\n");
	inicjalizacja(tab);//wypelnienie tablicy odpowiednimi wartosciami
	plansza(tab);//narysowanie tablicy
	printf("\n\nPodaj miejsce w ktorym chcesz rozpoczac: wiersz kolumna np.a 7 a nastepnie wcisnij \"enter\"\n");
	s = scanf(" %c%d", &c, &numer);//pierwsze zczytanie danych

	while ((numer < 1 || numer>8 || c<'a' || c>'h') || s != 2) {//sprawdzenie mozliwosci ruchu
		clear();
		plansza(tab);
		printf("\nPodales bledne pole, sprobuj jeszcze raz\n");
		s = scanf(" %c%d", &c, &numer);

	}
	litera = c - 'a';
	tab[WYMIAR + 2 - numer][litera + 2] = 1;//przypisanie elementowi tablicy innej wartosci od zadanej, aby moc go odroznic
	clear();
	for (ruch = 0; ruch < 63; ruch++) {
		mozliwosci(tab, litera, numer);
		stara_litera = litera;
		stary_numer = numer;
		plansza(tab);
		printf("\n\nPodaj miejsce do ktorego chcesz przeskoczyc: wiersz kolumna np.a 7 a nastepnie wcisnij \"enter\"\n");
		s = scanf(" %c%d", &c, &numer);
		litera = c - 'a';
		while (warunek(tab, litera, numer, stary_numer, stara_litera, c, s)) {
			clear();
			plansza(tab);
			printf("\nPodales bledne pole, sprobuj jeszcze raz\n");
			s = scanf(" %c%d", &c, &numer);
			litera = c - 'a';
		}
		tab[WYMIAR + 2 - numer][litera + 2] = ruch + 2;
		clear();;
	}
	if (ruch == 63) {
		printf("Gratulacje udalo Ci sie\n");
	}
	return 0;
}
void inicjalizacja(int tab[WYMIAR + 4][WYMIAR + 4]) {//funkcja inicjalizujaca tablice
	int i, j;
	for (i = 0; i < WYMIAR + 4; i++) {
		for (j = 0; j < WYMIAR + 4; j++) {
			tab[i][j] = 1;
		}
	}
	for (i = 2; i < WYMIAR + 2; i++) {
		for (j = 2; j < WYMIAR + 2; j++) {
			tab[i][j] = 0;
		}
	}
}
void plansza(int tab[WYMIAR + 4][WYMIAR + 4]) {//funkcja rysujaca szachownice
	int a, b, i, j, litery;
	printf("         ");
	for (i = 0; i < 56; i++) {
		printf("_");
	}
	printf("\n\t");

	for (i = 2; i < WYMIAR + 2; i++) {
		for (a = 0; a < 9; a++) {
			printf("|      ");
		}
		printf("\n%8d", WYMIAR + 2 - i);

		for (j = 2; j < WYMIAR + 2; j++) {
			printf("|  ");
			if (tab[i][j] == 0)
				printf("  ");
			else {
				if (tab[i][j] < 10) {
					printf(" %d", tab[i][j]);
				}
				else {
					printf("%d", tab[i][j]);
				}

			}
			printf("  ");
		}
		printf("|\n\t");
		for (b = 0; b < WYMIAR; b++) {
			printf("|______");
		}
		printf("|\n\t");
	}
	litery = 'a';
	printf("%5c", litery);
	for (litery = 'b'; litery < 'i'; litery++) {
		printf("%7c", litery);
	}
	printf("\n");
}
int mozliwosci(int tab[WYMIAR + 4][WYMIAR + 4], int litera, int numer) {//funkcja sprawdza czy instnie mozliwy ruch do wykonania
	int x = WYMIAR + 2 - numer;
	int y = litera + 2;
	if (tab[x - 1][y + 2] != 0 && tab[x + 1][y + 2] != 0 && tab[x - 2][y + 1] != 0 && tab[x + 2][y + 1] != 0 &&
		tab[x + 2][y - 1] != 0 && tab[x - 2][y - 1] != 0 && tab[x + 1][y - 2] != 0 && tab[x - 1][y - 2] != 0) {
		clear();
		printf("Przegrales nie ma juz mozliwego ruchu\n");
	}
	return 0;
}
int warunek(int tab[WYMIAR + 4][WYMIAR + 4], int litera, int numer, int stary_numer, int stara_litera, char c, int s) {//sprawdzenie czy ruch jest mozliwy
	if ((s != 2) || (numer < 1 || numer>8 || c<'a' || c>'h') || (tab[WYMIAR + 2 - numer][litera + 2] != 0) ||
		(((numer != stary_numer + 2) || ((litera != stara_litera + 1) && (litera != stara_litera - 1))) &&
		((numer != stary_numer + 1) || ((litera != stara_litera + 2) && (litera != stara_litera - 2))) &&
			((numer != stary_numer - 1) || ((litera != stara_litera + 2) && (litera != stara_litera - 2))) &&
			((numer != stary_numer - 2) || ((litera != stara_litera + 1) && (litera != stara_litera - 1))))) {
		return 1;
	}
	else {
		return 0;
	}
}
void clear() {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
	system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
	system("cls");
#endif
}
