#include <iostream>
#include <cstdlib>



void wywolaj_logo();
void mapa1(char pp1[][80], int& gw, int& gk, int cele1[][2], int& n, int& ile_ruchow, char p_pp1[][100]);
void mapa2(char pp2[][80], int& gw, int& gk, int cele2[][2], int& n, int& ile_ruchow, char p_pp2[][100]);
void mapa3(char pp3[][80], int& gw, int& gk, int cele3[][2], int& n, int& ile_ruchow, char p_pp3[][100]);
void mapa4(char pp4[][80], int& gw, int& gk, int cele4[][2], int& n, int& ile_ruchow, char p_pp4[][100]);
void mapa5(char pp5[][80], int& gw, int& gk, int cele5[][2], int& n, int& ile_ruchow, char p_pp5[][100]);

void sterowanie(bool& test_menu, char menu, int ile_posuniec, int wiersz_G, int kolumna_G, char p[][80], int cele[][2],
    bool test_wygrana, int ile_celow, bool zaliczenie[], char mapa, bool& brak_ruchow, char pelna_p[][100], char nr);
void wchodzenie_w_sciane(int& ile_posuniec); //funkcja ktora wyswietli powiadomienie o zlym ruchu
void ruch(char pp[][80], char pelna_p[][100], int y, int x);
void test_X(char pp[][80], int cele[][2], bool& wygrana, int n, char p_pp[][100]);


