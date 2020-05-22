#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

void NowaPlansza(char** plansza, int rozmiar);
void Wyswietl(char** plansza, int rozmiar);
bool Wolne(char** macierz,int wiersz, int kolumna);
void Ruch(char** macierz,int rozmiar, int& Ilosc_ruchow, int& wiersz, int& kolumna);
int wygrana(char** macierz, int rozmiar, int ilosc, int wiersz, int kolumna);
void Latwy(char** macierz, int rozmiar, int& wiersz, int& kolumna, int& Ilosc_ruchow);
int maxx(int a,int b);
int minx(int a,int b);
int MiniMax(char** macierz, int glebokosc, int rozmiar,int ilosc,int wiersz, int kolumna ,int Ilosc_ruchow, bool gracz, int alpha, int beta);
void NajlepszyRuch (char** macierz, int rozmiar, int ilosc, int& wiersz, int& kolumna, int& Ilosc_ruchow);


int main()
{
    char** plansza;
    int wiersz , kolumna, kto = 0, czy_byl_ruch, rozmiar, ile, ilosc, poziom;

	
	do // wczytanie rozmiaru
	{
		cout << "Podaj rozmiar (conajmniej 3): " << endl;
	    cin >> rozmiar;
    	ile = rozmiar * rozmiar;
	} while (rozmiar < 3);
	
	do // wczytanie ilości znaków potrzebnych do zwycięstwa
	{
		cout << "Podaj ilość znaków potrzebnych do zwycięstwa (od 3 do " << rozmiar << "): " << endl;
    	cin >> ilosc;
		if (ilosc < 0 || ilosc > rozmiar)
		cout << "Błędna wartość" << endl;
	}while(ilosc < 0 || ilosc > rozmiar);
	
	do // wczyyanie poziomu trudności
	{
		cout << "Wybierz poziom trudności: " << endl;
		cout << " 1 - Łatwy " << endl;
		cout << " 2 - Trudny " << endl;
    	cin >> poziom;
		if (poziom < 1 || poziom > 2)
		cout << "Błędna wartość" << endl;
	}while(poziom < 1 || poziom > 2);

	NowaPlansza(plansza, rozmiar);
    Wyswietl(plansza, rozmiar);
    

        do // sprawdzenie końca gry
		{
        	do // sprawdzenie czy odbył się ruch
			{
	            czy_byl_ruch = ile;
    	        Ruch(plansza, rozmiar, ile, wiersz, kolumna);
        	    Wyswietl(plansza, rozmiar);
            }while(ile==czy_byl_ruch);

            kto = wygrana(plansza, rozmiar, ilosc, wiersz, kolumna);
            if (kto == -1 || ile == 0)
			{
				break;
			}
			if (poziom == 1)
			{
				do // sprawdzenie czy odbył się ruch
				{
	    	        czy_byl_ruch = ile;
	        	    Latwy(plansza, rozmiar, wiersz, kolumna, ile);
    	    	}while(ile==czy_byl_ruch);
        	    Wyswietl(plansza, rozmiar);
            	kto = wygrana(plansza, rozmiar, ilosc, wiersz, kolumna);
				if (kto == 1 || ile == 0)
				{
					break;
				}
			}
			if(poziom == 2)
			{
				do // sprawdzenie czy odbył się ruch
				{
	    	        czy_byl_ruch = ile;
	        	    NajlepszyRuch(plansza, rozmiar, ilosc, wiersz, kolumna, ile);
    	    	}while(ile==czy_byl_ruch);
        	    Wyswietl(plansza, rozmiar);
            	kto = wygrana(plansza, rozmiar, ilosc, wiersz, kolumna);
				if (kto == 1 || ile == 0)
				{
					break;
				}
			}

        }while(kto != 1 && kto != -1 && ile != 0);
    
    if (kto == -1)
    cout << "Brawo wygrałeś" << endl;
    else if (kto == 1)
    cout << "Nastepnym razem się uda" << endl;
    else if (ile == 0)
    cout << "Remis" << endl;
}


//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////



void NowaPlansza(char** macierz, int rozmiar) 	// tworzy planszę o podanym rozmiarze
	{
		for (int i = 0; i < rozmiar; i++)
		{
			macierz[i] = new char[rozmiar];
			for (int j = 0; j < rozmiar; j++)
			{
				macierz[i][j] = ' ';
			}
		}
	}

void Wyswietl(char** macierz, int rozmiar)		// wyświetla planszę
	{
        cout << endl;
		for (int i = 0; i < rozmiar; i++)
		{
            cout << " | ";
			for (int j = 0; j < rozmiar; j++)
			{
				cout << macierz[i][j] << " | ";
                
			}
			cout << endl;
            cout << endl;
			
		}
        cout << endl;
	}

bool Wolne(char** macierz,int wiersz, int kolumna) 	// sprawdza czy możliwe jest wpisanie znaku w to miejsce
	{
		if (macierz[wiersz][kolumna] == 'O' || macierz[wiersz][kolumna] == 'X')
		{
			cout << "W tym polu znajduje się już znak" << endl;
			return false;
		}
		return true;
    }