int main()
{
    char menu = ' ', test_mapa, nr;
    bool test_menu = false, test_gra = true, test_wybor = false, test_wygrana = false, brak_ruchow = false;
    bool zaliczenie[4] = { false, false, false, false }; // ta tablica bedzie sprawdzac czy gracz przeszedl poprzednie etapy
    char p[25][80];  // ta tablica bedzie sie wyswietlac w trakcie gry i bedzie mozna ja przesuwac, jest wycinkiem tablicy ponizej
    char pelna_p[30][100]; //to jest tablica wieksza od ekranu
    int wiersz_G = 4, kolumna_G = 4, ile_celow = 0, ile_posuniec = 0;
    int cele[3][2];

    // Poczatek glownej petli ktora jest menu
    while (test_gra == true)
    {
        std::cout << "Zbyszko Stachecki s193621" << std::endl;

        std::cout << std::endl << std::endl;
        wywolaj_logo();

        std::cout << std::endl << std::endl << "Witaj w grze Sokoban, wybierz jedna z opcji i zaakceptuj klawiszem enter";
        std::cout << std::endl << "Aby wyjsc z gry wybierz: E";
        std::cout << std::endl << std::endl << "Pamietaj, ze aby wybrac dany poziom musisz najpierw przejsc poprzednie!" << std::endl;
        std::cout << std::endl << "Aby wybrac poziom 1, wybierz: 1";
        std::cout << std::endl << "Aby wybrac poziom 2, wybierz: 2";
        std::cout << std::endl << "Aby wybrac poziom 3, wybierz: 3";
        std::cout << std::endl << "Aby wybrac poziom 4, wybierz: 4";
        std::cout << std::endl << "Aby wybrac poziom 5, wybierz: 5";
        std::cout << std::endl << std::endl << std::endl;
        std::cin >> test_mapa;

        // Wychodzenie z gry 
        if (test_mapa == 'e' || test_mapa == 'E') {
            test_gra = false;
            test_menu = false;
        }
        if (test_mapa == '1' || (test_mapa == '2' && zaliczenie[0] == true) || (test_mapa == '3' && zaliczenie[1] == true)
            || (test_mapa == '4' && zaliczenie[2] == true) || (test_mapa == '5' && zaliczenie[3] == true)) //sprawdzanie czy gracza przeszedl poprzednie etapy
            test_menu = true;

        for (int i = 0; i < 3; i++) { //zerowanie pozycji X z poprzednich map
            cele[i][0] = 0;
            cele[i][1] = 0;
        }


        if (test_menu == true)
        {
            system("cls");

            std::cout << "Gra Sokoban zmienila sie od swojego powstania." << std::endl << "Teraz w magazynie pracuje juz nie magazynier, a dron : @"
                << std::endl << "Twoim celem jest przeniesc skrzynki : 0, w wyznaczone miejsca : X";
            std::cout << std::endl << std::endl << "Aby kontyunowac wcisnij ENTER";
            (void)getchar(); (void)getchar();

            do {
                if (test_mapa == '1') {
                    system("cls");
                    mapa1(p, wiersz_G, kolumna_G, cele, ile_celow, ile_posuniec, pelna_p);
                    test_wybor = true;
                }
                else if (test_mapa == '2' && zaliczenie[0] == true) {
                    system("cls");
                    mapa2(p, wiersz_G, kolumna_G, cele, ile_celow, ile_posuniec, pelna_p);
                    test_wybor = true;
                }
                else if (test_mapa == '3' && zaliczenie[1] == true) { //na tym poziomie bedzie mozna najlepiej przetestowac funkcje przewijania mapy
                    system("cls");
                    mapa3(p, wiersz_G, kolumna_G, cele, ile_celow, ile_posuniec, pelna_p);
                    test_wybor = true;
                }
                else if (test_mapa == '4' && zaliczenie[2] == true) {
                    system("cls");
                    mapa4(p, wiersz_G, kolumna_G, cele, ile_celow, ile_posuniec, pelna_p);
                    test_wybor = true;
                }
                else if (test_mapa == '5' && zaliczenie[3] == true) {
                    system("cls");
                    mapa5(p, wiersz_G, kolumna_G, cele, ile_celow, ile_posuniec, pelna_p);
                    test_wybor = true;
                }
                else
                    std::cin >> test_mapa;
            } while (test_wybor == false);
            test_wybor = false;
            nr = test_mapa;

            sterowanie(test_menu, menu, ile_posuniec, wiersz_G, kolumna_G, p,
                cele, test_wygrana, ile_celow, zaliczenie, test_mapa, brak_ruchow, pelna_p, nr);

            while (brak_ruchow == true) { //ponowne wywolywanie mapy po skonczeniu sie ruchow
                system("cls");
                if (test_mapa == '1')
                    mapa1(p, wiersz_G, kolumna_G, cele, ile_celow, ile_posuniec, pelna_p);
                if (test_mapa == '2')
                    mapa2(p, wiersz_G, kolumna_G, cele, ile_celow, ile_posuniec, pelna_p);
                if (test_mapa == '3')
                    mapa3(p, wiersz_G, kolumna_G, cele, ile_celow, ile_posuniec, pelna_p);
                if (test_mapa == '4')
                    mapa4(p, wiersz_G, kolumna_G, cele, ile_celow, ile_posuniec, pelna_p);
                if (test_mapa == '5')
                    mapa5(p, wiersz_G, kolumna_G, cele, ile_celow, ile_posuniec, pelna_p);

                test_menu = true;
                sterowanie(test_menu, menu, ile_posuniec, wiersz_G, kolumna_G, p,
                    cele, test_wygrana, ile_celow, zaliczenie, test_mapa, brak_ruchow, pelna_p, nr);
            }

            test_wygrana = false;
        }
        (void)getchar();
        system("cls");

    }
    std::cout << std::endl << std::endl << "Milego dnia! ;33" << std::endl;
    return 0;
}

void mapa1(char pp1[][80], int& gw, int& gk, int cele1[][2], int& n, int& ile_ruchow, char p_pp1[][100])
{
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 100; j++) {
            if ((i == 0 || i == 19) && j < 32)
                p_pp1[i][j] = '~';
            else if (i == 3 && j == 4) {
                p_pp1[i][j] = '@';
                gw = i;
                gk = j;
            }
            else if (i == 3 && j == 7)
                p_pp1[i][j] = '0';
            else if (i == 3 && j == 9)
                p_pp1[i][j] = 'X';
            else
                p_pp1[i][j] = ' ';

            if (i < 20) {
                p_pp1[i][0] = '|';
                p_pp1[i][31] = '|';
            }
            if (i == 29 || j == 99) //Przyda sie do wyznaczania granicy przesuwania mapy
                p_pp1[i][j] = '*';

            if (i < 25 && j < 80)
                pp1[i][j] = p_pp1[i][j];
        }
    }
    cele1[0][0] = 3; cele1[0][1] = 9;
    n = 1; ile_ruchow = 6;
}

void mapa2(char pp2[][80], int& gw, int& gk, int cele2[][2], int& n, int& ile_ruchow, char p_pp2[][100])
{
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            if ((i == 0 || i == 24) && j < 80)
                p_pp2[i][j] = '~';
            else if (i == 7 && j == 40) {
                p_pp2[i][j] = '@';
                gw = i;
                gk = j;
            }
            else if ((i == 4 && j == 35) || (i == 4 && j == 36) || (i == 4 && j == 38))
                p_pp2[i][j] = '0';
            else if ((i == 5 && j == 34) || (i == 3 && j == 36) || (i == 3 && j == 39)) {
                p_pp2[i][j] = 'X';
            }
            else
                p_pp2[i][j] = ' ';

            if (i < 25) {
                p_pp2[i][0] = '|';
                p_pp2[i][79] = '|';
            }
            if (i == 29 || j == 99) //Przyda sie do wyznaczania granicy przesuwania mapy
                p_pp2[i][j] = '*';

            if (i < 25 && j < 80)
                pp2[i][j] = p_pp2[i][j];
        }
    }
    cele2[0][0] = 5; cele2[0][1] = 34;
    cele2[1][0] = 3; cele2[1][1] = 36;
    cele2[2][0] = 3; cele2[2][1] = 39;
    n = 3; ile_ruchow = 70;
}

void mapa3(char pp3[][80], int& gw, int& gk, int cele3[][2], int& n, int& ile_ruchow, char p_pp3[][100])
{
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 100; j++) {
            if (i == 0 || i == 29)
                p_pp3[i][j] = '~';
            else if (i == 24 && j == 78) {
                p_pp3[i][j] = '@';
                gw = i;
                gk = j;
            }
            else if ((i == 3 && j == 96) || (i == 4 && j == 96))
                p_pp3[i][j] = '0';
            else if ((i == 3 && j == 97) || (i == 4 && j == 97))
                p_pp3[i][j] = 'X';
            else {
                p_pp3[i][j] = ' ';
                p_pp3[i][0] = '|';
                p_pp3[i][99] = '|';
            }

            if (i < 25 && j < 80)
                pp3[i][j] = p_pp3[i][j];
        }
    }
    cele3[0][0] = 3; cele3[0][1] = 97;
    cele3[1][0] = 4; cele3[1][1] = 97;
    n = 2; ile_ruchow = 100;
}

void mapa4(char pp4[][80], int& gw, int& gk, int cele4[][2], int& n, int& ile_ruchow, char p_pp4[][100])
{
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 100; j++) {
            if ((i == 0 || i == 20) && j < 92)
                p_pp4[i][j] = '~';
            else if (i == 4 && j == 90) {
                p_pp4[i][j] = '@';
                gw = i;
                gk = j;
            }
            else if (i == 17 && j == 88)
                p_pp4[i][j] = '0';
            else if (i == 19 && j == 88)
                p_pp4[i][j] = 'X';
            else {
                p_pp4[i][j] = ' ';
                if (i <= 20) {
                    p_pp4[i][0] = '|';
                    p_pp4[i][92] = '|';
                }
            }

            if (i < 25 && j < 80)
                pp4[i][j] = p_pp4[i][j];
        }
    }
    cele4[0][0] = 19; cele4[0][1] = 88;
    n = 1; ile_ruchow = 50;
}