void Ruch(char** macierz, int rozmiar, int& Ilosc_ruchow, int& wiersz, int& kolumna) 	// wykonuje ruch gracza 
	{
        cout << "Podaj nr wiersza: ";
	    cin >> wiersz;
    	wiersz--;
        cout << "Podaj nr kolumny: ";
        cin >> kolumna;
    	kolumna--;
        if (kolumna >= 0 && kolumna < rozmiar && wiersz >= 0 && wiersz < rozmiar 
        && true == Wolne(macierz, wiersz, kolumna)){
		macierz[wiersz][kolumna] = 'X';
        Ilosc_ruchow--;
        }
        else{
        cout << "Podaj współrzędne innego wonego miejsca" << endl;
        }
	}

bool remis(int Ilosc_ruchow)	// sprawdza czy nie skończyły się ruchy
	{
		
		if (Ilosc_ruchow == 0)
			return true;
		else
			return false;
	}

int wygrana(char** macierz,int rozmiar, int ilosc, int wiersz, int kolumna) // wyszukuje zwycięzcę
{
	int ileX = 0; 
    int ileO = 0;
	if(macierz[wiersz][kolumna] == 'X')
	{
		for (int i = 0; i < ilosc; i++)   //Sprawdzamy pionowo
		{
			if (wiersz + i < rozmiar && macierz[wiersz + i][kolumna] == 'X') {
        	    ileX++;
            	if (ileX == ilosc)
				return -1;}
            else{
    			for (int j = 1; j < ilosc; j++){
                    if (wiersz - j >= 0 && macierz[wiersz - j][kolumna] == 'X')
                    ileX++;
					else
					{
						ileX = 0;
						break;
						}
                    if (ileX == ilosc)
    		    	return -1;
				
                }
            }
		}
	
		ileX = 0;

		for (int i = 0; i < ilosc; i++)   //Sprawdzamy poziomo
		{
			if (kolumna + i < rozmiar && macierz[wiersz][kolumna + i] == 'X') {
            ileX++;
            if (ileX == ilosc)
			return -1;}
            else{
    			for (int j = 1; j < ilosc; j++){
                    if (kolumna - j >= 0 && macierz[wiersz][kolumna - j] == 'X') 
                    ileX++;
					else
					{
						ileX = 0;
						break;
						}
                    if (ileX == ilosc)
    		    	return -1;
                }
            }
		}

		ileX = 0;

        for (int i = 0; i < ilosc; i++)   //Sprawdzamy 1 przekątną
		{
			if (kolumna + i < rozmiar && wiersz + i < rozmiar && macierz[wiersz + i][kolumna + i] == 'X') {
            ileX++;
            if (ileX == ilosc)
			return -1;}
            else{
   				for (int j = 1; j < ilosc; j++){
                    if (kolumna - j >= 0 && wiersz - j >= 0 && macierz[wiersz -j][kolumna - j] == 'X') 
                    ileX++;
					else
					{
						ileX = 0;
						break;
						}
                    if (ileX == ilosc)
    		    	return -1;
                }
            }
		}

		ileX = 0;

		for (int i = 0; i < ilosc; i++)   //Sprawdzamy 2 przekątną
		{
			if (kolumna - i >= 0 && wiersz + i < rozmiar && macierz[wiersz + i][kolumna - i] == 'X') {
            ileX++;
            if (ileX == ilosc)
			return -1;}
            else{
    			for (int j = 1; j < ilosc; j++){
                    if (kolumna + j < rozmiar && wiersz - j >= 0 && macierz[wiersz -j][kolumna + j] == 'X') 
                    ileX++;
					else
					{
						ileX = 0;
						break;
						}
                    if (ileX == ilosc)
    		    	return -1;
				}
			}
		}
	}
	if(macierz[wiersz][kolumna] == 'O')
	{
		for (int i = 0; i < ilosc; i++)   //Sprawdzamy pionowo
		{
			if (wiersz + i < rozmiar && macierz[wiersz + i][kolumna] == 'O'){ 
            ileO++;
            if (ileO == ilosc)
			return 1;}
            else{
    			for (int j = 1; j < ilosc; j++){
                    if (wiersz - j >= 0 && macierz[wiersz - j][kolumna] == 'O') 
                    ileO++;
					else
					{
						ileO = 0;
						break;
						}
                    if (ileO == ilosc)
    		    	return 1;
                    
                }
            }
		}

		ileO = 0;

		for (int i = 0; i < ilosc; i++)   //Sprawdzamy poziomo
		{
			if (kolumna + i < rozmiar && macierz[wiersz][kolumna + i] == 'O') {
            ileO++;
            if (ileO == ilosc)
			return 1;}
            else{
    			for (int j = 1; j < ilosc; j++){
                    if (kolumna - j >= 0 && macierz[wiersz][kolumna - j] == 'O') 
                    ileO++;
					else
					{
						ileO = 0;
						break;
						}
                    if (ileO == ilosc)
    		    	return 1;
                }
            }
		}

		ileO = 0;

        for (int i = 0; i < ilosc; i++)   //Sprawdzamy 1 przekątną
		{
			if (kolumna + i < rozmiar && wiersz + i < rozmiar && macierz[wiersz + i][kolumna + i] == 'O') {
            ileO++;
            if (ileO == ilosc)
			return 1;}
            else{
    			for (int j = 1; j < ilosc; j++){
                    if (kolumna - j >= 0 && wiersz - j >= 0 && macierz[wiersz -j][kolumna - j] == 'O') 
                    ileO++;
					else
					{
						ileO = 0;
						break;
						}
                    if (ileO == ilosc)
    		    	return 1;
                }
            }
		}

		ileO = 0;

		for (int i = 0; i < ilosc; i++)   //Sprawdzamy 2 przekątną
		{
			if (kolumna - i >= 0 && wiersz + i < rozmiar && macierz[wiersz + i][kolumna - i] == 'O') {
            ileO++;
            if (ileO == ilosc)
			return 1;}
            else{
    			for (int j = 1; j < ilosc; j++){
                    if (kolumna + j < rozmiar && wiersz - j >= 0 && macierz[wiersz -j][kolumna + j] == 'O') 
                    ileO++;
					else
					{
						ileO = 0;
						break;
						}
                    if (ileO == ilosc)
    		    	return 1;
                }
            }
		}
	}
	return 0;
	}
	