void mapa5(char pp5[][80], int& gw, int& gk, int cele5[][2], int& n, int& ile_ruchow, char p_pp5[][100])
{
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 100; j++) {
            if ((i == 0 || i == 29) && j < 50)
                p_pp5[i][j] = '~';
            else if (i == 28 && j == 3) {
                p_pp5[i][j] = '@';
                gw = i;
                gk = j;
            }
            else if (i == 5 && j == 5)
                p_pp5[i][j] = '0';
            else if (i == 5 && j == 10)
                p_pp5[i][j] = 'X';
            else {
                p_pp5[i][j] = ' ';
                p_pp5[i][0] = '|';
                p_pp5[i][50] = '|';

            }

            if (i < 25 && j < 80)
                pp5[i][j] = p_pp5[i][j];
        }
    }
    cele5[0][0] = 5; cele5[0][1] = 10;
    n = 1; ile_ruchow = 40;
}

void sterowanie(bool& test_menu, char menu, int ile_posuniec, int wiersz_G, int kolumna_G, char p[][80], int cele[][2],
    bool test_wygrana, int ile_celow, bool zaliczenie[], char mapa, bool& brak_ruchow, char pelna_p[][100], char nr)
{
    int y = 0, x = 0; //zmienne ktora pomoga przy przesuwaniu mapy, y - w pionie, x - w poziomie
    char bufor = ' ';

    std::cout << std::endl;
    brak_ruchow = false;


    while (test_menu == true)
    {
        system("cls");

        std::cout << std::endl << "Uzywaj klawiszow WSAD aby poruszac sie postacia: @" << std::endl
            << "Symbolem: # oznaczone sa skrzynki ktore dotarly na miejsce";
        std::cout << std::endl << "Aby przesuwac mape uzywaj klawiszy J,K,I,M (oznaczajace odpowiednio: lewo, prawo, gora, dol";
        std::cout << std::endl << std::endl << "Wybierz: Q aby wrocic do menu";
        std::cout << std::endl << "Aby rozpoczac etap od nowa, wcisnij: T";

        std::cout << std::endl << std::endl << "Pozostala ilosc ruchow: " << ile_posuniec << std::endl;

        test_X(p, cele, test_wygrana, ile_celow, pelna_p);

        if (test_wygrana == true) {
            system("cls");
            std::cout << std::endl << "Udalo Ci sie przejsc ten etap. Brawo!!!";
            std::cout << std::endl << "Aby powrocic do wyboru poziomow, wcisnij: ENTER" << std::endl;
            test_menu = false;
            (void)getchar();
            if (nr == '1')
                zaliczenie[0] = true;
            else if (nr == '2')
                zaliczenie[1] = true;
            else if (nr == '3')
                zaliczenie[2] = true;
            else if (nr == '4')
                zaliczenie[3] = true;
            break;
        }

        if (ile_posuniec == 0 && test_wygrana != true && menu != 't' && menu != 'T') { //koniec ruchow
            system("cls");
            std::cout << std::endl << "Skonczyly Ci sie ruchy!" << std::endl << "Aby rozpoczac od nowa, wcisnij: ENTER" << std::endl;
            (void)getchar(); (void)getchar();
            brak_ruchow = true;
            test_menu = false;
        }

        ruch(p, pelna_p, y, x); //Ta funkcja wywoluje mape co kazdy ruch
        std::cin >> menu;

        //-----Tutaj jest kod odpowiedzialny za poruszanie sie
        if (menu == 'w' || menu == 'W') {
            if (pelna_p[wiersz_G - 1][kolumna_G] == ' ' || pelna_p[wiersz_G - 1][kolumna_G] == 'X')
            {
                pelna_p[wiersz_G - 1][kolumna_G] = '@';
                pelna_p[wiersz_G][kolumna_G] = bufor;
                wiersz_G = wiersz_G - 1;
            }
            else if ((pelna_p[wiersz_G - 1][kolumna_G] == '0' || pelna_p[wiersz_G - 1][kolumna_G] == '#') && pelna_p[wiersz_G - 2][kolumna_G] != '~'
                && pelna_p[wiersz_G - 2][kolumna_G] != '0' && pelna_p[wiersz_G - 2][kolumna_G] != '#')
            {
                pelna_p[wiersz_G - 1][kolumna_G] = '@';
                pelna_p[wiersz_G - 2][kolumna_G] = '0';
                pelna_p[wiersz_G][kolumna_G] = bufor;
                wiersz_G = wiersz_G - 1;
            }
            else {
                wchodzenie_w_sciane(ile_posuniec);
            }
        }

        if (menu == 's' || menu == 'S') {
            if (pelna_p[wiersz_G + 1][kolumna_G] == ' ' || pelna_p[wiersz_G + 1][kolumna_G] == 'X')
            {
                pelna_p[wiersz_G + 1][kolumna_G] = '@';
                pelna_p[wiersz_G][kolumna_G] = bufor;
                wiersz_G = wiersz_G + 1;
            }
            else if ((pelna_p[wiersz_G + 1][kolumna_G] == '0' || pelna_p[wiersz_G + 1][kolumna_G] == '#') && pelna_p[wiersz_G + 2][kolumna_G] != '~'
                && pelna_p[wiersz_G + 2][kolumna_G] != '0' && pelna_p[wiersz_G + 2][kolumna_G] != '#')
            {
                pelna_p[wiersz_G + 1][kolumna_G] = '@';
                pelna_p[wiersz_G + 2][kolumna_G] = '0';
                pelna_p[wiersz_G][kolumna_G] = bufor;
                wiersz_G = wiersz_G + 1;
            }
            else {
                wchodzenie_w_sciane(ile_posuniec);
            }
        }

        if (menu == 'a' || menu == 'A')
        {
            if (pelna_p[wiersz_G][kolumna_G - 1] == ' ' || pelna_p[wiersz_G][kolumna_G - 1] == 'X')
            {
                pelna_p[wiersz_G][kolumna_G - 1] = '@';
                pelna_p[wiersz_G][kolumna_G] = bufor;
                kolumna_G = kolumna_G - 1;
            }
            else if ((pelna_p[wiersz_G][kolumna_G - 1] == '0' || pelna_p[wiersz_G][kolumna_G - 1] == '#') && pelna_p[wiersz_G][kolumna_G - 2] != '|'
                && pelna_p[wiersz_G][kolumna_G - 2] != '0' && pelna_p[wiersz_G][kolumna_G - 2] != '#')
            {
                pelna_p[wiersz_G][kolumna_G - 1] = '@';
                pelna_p[wiersz_G][kolumna_G - 2] = '0';
                pelna_p[wiersz_G][kolumna_G] = bufor;
                kolumna_G = kolumna_G - 1;
            }
            else {
                wchodzenie_w_sciane(ile_posuniec);
            }
        }

        if (menu == 'd' || menu == 'D') {
            if (pelna_p[wiersz_G][kolumna_G + 1] == ' ' || pelna_p[wiersz_G][kolumna_G + 1] == 'X')
            {
                pelna_p[wiersz_G][kolumna_G + 1] = '@';
                pelna_p[wiersz_G][kolumna_G] = bufor;
                kolumna_G = kolumna_G + 1;
            }
            else if ((pelna_p[wiersz_G][kolumna_G + 1] == '0' || pelna_p[wiersz_G][kolumna_G + 1] == '#')
                && pelna_p[wiersz_G][kolumna_G + 2] != '|' && pelna_p[wiersz_G][kolumna_G + 2] != '0'
                && pelna_p[wiersz_G][kolumna_G + 2] != '#')
            {
                pelna_p[wiersz_G][kolumna_G + 1] = '@';
                pelna_p[wiersz_G][kolumna_G + 2] = '0';
                pelna_p[wiersz_G][kolumna_G] = bufor;
                kolumna_G = kolumna_G + 1;
            }
            else {
                wchodzenie_w_sciane(ile_posuniec);
            }
        }

        //------Tutaj jest kod do poruszania mapy
        if (menu == 'j' || menu == 'J') { //Mozna przesuwac o ile mapa nie jest juz u lewej krawedzi
            ++ile_posuniec;
            if (p[1][0] != '|')
                --x;
        }
        if (menu == 'k' || menu == 'K') { //Mozna przesuwac o ile mapa nie jest juz u prawej krawedzi
            ++ile_posuniec;
            if (p[1][79] != '*' && p[0][79] != '|')
                ++x;
        }
        if (menu == 'i' || menu == 'I') { //Mozna przesuwac o ile mapa nie jest juz u gornej krawedzi
            ++ile_posuniec;
            if (p[0][1] != '~')
                --y;
        }
        if (menu == 'm' || menu == 'M') { //Mozna przesuwac o ile mapa nie jest juz u dolnej krawedzi
            ++ile_posuniec;
            if (p[24][1] != '*' && p[24][1] != '~')
                ++y;
        }



        if (menu == 't' || menu == 'T') { //resetowanie mapy
            system("cls");
            brak_ruchow = true;
            test_menu = false;
        }

        if (menu == 'q' || menu == 'Q') //wychodzenie do menu
            test_menu = false;

        --ile_posuniec;
    }
}

void test_X(char pp[][80], int cele[][2], bool& wygrana, int n, char p_pp[][100]) //ta funkcja nadpisuje zmazane X z planszy + sprawdza wygrana
{
    int spelnione_cele = 0;

    for (int i = 0; i < 3; i++) {
        if (p_pp[cele[i][0]][cele[i][1]] == ' ')
            p_pp[cele[i][0]][cele[i][1]] = 'X';
        else if (p_pp[cele[i][0]][cele[i][1]] == '0' || p_pp[cele[i][0]][cele[i][1]] == '#') {
            p_pp[cele[i][0]][cele[i][1]] = '#';
            spelnione_cele++;
        }
    }
    if (spelnione_cele == n)
        wygrana = true;
}

void ruch(char pp[][80], char pelna_p[][100], int y, int x) //ta funkcja wyswietla zmieniona po kazdym ruchu plansze
{
    std::cout << std::endl;
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 80; j++) {
            pp[i][j] = pelna_p[i + y][j + x];
            std::cout << pp[i][j];
        }
        std::cout << std::endl;
    }
}

void wchodzenie_w_sciane(int& ile_posuniec)
{
    system("cls");
    std::cout << std::endl << "Nie mozesz wejsc w sciane, ani przesuwac paru skrzynek na raz!!!";
    std::cout << std::endl << "Wcisnij ENTER aby kontyunowac";
    (void)getchar(); (void)getchar();
    ++ile_posuniec;
}