void Latwy(char** macierz, int rozmiar, int& wiersz, int& kolumna, int& Ilosc_ruchow) // wpisuje w losowe wolne miejsce znak
	{
			wiersz = rand() % rozmiar ;
			kolumna = rand() % rozmiar ;

		if (macierz[wiersz][kolumna] == ' '){
		macierz[wiersz][kolumna] = 'O';
        Ilosc_ruchow--;
        }
	}

// minmax
int MiniMax(char** macierz, int glebokosc, int rozmiar,int ilosc,int wiersz, int kolumna ,int Ilosc_ruchow, bool gracz, int alpha, int beta)
{
    int wynik = wygrana(macierz,rozmiar, ilosc, wiersz, kolumna);
	if (wynik == 1)
	return 100 - glebokosc;
	if (wynik == -1)
	return -100 + glebokosc;

	if(remis(Ilosc_ruchow))
	return 0;

	if (glebokosc == 2 * ilosc)
	return 0;

    	if(gracz){
		int najlepsze = -1000;
		for(int i = 0; i < rozmiar; i++){
			for(int j = 0;j < rozmiar; j++){


				if(macierz[i][j] == ' '){
					macierz[i][j] = 'O';
					Ilosc_ruchow--;
					int val = MiniMax(macierz, glebokosc + 1, rozmiar, ilosc, i, j , Ilosc_ruchow, false, alpha, beta);
					najlepsze = maxx(najlepsze,val);
					alpha = maxx(najlepsze,alpha);
					macierz[i][j] = ' ';
					Ilosc_ruchow++;
					if(beta <= alpha)
						break;
				}
				if(beta <= alpha)
					break;
			}
		}
		return najlepsze;
	}else{
		int najlepsze = 1000;
		for(int i = 0; i < rozmiar; i++){
			for(int j = 0;j < rozmiar; j++){
				if(macierz[i][j] == ' '){
					macierz[i][j] = 'X';
					Ilosc_ruchow--;
					int val = MiniMax(macierz, glebokosc + 1, rozmiar, ilosc, i, j , Ilosc_ruchow, true, alpha, beta);
					najlepsze = minx(najlepsze,val);
					beta = minx(najlepsze,beta);
					macierz[i][j] = ' ';
					Ilosc_ruchow++;
					if(beta <= alpha)
						break;
				}
				if(beta <= alpha)
					break;
			}
		}

		return najlepsze;
	}

}

int maxx(int a,int b)	// znajduje większą wartość
{
	if(a > b){
		return a;
	}
	return b;
}



int minx(int a,int b)	// znajduje mniejszą wartość
{
	if(a < b){
		return a;
	}
	return b;
}

// wyszukuje najlepszy ruch i wykonuje go z urzyciem minmax
void NajlepszyRuch (char** macierz, int rozmiar, int ilosc, int& wiersz, int& kolumna, int& Ilosc_ruchow)
{
	int naj = -1000;
	int alpha = -1000;
	int beta = 1000;
    int x, y;

    for(int i = 0; i < rozmiar; i++)
		{
        for(int j = 0; j < rozmiar; j++)
            if(macierz[i][j] == ' ')
            {
                macierz[i][j] = 'O';
				Ilosc_ruchow--;
                int ruch =MiniMax(macierz, 0, rozmiar, ilosc, i, j, Ilosc_ruchow, false, alpha, beta); 
                macierz [i][j] = ' ';
				Ilosc_ruchow++;
                if(ruch > naj)
                {
                    wiersz = i;
				    kolumna = j;
                	naj = ruch;
                }

        	}
		}
macierz[wiersz][kolumna] = 'O';
--Ilosc_ruchow;

}