void wywolaj_logo()
{
    /* Tablice przechowuj¹ce liczby odpowiadaj¹ce literom z tablicy ASCII,
    32 - spacja, 83 - S, 79 - O, 75 - K, 66 - B, 65 - A, 78 - N */
    int litera_S[10][11] = { {32,32,32,83,83,83,83,32,32,32},{32,83,83,32,32,32,32,83,83,32},
                {83,83,32,32,32,32,32,32,83,83},{32,32,32,32,32,32,32,83,83,32},
                {32,32,32,32,32,83,83,32,32,32},{32,32,32,83,83,32,32,32,32,32},
                {32,83,83,32,32,32,32,32,32,32},{83,83,32,32,32,32,32,32,83,83},
                {32,83,83,32,32,32,32,83,83,32},{32,32,32,83,83,83,83,32,32,32} };

    int litera_O[10][11] = { {32,32,32,32,79,79,79,32,32,32,32}, {32,32,79,79,32,32,32,79,79,32,32},
                {79,79,32,32,32,32,32,32,32,79,79}, {79,79,32,32,32,32,32,32,32,79,79},
                {79,79,32,32,32,32,32,32,32,79,79}, {79,79,32,32,32,32,32,32,32,79,79},
                {79,79,32,32,32,32,32,32,32,79,79}, {79,79,32,32,32,32,32,32,32,79,79},
                {32,32,79,79,32,32,32,79,79,32,32}, {32,32,32,32,79,79,79,32,32,32,32} };

    int litera_K[10][11] = { {75,75,32,32,32,32,32,75,75,32,32}, {75,75,32,32,32,32,75,75,32,32,32},
                {75,75,32,32,32,75,75,32,32,32,32}, {75,75,32,32,75,75,32,32,32,32,32},
                {75,75,75,75,32,32,32,32,32,32,32}, {75,75,32,32,75,75,32,32,32,32,32},
                {75,75,32,32,32,75,75,32,32,32,32}, {75,75,32,32,32,32,75,75,32,32,32},
                {75,75,32,32,32,32,32,75,75,32,32}, {75,75,32,32,32,32,32,32,75,75,32} };

    int litera_B[10][11] = { {66,66,66,66,66,66,32,32,32,32,32}, {66,66,32,32,32,32,66,66,32,32,32},
                {66,66,32,32,32,32,32,66,66,32,32}, {66,66,32,32,32,32,32,32,66,66,32},
                {66,66,32,32,32,32,32,66,66,32,32}, {66,66,66,66,66,66,66,32,32,32,32},
                {66,66,32,32,32,32,66,66,32,32,32}, {66,66,32,32,32,32,32,66,66,32,32},
                {66,66,32,32,32,32,66,66,32,32,32}, {66,66,66,66,66,66,32,32,32,32,32} };

    int litera_A[10][11] = { {32,32,32,65,65,65,65,32,32,32,32}, {32,32,65,65,32,32,65,65,32,32,32},
                {32,65,65,32,32,32,32,65,65,32,32}, {65,65,32,32,32,32,32,32,65,65,32},
                {65,65,32,32,32,32,32,32,65,65,32}, {65,65,32,32,32,32,32,32,65,65,32},
                {65,65,65,65,65,65,65,65,65,65,32}, {65,65,32,32,32,32,32,32,65,65,32},
                {65,65,32,32,32,32,32,32,65,65,32}, {65,65,32,32,32,32,32,32,65,65,32} };

    int litera_N[10][11] = { {78,78,32,32,32,32,32,32,32,78,78}, {78,78,78,78,32,32,32,32,32,78,78},
                {78,78,32,78,78,32,32,32,32,78,78}, {78,78,32,32,78,78,32,32,32,78,78},
                {78,78,32,32,78,78,32,32,32,78,78}, {78,78,32,32,32,78,78,32,32,78,78},
                {78,78,32,32,32,78,78,32,32,78,78}, {78,78,32,32,32,32,78,78,32,78,78},
                {78,78,32,32,32,32,32,78,78,78,78}, {78,78,32,32,32,32,32,32,32,78,78} };

    char wypisz;

    for (int i = 0; i < 10; i++) // Wypisywanie loga SOKOBAN 
    {
        for (int j = 0; j < 11; j++) {
            wypisz = (char)litera_S[i][j];
            std::cout << wypisz;
        }
        std::cout << "  ";

        for (int j = 0; j < 11; j++) {
            wypisz = (char)litera_O[i][j];
            std::cout << wypisz;
        }
        std::cout << "  ";

        for (int j = 0; j < 11; j++) {
            wypisz = (char)litera_K[i][j];
            std::cout << wypisz;
        }

        for (int j = 0; j < 11; j++) {
            wypisz = (char)litera_O[i][j];
            std::cout << wypisz;
        }
        std::cout << "  ";

        for (int j = 0; j < 11; j++) {
            wypisz = (char)litera_B[i][j];
            std::cout << wypisz;
        }
        std::cout << " ";

        for (int j = 0; j < 11; j++) {
            wypisz = (char)litera_A[i][j];
            std::cout << wypisz;
        }
        std::cout << "  ";

        for (int j = 0; j < 11; j++) {
            wypisz = (char)litera_N[i][j];
            std::cout << wypisz;
        }
        std::cout << std::endl;
    }
}