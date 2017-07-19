#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>


using namespace std;

sf::RenderWindow okno(sf::VideoMode(800,800),"Szachy");
sf::Event wydarzenie;
sf::Vector2i pozycjaMyszy, nowaPozycjaMyszy;
//    sf::Vector2f pozycjaMyszyNaScenie;

sf::Texture tekstura, zaznaPola, bierki, zaznaAtak, gameOver;



sf::Sprite szachownica;
sf::Sprite graSkonczona;
sf::Sprite f[32];
sf::Sprite zaznaczeniePola[61];




bool graWToku = false;
bool czyBiale[32];
bool ruchBialych = true;
int czyPoleZaznaczone = 0;
bool warunkowy = false;


int nowaPozycja(int x, int y);
bool czyNastRPionka[16];
int zaznaczonyPionek = -1;
int maxZaznaczen = 0;

void czyKoniecGry (int c)
{
    for (int j = 30; j < 32; j++)
    {

        if (f[j].getPosition().x == zaznaczeniePola[c].getPosition().x && f[j].getPosition().y == zaznaczeniePola[c].getPosition().y && czyBiale[j] != ruchBialych)
        {
            okno.draw(graSkonczona);
            graSkonczona.setPosition(0,0);
        }

    }
}

int main()
{
    // ładowanie tekstur
    tekstura.loadFromFile( "images/szachownica.jpg" );
    zaznaPola.loadFromFile("images/zaznaPola.png");
    bierki.loadFromFile("images/bierki.png");
    zaznaAtak.loadFromFile("images/zaznaAtak.png");
    gameOver.loadFromFile("images/graSkonczona.png");

    szachownica.setTexture(tekstura);
    graSkonczona.setTexture(gameOver);

    for (int i = 0; i < 16; i++)
    {
        czyNastRPionka[i] = false;
    }

    for (int i = 0; i < 61; i++)
    {
        zaznaczeniePola[i].setTexture(zaznaPola);
    }


    for (int i = 0; i < 8; i++)
    {
        f[i].setTexture(bierki);
        //pobieranie grafiki konkretnego pionka | ponizej na tej samej zasadzie to dziala
        f[i].setTextureRect(sf::IntRect(500, 100, 100, 100));

        //przypisywanie id do tablicy | ponizej na tej samej zasadzie to dziala
    }

    //rysowanie bialych pionkow
    for (int i = 8; i < 16; i++)
    {
        f[i].setTexture(bierki);
        f[i].setTextureRect(sf::IntRect(500, 0, 100, 100));
    }

    //rysowanie czarnych wiez
    f[16].setTexture(bierki);
    f[16].setTextureRect(sf::IntRect(0, 100, 100, 100));

    f[17].setTexture(bierki);
    f[17].setTextureRect(sf::IntRect(0, 100, 100, 100));

    //rysowanie bialych wiez
    f[18].setTexture(bierki);
    f[18].setTextureRect(sf::IntRect(0, 0, 100, 100));

    f[19].setTexture(bierki);
    f[19].setTextureRect(sf::IntRect(0, 0, 100, 100));

    //rysowanie czarnych koni
    f[20].setTexture(bierki);
    f[20].setTextureRect(sf::IntRect(100, 100, 100, 100));

    f[21].setTexture(bierki);
    f[21].setTextureRect(sf::IntRect(100, 100, 100, 100));

    //rysowanie bialych koni
    f[22].setTexture(bierki);
    f[22].setTextureRect(sf::IntRect(100, 0, 100, 100));

    f[23].setTexture(bierki);
    f[23].setTextureRect(sf::IntRect(100, 0, 100, 100));

    //rysowanie czarnych goncow
    f[24].setTexture(bierki);
    f[24].setTextureRect(sf::IntRect(200, 100, 100, 100));

    f[25].setTexture(bierki);
    f[25].setTextureRect(sf::IntRect(200, 100, 100, 100));

    //rysowanie bialych goncow
    f[26].setTexture(bierki);
    f[26].setTextureRect(sf::IntRect(200, 0, 100, 100));

    f[27].setTexture(bierki);
    f[27].setTextureRect(sf::IntRect(200, 0, 100, 100));

    //rysowanie czarnego hetmana
    f[28].setTexture(bierki);
    f[28].setTextureRect(sf::IntRect(400, 100, 100, 100));

    //rysowanie bialego hetmana
    f[29].setTexture(bierki);
    f[29].setTextureRect(sf::IntRect(400, 0, 100, 100));

    //rysowanie czarnego krola
    f[30].setTexture(bierki);
    f[30].setTextureRect(sf::IntRect(300, 100, 100, 100));

    //rysowanie bialego krola
    f[31].setTexture(bierki);
    f[31].setTextureRect(sf::IntRect(300, 0, 100, 100));



    // główna pętla gry
    while(okno.isOpen())
    {
        //zamykanie gry
        while(okno.pollEvent(wydarzenie))
        {
            if(wydarzenie.type == sf::Event::KeyPressed && wydarzenie.key.code ==
                    sf::Keyboard::Escape)
                okno.close();
        }

        okno.draw(szachownica);



        //p pionków
        for (int i = 0; i < 32; i++)
        {
            okno.draw(f[i]);
        }
        if (graWToku == false)
        {

            //rysowanie czarnych pionkow

            for (int i = 0; i < 8; i++)
            {
                //ustawianie na konkrektnej pozycji | ponizej na tej samej zasadzie to dziala
                f[i].setPosition(100*i, 100);
                //przypisywanie id do tablicy | ponizej na tej samej zasadzie to dziala
                czyBiale[i] = false;
            }

            //rysowanie bialych pionkow
            for (int i = 8; i < 16; i++)
            {
                f[i].setPosition(100*(i-8), 600);
                czyBiale[i] = true;
            }

            //rysowanie czarnych wiez
            f[16].setPosition(0,0);
            czyBiale[16] = false;

            f[17].setPosition(700,0);
            czyBiale[17] = false;

            //rysowanie bialych wiez
            f[18].setPosition(0,700);
            czyBiale[18] = true;

            f[19].setPosition(700,700);
            czyBiale[19] = true;

            //rysowanie czarnych koni
            f[20].setPosition(100,0);
            czyBiale[20] = false;

            f[21].setPosition(600,0);
            czyBiale[21] = false;

            //rysowanie bialych koni
            f[22].setPosition(100,700);
            czyBiale[22] = true;

            f[23].setPosition(600,700);
            czyBiale[23] = true;

            //rysowanie czarnych goncow
            f[24].setPosition(200,0);
            czyBiale[24] = false;

            f[25].setPosition(500,0);
            czyBiale[25] = false;

            //rysowanie bialych goncow
            f[26].setPosition(200,700);
            czyBiale[26] = true;

            f[27].setPosition(500,700);
            czyBiale[27] = true;

            //rysowanie czarnego hetmana
            f[28].setPosition(300,000);
            czyBiale[28] = false;

            //rysowanie bialego hetmana
            f[29].setPosition(300,700);
            czyBiale[29] = true;

            //rysowanie czarnego krola
            f[30].setPosition(400,000);
            czyBiale[30] = false;

            //rysowanie bialego krola
            f[31].setPosition(400,700);
            czyBiale[31] = true;


        }
        graWToku = true;



        //pobieranie pozycji kliknięcia
//        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
//        {
//            pozycjaMyszy = sf::Mouse::getPosition( okno );
//            pozycjaMyszy.x = (pozycjaMyszy.x / 100) * 100;
//            pozycjaMyszy.y = (pozycjaMyszy.y / 100) * 100;
//
//            czyPoleZaznaczone = !czyPoleZaznaczone;
//
//
//        }
        if (wydarzenie.type == sf::Event::MouseButtonPressed)
        {
            if (wydarzenie.mouseButton.button == sf::Mouse::Left)
            {

                if ((wydarzenie.mouseButton.x / 100) * 100 != pozycjaMyszy.x || (wydarzenie.mouseButton.y / 100) * 100 != pozycjaMyszy.y)
                {
                    czyPoleZaznaczone++;
                }
                pozycjaMyszy.x = (wydarzenie.mouseButton.x / 100) * 100;
                pozycjaMyszy.y = (wydarzenie.mouseButton.y / 100) * 100;




            }


        }


        //zaznaczanie mozliwych ruchow
        if (czyPoleZaznaczone == 0)
        {

        }
        else if (czyPoleZaznaczone % 2 > 0)
        {
            for (int i = 0; i < 32; i++)
            {
                if (f[i].getPosition().x == pozycjaMyszy.x && f[i].getPosition().y == pozycjaMyszy.y)
                {
                    zaznaczonyPionek = i;
//zaznaczaie mozliwych ruchow
                    //zaznaczanie dla czarnych pionkow
                    if (i < 8)
                    {
                        if (czyNastRPionka[i] == false)
                        {
                            for (int j = 0; j < 2; j++)
                            {
                                for (int k = 0; k < 32; k++)
                                {


                                    if (f[i].getPosition().x == f[k].getPosition().x && f[i].getPosition().y+((j+1)*100) == f[k].getPosition().y)
                                    {
                                        j = 2;
                                        break;

                                    }

                                }
                                if (j != 2)
                                {
                                    okno.draw(zaznaczeniePola[j]);
                                    zaznaczeniePola[j].setPosition(f[i].getPosition().x,f[i].getPosition().y+((j+1)*100));
                                        //                                okno.draw(zaznaczeniePola);
                                        //                                zaznaczeniePola.setPosition(f[i].getPosition().x,f[i].getPosition().y+200);
                                    maxZaznaczen = j + 1;
                                }


                            }
                            for (int k = 0; k < 32; k++)
                            {
                                if (f[i].getPosition().x-100 == f[k].getPosition().x && f[i].getPosition().y+100 == f[k].getPosition().y && czyBiale[k] != ruchBialych)
                                {
                                    okno.draw(zaznaczeniePola[2]);
                                    zaznaczeniePola[2].setPosition(f[i].getPosition().x-100,f[i].getPosition().y+100);
                                    czyKoniecGry(2);
                                    maxZaznaczen = 3;
                                }
                                else if (f[i].getPosition().x+100 == f[k].getPosition().x && f[i].getPosition().y+100 == f[k].getPosition().y && czyBiale[k] != ruchBialych)
                                {
                                    okno.draw(zaznaczeniePola[3]);
                                    zaznaczeniePola[3].setPosition(f[i].getPosition().x+100,f[i].getPosition().y+100);
                                    czyKoniecGry(3);
                                    maxZaznaczen = 4;
                                }
                            }
                        }
                        else
                        {
                            for (int k = 0; k < 32; k++)
                            {
                                if (f[i].getPosition().x-100 == f[k].getPosition().x && f[i].getPosition().y+100 == f[k].getPosition().y && czyBiale[k] != ruchBialych)
                                {
                                    okno.draw(zaznaczeniePola[1]);
                                    zaznaczeniePola[1].setPosition(f[i].getPosition().x-100,f[i].getPosition().y+100);
                                    czyKoniecGry(1);
                                    maxZaznaczen = 2;
                                }
                                else if (f[i].getPosition().x+100 == f[k].getPosition().x && f[i].getPosition().y+100 == f[k].getPosition().y && czyBiale[k] != ruchBialych)
                                {
                                    okno.draw(zaznaczeniePola[2]);
                                    zaznaczeniePola[2].setPosition(f[i].getPosition().x+100,f[i].getPosition().y+100);
                                    czyKoniecGry(2);
                                    maxZaznaczen = 3;
                                }

                            }
                            for (int k = 0; k < 32; k++)
                            {
                                if (f[i].getPosition().x == f[k].getPosition().x && f[i].getPosition().y+100 == f[k].getPosition().y)
                                {
                                    warunkowy = true;
                                    break;
                                }

                            }
                            if (warunkowy != true)
                            {
                                okno.draw(zaznaczeniePola[0]);
                                zaznaczeniePola[0].setPosition(f[i].getPosition().x,f[i].getPosition().y+100);
                                maxZaznaczen += 1;
                            }
                            warunkowy = false;
                        }
                    }
                    //zaznaczanie dla bialych pionkow
                    else if (i >= 8 && i < 16)
                    {
                        if (czyNastRPionka[i] == false)
                        {
                            for (int j = 0; j < 2; j++)
                            {
                                for (int k = 0; k < 32; k++)
                                {


                                    if (f[i].getPosition().x == f[k].getPosition().x && f[i].getPosition().y-((j+1)*100) == f[k].getPosition().y)
                                    {
                                        j = 2;
                                        break;

                                    }

                                }
                                if (j != 2)
                                {
                                    okno.draw(zaznaczeniePola[j]);
                                    zaznaczeniePola[j].setPosition(f[i].getPosition().x,f[i].getPosition().y-((j+1)*100));
                                        //                                okno.draw(zaznaczeniePola);
                                        //                                zaznaczeniePola.setPosition(f[i].getPosition().x,f[i].getPosition().y+200);
                                    maxZaznaczen = j + 1;
                                }


                            }
                            for (int k = 0; k < 32; k++)
                            {
                                if (f[i].getPosition().x-100 == f[k].getPosition().x && f[i].getPosition().y-100 == f[k].getPosition().y && czyBiale[k] != ruchBialych)
                                {
                                    okno.draw(zaznaczeniePola[2]);
                                    zaznaczeniePola[2].setPosition(f[i].getPosition().x-100,f[i].getPosition().y-100);
                                    czyKoniecGry(2);
                                    maxZaznaczen = 3;
                                }
                                else if (f[i].getPosition().x+100 == f[k].getPosition().x && f[i].getPosition().y-100 == f[k].getPosition().y && czyBiale[k] != ruchBialych)
                                {
                                    okno.draw(zaznaczeniePola[3]);
                                    zaznaczeniePola[3].setPosition(f[i].getPosition().x+100,f[i].getPosition().y-100);
                                    czyKoniecGry(3);
                                    maxZaznaczen = 4;
                                }
                            }
                        }
                        else
                        {
                            for (int k = 0; k < 32; k++)
                            {
                                if (f[i].getPosition().x-100 == f[k].getPosition().x && f[i].getPosition().y-100 == f[k].getPosition().y && czyBiale[k] != ruchBialych)
                                {
                                    okno.draw(zaznaczeniePola[1]);
                                    zaznaczeniePola[1].setPosition(f[i].getPosition().x-100,f[i].getPosition().y-100);
                                    czyKoniecGry(1);
                                    maxZaznaczen = 2;
                                }
                                else if (f[i].getPosition().x+100 == f[k].getPosition().x && f[i].getPosition().y-100 == f[k].getPosition().y && czyBiale[k] != ruchBialych)
                                {
                                    okno.draw(zaznaczeniePola[2]);
                                    zaznaczeniePola[2].setPosition(f[i].getPosition().x+100,f[i].getPosition().y-100);
                                    czyKoniecGry(2);
                                    maxZaznaczen = 3;
                                }

                            }
                            for (int k = 0; k < 32; k++)
                            {
                                if (f[i].getPosition().x == f[k].getPosition().x && f[i].getPosition().y-100 == f[k].getPosition().y)
                                {
                                    warunkowy = true;
                                    break;
                                }

                            }
                            if (warunkowy != true)
                            {
                                okno.draw(zaznaczeniePola[0]);
                                zaznaczeniePola[0].setPosition(f[i].getPosition().x,f[i].getPosition().y-100);
                                maxZaznaczen += 1;
                            }
                            warunkowy = false;
                        }
                    }
                    //zaznaczanie wszystkich wiez
                    else if (i >= 16 && i < 20)
                    {
                        for (int j = 1; j < 8; j++)
                        {
                            for (int l = 1; l < 8; l++)
                            {
                                for (int k = 0; k < 32; k++)
                                {
                                    if (f[i].getPosition().x == f[k].getPosition().x && f[i].getPosition().y+(l*100) == f[k].getPosition().y)
                                    {
                                        if (czyBiale[i] == czyBiale[k])
                                        {
                                            maxZaznaczen = l-1;
                                            warunkowy = true;
                                            break;
                                        }
                                        else if (czyBiale[i] != czyBiale[k])
                                        {
                                            okno.draw(zaznaczeniePola[l-1]);
                                            zaznaczeniePola[l-1].setPosition(f[i].getPosition().x,f[i].getPosition().y+(l*100));
                                            czyKoniecGry(l-1);
                                            maxZaznaczen = l;
                                            warunkowy = true;
                                            break;
                                        }

                                    }

                                }
                                if (warunkowy != true)
                                {
                                    okno.draw(zaznaczeniePola[l-1]);
                                    zaznaczeniePola[l-1].setPosition(f[i].getPosition().x,f[i].getPosition().y+(l*100));
                                    maxZaznaczen = l;
                                }
                                else if (warunkowy == true)
                                {
                                    warunkowy = false;
                                    break;
                                }

                            }
                            for (int k = 0; k < 32; k++)
                                {
                                    if (f[i].getPosition().x == f[k].getPosition().x && f[i].getPosition().y-(j*100) == f[k].getPosition().y)
                                    {
                                        if (czyBiale[i] == czyBiale[k])
                                        {
                                            maxZaznaczen = j+5;
                                            warunkowy = true;
                                            break;
                                        }
                                        else if (czyBiale[i] != czyBiale[k])
                                        {
                                            okno.draw(zaznaczeniePola[j+6]);
                                            zaznaczeniePola[j+6].setPosition(f[i].getPosition().x,f[i].getPosition().y-(j*100));
                                            czyKoniecGry(j+6);
                                            maxZaznaczen = j+6;
                                            warunkowy = true;
                                            break;
                                        }
                                    }

                                }
                                if (warunkowy != true)
                                {
                                    okno.draw(zaznaczeniePola[j+6]);
                                    zaznaczeniePola[j+6].setPosition(f[i].getPosition().x,f[i].getPosition().y-(j*100));
                                    maxZaznaczen = j+6;
                                }
                                else if (warunkowy == true)
                                {
                                    warunkowy = false;
                                    break;
                                }
                        }
                        for (int j = 1; j < 8; j++)
                        {
                            for (int l = 1; l < 8; l++)
                            {
                                for (int k = 0; k < 32; k++)
                                {
                                    if (f[i].getPosition().x+(l*100) == f[k].getPosition().x && f[i].getPosition().y == f[k].getPosition().y)
                                    {
                                        if (czyBiale[i] == czyBiale[k])
                                        {
                                            maxZaznaczen = l+12;
                                            warunkowy = true;
                                            break;
                                        }
                                        else if (czyBiale[i] != czyBiale[k])
                                        {
                                            okno.draw(zaznaczeniePola[l+13]);
                                            zaznaczeniePola[l+13].setPosition(f[i].getPosition().x+(l*100),f[i].getPosition().y);
                                            maxZaznaczen = l+13;
                                            czyKoniecGry(l+13);
                                            warunkowy = true;
                                            break;
                                        }
                                    }

                                }
                                if (warunkowy != true)
                                {
                                    okno.draw(zaznaczeniePola[l+13]);
                                    zaznaczeniePola[l+13].setPosition(f[i].getPosition().x+(l*100),f[i].getPosition().y);
                                    maxZaznaczen = l+13;
                                }
                                else if (warunkowy == true)
                                {
                                    warunkowy = false;
                                    break;
                                }

                            }
                            for (int k = 0; k < 32; k++)
                                {
                                    if (f[i].getPosition().x-(j*100) == f[k].getPosition().x && f[i].getPosition().y == f[k].getPosition().y)
                                    {
                                        if (czyBiale[i] == czyBiale[k])
                                        {
                                            maxZaznaczen = j+19;
                                            warunkowy = true;
                                            break;
                                        }
                                        else if (czyBiale[i] != czyBiale[k])
                                        {
                                            okno.draw(zaznaczeniePola[j+20]);
                                            zaznaczeniePola[j+20].setPosition(f[i].getPosition().x-(j*100),f[i].getPosition().y);
                                            czyKoniecGry(j+20);
                                            maxZaznaczen = j+20;
                                            warunkowy = true;
                                            break;
                                        }
                                    }

                                }
                                if (warunkowy != true)
                                {
                                    okno.draw(zaznaczeniePola[j+20]);
                                    zaznaczeniePola[j+20].setPosition(f[i].getPosition().x-(j*100),f[i].getPosition().y);
                                    maxZaznaczen = j+20;
                                }
                                else if (warunkowy == true)
                                {
                                    warunkowy = false;
                                    break;
                                }
                        }
                    }
                    //zaznaczanie dla wszystkich koni
                    else if (i >= 20 && i < 24)
                    {
                        for (int k = 0; k < 32; k++)
                        {
                            if (f[i].getPosition().x+100 == f[k].getPosition().x && f[i].getPosition().y+200 == f[k].getPosition().y)
                            {
                                if (czyBiale[k] != czyBiale[i])
                                {
                                    okno.draw(zaznaczeniePola[0]);
                                    zaznaczeniePola[0].setPosition(f[i].getPosition().x+100,f[i].getPosition().y+200);
                                    czyKoniecGry(0);
                                    maxZaznaczen = 8;
                                    break;
                                }
                                else if (czyBiale[k] == czyBiale[i])
                                {
                                    break;
                                }
                            }
                            if (k == 31)
                            {
                                okno.draw(zaznaczeniePola[0]);
                                zaznaczeniePola[0].setPosition(f[i].getPosition().x+100,f[i].getPosition().y+200);
                                maxZaznaczen = 8;
                            }
                        }
                        for (int k = 0; k < 32; k++)
                        {
                            if (f[i].getPosition().x-100 == f[k].getPosition().x && f[i].getPosition().y+200 == f[k].getPosition().y)
                            {
                                if (czyBiale[k] != czyBiale[i])
                                {
                                    okno.draw(zaznaczeniePola[1]);
                                    zaznaczeniePola[1].setPosition(f[i].getPosition().x-100,f[i].getPosition().y+200);
                                    czyKoniecGry(1);
                                    maxZaznaczen = 8;
                                    break;
                                }
                                else if (czyBiale[k] == czyBiale[i])
                                {
                                    break;
                                }
                            }
                            if (k == 31)
                            {
                                okno.draw(zaznaczeniePola[1]);
                                zaznaczeniePola[1].setPosition(f[i].getPosition().x-100,f[i].getPosition().y+200);
                                maxZaznaczen = 8;
                            }
                        }
                        for (int k = 0; k < 32; k++)
                        {
                            if (f[i].getPosition().x-200 == f[k].getPosition().x && f[i].getPosition().y+100 == f[k].getPosition().y)
                            {
                                if (czyBiale[k] != czyBiale[i])
                                {
                                    okno.draw(zaznaczeniePola[2]);
                                    zaznaczeniePola[2].setPosition(f[i].getPosition().x-200,f[i].getPosition().y+100);
                                    czyKoniecGry(2);
                                    maxZaznaczen = 8;
                                    break;
                                }
                                else if(czyBiale[k] == czyBiale[i])
                                {
                                    break;
                                }
                            }
                            if (k == 31)
                            {
                                okno.draw(zaznaczeniePola[2]);
                                zaznaczeniePola[2].setPosition(f[i].getPosition().x-200,f[i].getPosition().y+100);
                                maxZaznaczen = 8;
                            }
                        }
                        for (int k = 0; k < 32; k++)
                        {
                            if (f[i].getPosition().x-200 == f[k].getPosition().x && f[i].getPosition().y-100 == f[k].getPosition().y)
                            {
                                if (czyBiale[k] != czyBiale[i])
                                {
                                    okno.draw(zaznaczeniePola[3]);
                                    zaznaczeniePola[3].setPosition(f[i].getPosition().x-200,f[i].getPosition().y-100);
                                    czyKoniecGry(3);
                                    maxZaznaczen = 8;
                                    break;
                                }
                                else if (czyBiale[k] == czyBiale[i])
                                {
                                    break;
                                }
                            }
                            if (k == 31)
                            {
                                okno.draw(zaznaczeniePola[3]);
                                zaznaczeniePola[3].setPosition(f[i].getPosition().x-200,f[i].getPosition().y-100);
                                maxZaznaczen = 8;
                            }
                        }

                        for (int k = 0; k < 32; k++)
                        {
                            if (f[i].getPosition().x-100 == f[k].getPosition().x && f[i].getPosition().y-200 == f[k].getPosition().y)
                            {
                                if (czyBiale[k] != czyBiale[i])
                                {
                                    okno.draw(zaznaczeniePola[4]);
                                    zaznaczeniePola[4].setPosition(f[i].getPosition().x-100,f[i].getPosition().y-200);
                                    czyKoniecGry(4);
                                    maxZaznaczen = 8;
                                    break;
                                }
                                else if (czyBiale[k] == czyBiale[i])
                                {
                                    break;
                                }
                            }
                            if (k == 31)
                            {
                                okno.draw(zaznaczeniePola[4]);
                                zaznaczeniePola[4].setPosition(f[i].getPosition().x-100,f[i].getPosition().y-200);
                                maxZaznaczen = 8;
                            }
                        }
                        for (int k = 0; k < 32; k++)
                        {
                            if (f[i].getPosition().x+100 == f[k].getPosition().x && f[i].getPosition().y-200 == f[k].getPosition().y)
                            {
                                if (czyBiale[k] != czyBiale[i])
                                {
                                    okno.draw(zaznaczeniePola[5]);
                                    zaznaczeniePola[5].setPosition(f[i].getPosition().x+100,f[i].getPosition().y-200);
                                    czyKoniecGry(5);
                                    maxZaznaczen = 8;
                                    break;
                                }
                                else if (czyBiale[k] == czyBiale[i])
                                {
                                    break;
                                }
                            }

                            if (k == 31)
                            {
                                okno.draw(zaznaczeniePola[5]);
                                zaznaczeniePola[5].setPosition(f[i].getPosition().x+100,f[i].getPosition().y-200);
                                maxZaznaczen = 8;
                            }
                        }
                        for (int k = 0; k < 32; k++)
                        {
                            if (f[i].getPosition().x+200 == f[k].getPosition().x && f[i].getPosition().y-100 == f[k].getPosition().y)
                            {
                                if ( czyBiale[k] != czyBiale[i])
                                {
                                    okno.draw(zaznaczeniePola[6]);
                                    zaznaczeniePola[6].setPosition(f[i].getPosition().x+200,f[i].getPosition().y-100);
                                    czyKoniecGry(6);
                                    maxZaznaczen = 8;
                                    break;
                                }
                                else if (czyBiale[k] == czyBiale[i])
                                {
                                    break;
                                }
                            }
                            if (k == 31)
                            {
                                okno.draw(zaznaczeniePola[6]);
                                zaznaczeniePola[6].setPosition(f[i].getPosition().x+200,f[i].getPosition().y-100);
                                maxZaznaczen = 8;
                            }
                        }

                        for (int k = 0; k < 32; k++)
                        {
                            if (f[i].getPosition().x+200 == f[k].getPosition().x && f[i].getPosition().y+100 == f[k].getPosition().y)
                            {
                                if (czyBiale[k] != czyBiale[i])
                                {
                                    okno.draw(zaznaczeniePola[7]);
                                    zaznaczeniePola[7].setPosition(f[i].getPosition().x+200,f[i].getPosition().y+100);
                                    czyKoniecGry(7);
                                    maxZaznaczen = 8;
                                    break;
                                }
                                else if (czyBiale[k] == czyBiale[i])
                                {
                                    break;
                                }
                            }
                            if (k == 31)
                            {
                                okno.draw(zaznaczeniePola[7]);
                                zaznaczeniePola[7].setPosition(f[i].getPosition().x+200,f[i].getPosition().y+100);
                                maxZaznaczen = 8;
                            }
                        }

                    }
                    //znaznaczanie dla wszystkich goncow
                    else if (i >= 24 && i < 28)
                    {
                        for (int j = 1; j < 8; j++)
                        {
                            for (int l = 1; l < 8; l++)
                            {
                                for (int k = 0; k < 32; k++)
                                {
                                    if (f[i].getPosition().x+(l*100) == f[k].getPosition().x && f[i].getPosition().y+(l*100) == f[k].getPosition().y)
                                    {
                                        if (czyBiale[i] == czyBiale[k])
                                        {
                                            maxZaznaczen = l-1;
                                            warunkowy = true;
                                            break;
                                        }
                                        else if (czyBiale[i] != czyBiale[k])
                                        {
                                            okno.draw(zaznaczeniePola[l-1]);
                                            zaznaczeniePola[l-1].setPosition(f[i].getPosition().x+(l*100),f[i].getPosition().y+(l*100));
                                            czyKoniecGry(l-1);
                                            maxZaznaczen = l;
                                            warunkowy = true;
                                            break;
                                        }

                                    }

                                }
                                if (warunkowy != true)
                                {
                                    okno.draw(zaznaczeniePola[l-1]);
                                    zaznaczeniePola[l-1].setPosition(f[i].getPosition().x+(l*100),f[i].getPosition().y+(l*100));
                                    maxZaznaczen = l;
                                }
                                else if (warunkowy == true)
                                {
                                    warunkowy = false;
                                    break;
                                }

                            }
                            for (int k = 0; k < 32; k++)
                                {
                                    if (f[i].getPosition().x+(j*100) == f[k].getPosition().x && f[i].getPosition().y-(j*100) == f[k].getPosition().y)
                                    {
                                        if (czyBiale[i] == czyBiale[k])
                                        {
                                            maxZaznaczen = j+5;
                                            warunkowy = true;
                                            break;
                                        }
                                        else if (czyBiale[i] != czyBiale[k])
                                        {
                                            okno.draw(zaznaczeniePola[j+6]);
                                            zaznaczeniePola[j+6].setPosition(f[i].getPosition().x+(j*100),f[i].getPosition().y-(j*100));
                                            czyKoniecGry(j+6);
                                            maxZaznaczen = j+6;
                                            warunkowy = true;
                                            break;
                                        }
                                    }

                                }
                                if (warunkowy != true)
                                {
                                    okno.draw(zaznaczeniePola[j+6]);
                                    zaznaczeniePola[j+6].setPosition(f[i].getPosition().x+(j*100),f[i].getPosition().y-(j*100));
                                    maxZaznaczen = j+6;
                                }
                                else if (warunkowy == true)
                                {
                                    warunkowy = false;
                                    break;
                                }
                        }
                        for (int j = 1; j < 8; j++)
                        {
                            for (int l = 1; l < 8; l++)
                            {
                                for (int k = 0; k < 32; k++)
                                {
                                    if (f[i].getPosition().x-(l*100) == f[k].getPosition().x && f[i].getPosition().y+(l*100) == f[k].getPosition().y)
                                    {
                                        if (czyBiale[i] == czyBiale[k])
                                        {
                                            maxZaznaczen = l+12;
                                            warunkowy = true;
                                            break;
                                        }
                                        else if (czyBiale[i] != czyBiale[k])
                                        {
                                            okno.draw(zaznaczeniePola[l+13]);
                                            zaznaczeniePola[l+13].setPosition(f[i].getPosition().x-(l*100),f[i].getPosition().y+(l*100));
                                            czyKoniecGry(l+13);
                                            maxZaznaczen = l+13;
                                            warunkowy = true;
                                            break;
                                        }
                                    }

                                }
                                if (warunkowy != true)
                                {
                                    okno.draw(zaznaczeniePola[l+13]);
                                    zaznaczeniePola[l+13].setPosition(f[i].getPosition().x-(l*100),f[i].getPosition().y+(l*100));
                                    maxZaznaczen = l+13;
                                }
                                else if (warunkowy == true)
                                {
                                    warunkowy = false;
                                    break;
                                }

                            }
                            for (int k = 0; k < 32; k++)
                                {
                                    if (f[i].getPosition().x-(j*100) == f[k].getPosition().x && f[i].getPosition().y-(j*100) == f[k].getPosition().y)
                                    {
                                        if (czyBiale[i] == czyBiale[k])
                                        {
                                            maxZaznaczen = j+19;
                                            warunkowy = true;
                                            break;
                                        }
                                        else if (czyBiale[i] != czyBiale[k])
                                        {
                                            okno.draw(zaznaczeniePola[j+20]);
                                            zaznaczeniePola[j+20].setPosition(f[i].getPosition().x-(j*100),f[i].getPosition().y-(j*100));
                                            czyKoniecGry(j+20);
                                            maxZaznaczen = j+20;
                                            warunkowy = true;
                                            break;
                                        }
                                    }

                                }
                                if (warunkowy != true)
                                {
                                    okno.draw(zaznaczeniePola[j+20]);
                                    zaznaczeniePola[j+20].setPosition(f[i].getPosition().x-(j*100),f[i].getPosition().y-(j*100));
                                    maxZaznaczen = j+20;
                                }
                                else if (warunkowy == true)
                                {
                                    warunkowy = false;
                                    break;
                                }
                        }
                    }
                    //zaznaczenie dla hetmanów
                    else if (i >=28 && i < 30)
                    {
                        for (int j = 1; j < 8; j++)
                        {
                            for (int l = 1; l < 8; l++)
                            {
                                for (int k = 0; k < 32; k++)
                                {
                                    if (f[i].getPosition().x == f[k].getPosition().x && f[i].getPosition().y+(l*100) == f[k].getPosition().y)
                                    {
                                        if (czyBiale[i] == czyBiale[k])
                                        {
                                            maxZaznaczen = l-1;
                                            warunkowy = true;
                                            break;
                                        }
                                        else if (czyBiale[i] != czyBiale[k])
                                        {
                                            okno.draw(zaznaczeniePola[l-1]);
                                            zaznaczeniePola[l-1].setPosition(f[i].getPosition().x,f[i].getPosition().y+(l*100));
                                            czyKoniecGry(l-1);
                                            maxZaznaczen = l;
                                            warunkowy = true;
                                            break;
                                        }

                                    }

                                }
                                if (warunkowy != true)
                                {
                                    okno.draw(zaznaczeniePola[l-1]);
                                    zaznaczeniePola[l-1].setPosition(f[i].getPosition().x,f[i].getPosition().y+(l*100));
                                    maxZaznaczen = l;
                                }
                                else if (warunkowy == true)
                                {
                                    warunkowy = false;
                                    break;
                                }

                            }
                            for (int k = 0; k < 32; k++)
                                {
                                    if (f[i].getPosition().x == f[k].getPosition().x && f[i].getPosition().y-(j*100) == f[k].getPosition().y)
                                    {
                                        if (czyBiale[i] == czyBiale[k])
                                        {
                                            maxZaznaczen = j+5;
                                            warunkowy = true;
                                            break;
                                        }
                                        else if (czyBiale[i] != czyBiale[k])
                                        {
                                            okno.draw(zaznaczeniePola[j+6]);
                                            zaznaczeniePola[j+6].setPosition(f[i].getPosition().x,f[i].getPosition().y-(j*100));
                                            czyKoniecGry(j+6);
                                            maxZaznaczen = j+6;
                                            warunkowy = true;
                                            break;
                                        }
                                    }

                                }
                                if (warunkowy != true)
                                {
                                    okno.draw(zaznaczeniePola[j+6]);
                                    zaznaczeniePola[j+6].setPosition(f[i].getPosition().x,f[i].getPosition().y-(j*100));
                                    maxZaznaczen = j+6;
                                }
                                else if (warunkowy == true)
                                {
                                    warunkowy = false;
                                    break;
                                }
                        }
                        for (int j = 1; j < 8; j++)
                        {
                            for (int l = 1; l < 8; l++)
                            {
                                for (int k = 0; k < 32; k++)
                                {
                                    if (f[i].getPosition().x+(l*100) == f[k].getPosition().x && f[i].getPosition().y == f[k].getPosition().y)
                                    {
                                        if (czyBiale[i] == czyBiale[k])
                                        {
                                            maxZaznaczen = l+12;
                                            warunkowy = true;
                                            break;
                                        }
                                        else if (czyBiale[i] != czyBiale[k])
                                        {
                                            okno.draw(zaznaczeniePola[l+13]);
                                            zaznaczeniePola[l+13].setPosition(f[i].getPosition().x+(l*100),f[i].getPosition().y);
                                            czyKoniecGry(l+13);
                                            maxZaznaczen = l+13;
                                            warunkowy = true;
                                            break;
                                        }
                                    }

                                }
                                if (warunkowy != true)
                                {
                                    okno.draw(zaznaczeniePola[l+13]);
                                    zaznaczeniePola[l+13].setPosition(f[i].getPosition().x+(l*100),f[i].getPosition().y);
                                    maxZaznaczen = l+13;
                                }
                                else if (warunkowy == true)
                                {
                                    warunkowy = false;
                                    break;
                                }

                            }
                            for (int k = 0; k < 32; k++)
                                {
                                    if (f[i].getPosition().x-(j*100) == f[k].getPosition().x && f[i].getPosition().y == f[k].getPosition().y)
                                    {
                                        if (czyBiale[i] == czyBiale[k])
                                        {
                                            maxZaznaczen = j+19;
                                            warunkowy = true;
                                            break;
                                        }
                                        else if (czyBiale[i] != czyBiale[k])
                                        {
                                            okno.draw(zaznaczeniePola[j+20]);
                                            zaznaczeniePola[j+20].setPosition(f[i].getPosition().x-(j*100),f[i].getPosition().y);
                                            czyKoniecGry(j+20);
                                            maxZaznaczen = j+20;
                                            warunkowy = true;
                                            break;
                                        }
                                    }

                                }
                                if (warunkowy != true)
                                {
                                    okno.draw(zaznaczeniePola[j+20]);
                                    zaznaczeniePola[j+20].setPosition(f[i].getPosition().x-(j*100),f[i].getPosition().y);
                                    maxZaznaczen = j+20;
                                }
                                else if (warunkowy == true)
                                {
                                    warunkowy = false;
                                    break;
                                }
                        }
                        /***************************/
                        for (int j = 1; j < 8; j++)
                        {
                            for (int l = 1; l < 8; l++)
                            {
                                for (int k = 0; k < 32; k++)
                                {
                                    if (f[i].getPosition().x+(l*100) == f[k].getPosition().x && f[i].getPosition().y+(l*100) == f[k].getPosition().y)
                                    {
                                        if (czyBiale[i] == czyBiale[k])
                                        {
                                            maxZaznaczen = l+26;
                                            warunkowy = true;
                                            break;
                                        }
                                        else if (czyBiale[i] != czyBiale[k])
                                        {
                                            okno.draw(zaznaczeniePola[l+26]);
                                            zaznaczeniePola[l+26].setPosition(f[i].getPosition().x+(l*100),f[i].getPosition().y+(l*100));
                                            czyKoniecGry(l+26);
                                            maxZaznaczen = l+26;
                                            warunkowy = true;
                                            break;
                                        }

                                    }

                                }
                                if (warunkowy != true)
                                {
                                    okno.draw(zaznaczeniePola[l+26]);
                                    zaznaczeniePola[l+26].setPosition(f[i].getPosition().x+(l*100),f[i].getPosition().y+(l*100));
                                    maxZaznaczen = l+26;
                                }
                                else if (warunkowy == true)
                                {
                                    warunkowy = false;
                                    break;
                                }

                            }
                            for (int k = 0; k < 32; k++)
                                {
                                    if (f[i].getPosition().x+(j*100) == f[k].getPosition().x && f[i].getPosition().y-(j*100) == f[k].getPosition().y)
                                    {
                                        if (czyBiale[i] == czyBiale[k])
                                        {
                                            maxZaznaczen = j+32;
                                            warunkowy = true;
                                            break;
                                        }
                                        else if (czyBiale[i] != czyBiale[k])
                                        {
                                            okno.draw(zaznaczeniePola[j+33]);
                                            zaznaczeniePola[j+33].setPosition(f[i].getPosition().x+(j*100),f[i].getPosition().y-(j*100));
                                            czyKoniecGry(j+33);
                                            maxZaznaczen = j+33;
                                            warunkowy = true;
                                            break;
                                        }
                                    }

                                }
                                if (warunkowy != true)
                                {
                                    okno.draw(zaznaczeniePola[j+33]);
                                    zaznaczeniePola[j+33].setPosition(f[i].getPosition().x+(j*100),f[i].getPosition().y-(j*100));
                                    maxZaznaczen = j+33;
                                }
                                else if (warunkowy == true)
                                {
                                    warunkowy = false;
                                    break;
                                }
                        }
                        for (int j = 1; j < 8; j++)
                        {
                            for (int l = 1; l < 8; l++)
                            {
                                for (int k = 0; k < 32; k++)
                                {
                                    if (f[i].getPosition().x-(l*100) == f[k].getPosition().x && f[i].getPosition().y+(l*100) == f[k].getPosition().y)
                                    {
                                        if (czyBiale[i] == czyBiale[k])
                                        {
                                            maxZaznaczen = l+39;
                                            warunkowy = true;
                                            break;
                                        }
                                        else if (czyBiale[i] != czyBiale[k])
                                        {
                                            okno.draw(zaznaczeniePola[l+40]);
                                            zaznaczeniePola[l+40].setPosition(f[i].getPosition().x-(l*100),f[i].getPosition().y+(l*100));
                                            czyKoniecGry(l+40);
                                            maxZaznaczen = l+40;
                                            warunkowy = true;
                                            break;
                                        }
                                    }

                                }
                                if (warunkowy != true)
                                {
                                    okno.draw(zaznaczeniePola[l+40]);
                                    zaznaczeniePola[l+40].setPosition(f[i].getPosition().x-(l*100),f[i].getPosition().y+(l*100));
                                    maxZaznaczen = l+40;
                                }
                                else if (warunkowy == true)
                                {
                                    warunkowy = false;
                                    break;
                                }

                            }
                            for (int k = 0; k < 32; k++)
                                {
                                    if (f[i].getPosition().x-(j*100) == f[k].getPosition().x && f[i].getPosition().y-(j*100) == f[k].getPosition().y)
                                    {
                                        if (czyBiale[i] == czyBiale[k])
                                        {
                                            maxZaznaczen = j+46;
                                            warunkowy = true;
                                            break;
                                        }
                                        else if (czyBiale[i] != czyBiale[k])
                                        {
                                            okno.draw(zaznaczeniePola[j+47]);
                                            zaznaczeniePola[j+47].setPosition(f[i].getPosition().x-(j*100),f[i].getPosition().y-(j*100));
                                            czyKoniecGry(j+47);
                                            maxZaznaczen = j+47;
                                            warunkowy = true;
                                            break;
                                        }
                                    }

                                }
                                if (warunkowy != true)
                                {
                                    okno.draw(zaznaczeniePola[j+47]);
                                    zaznaczeniePola[j+47].setPosition(f[i].getPosition().x-(j*100),f[i].getPosition().y-(j*100));
                                    maxZaznaczen = j+47;
                                }
                                else if (warunkowy == true)
                                {
                                    warunkowy = false;
                                    break;
                                }
                        }
                    }
                    //zaznaczanie dla kroli
                    else if (i >=30 && i <32)
                    {

                        for (int k = 0; k < 32; k++)
                        {
                            if (f[i].getPosition().x+100 == f[k].getPosition().x && f[i].getPosition().y == f[k].getPosition().y)
                            {
                                if (czyBiale[k] != czyBiale[i])
                                {
                                    okno.draw(zaznaczeniePola[0]);
                                    zaznaczeniePola[0].setPosition(f[i].getPosition().x+100,f[i].getPosition().y);
                                    czyKoniecGry(0);
                                    maxZaznaczen = 8;
                                    break;
                                }
                                else if (czyBiale[k] == czyBiale[i])
                                {
                                    break;
                                }
                            }
                            if (k == 31)
                            {
                                okno.draw(zaznaczeniePola[0]);
                                zaznaczeniePola[0].setPosition(f[i].getPosition().x+100,f[i].getPosition().y);
                                maxZaznaczen = 8;
                            }
                        }
                        for (int k = 0; k < 32; k++)
                        {
                            if (f[i].getPosition().x-100 == f[k].getPosition().x && f[i].getPosition().y == f[k].getPosition().y)
                            {
                                if (czyBiale[k] == czyBiale[i])
                                {
                                    okno.draw(zaznaczeniePola[1]);
                                    zaznaczeniePola[1].setPosition(f[i].getPosition().x-100,f[i].getPosition().y);
                                    czyKoniecGry(1);
                                    maxZaznaczen = 8;
                                    break;
                                }
                                else if (czyBiale[k] == czyBiale[i])
                                {
                                    break;
                                }
                            }
                            if (k == 31)
                            {
                                okno.draw(zaznaczeniePola[1]);
                                zaznaczeniePola[1].setPosition(f[i].getPosition().x-100,f[i].getPosition().y);
                                maxZaznaczen = 8;
                            }
                        }
                        for (int k = 0; k < 32; k++)
                        {
                            if (f[i].getPosition().x == f[k].getPosition().x && f[i].getPosition().y+100 == f[k].getPosition().y)
                            {
                                if (czyBiale[k] != czyBiale[i])
                                {
                                    okno.draw(zaznaczeniePola[2]);
                                    zaznaczeniePola[2].setPosition(f[i].getPosition().x,f[i].getPosition().y+100);
                                    czyKoniecGry(2);
                                    maxZaznaczen = 8;
                                    break;
                                }
                                else if(czyBiale[k] == czyBiale[i])
                                {
                                    break;
                                }
                            }
                            if (k == 31)
                            {
                                okno.draw(zaznaczeniePola[2]);
                                zaznaczeniePola[2].setPosition(f[i].getPosition().x,f[i].getPosition().y+100);
                                maxZaznaczen = 8;
                            }
                        }
                        for (int k = 0; k < 32; k++)
                        {
                            if (f[i].getPosition().x == f[k].getPosition().x && f[i].getPosition().y-100 == f[k].getPosition().y)
                            {
                                if (czyBiale[k] != czyBiale[i])
                                {
                                    okno.draw(zaznaczeniePola[3]);
                                    zaznaczeniePola[3].setPosition(f[i].getPosition().x,f[i].getPosition().y-100);
                                    czyKoniecGry(3);
                                    maxZaznaczen = 8;
                                    break;
                                }
                                else if (czyBiale[k] == czyBiale[i])
                                {
                                    break;
                                }
                            }
                            if (k == 31)
                            {
                                okno.draw(zaznaczeniePola[3]);
                                zaznaczeniePola[3].setPosition(f[i].getPosition().x,f[i].getPosition().y-100);
                                maxZaznaczen = 8;
                            }
                        }

                        for (int k = 0; k < 32; k++)
                        {
                            if (f[i].getPosition().x-100 == f[k].getPosition().x && f[i].getPosition().y-100 == f[k].getPosition().y)
                            {
                                if (czyBiale[k] != czyBiale[i])
                                {
                                    okno.draw(zaznaczeniePola[4]);
                                    zaznaczeniePola[4].setPosition(f[i].getPosition().x-100,f[i].getPosition().y-100);
                                    czyKoniecGry(4);
                                    maxZaznaczen = 8;
                                    break;
                                }
                                else if (czyBiale[k] == czyBiale[i])
                                {
                                    break;
                                }
                            }
                            if (k == 31)
                            {
                                okno.draw(zaznaczeniePola[4]);
                                zaznaczeniePola[4].setPosition(f[i].getPosition().x-100,f[i].getPosition().y-100);
                                maxZaznaczen = 8;
                            }
                        }
                        for (int k = 0; k < 32; k++)
                        {
                            if (f[i].getPosition().x+100 == f[k].getPosition().x && f[i].getPosition().y-100 == f[k].getPosition().y)
                            {
                                if (czyBiale[k] != czyBiale[i])
                                {
                                    okno.draw(zaznaczeniePola[5]);
                                    zaznaczeniePola[5].setPosition(f[i].getPosition().x+100,f[i].getPosition().y-100);
                                    czyKoniecGry(5);
                                    maxZaznaczen = 8;
                                    break;
                                }
                                else if (czyBiale[k] == czyBiale[i])
                                {
                                    break;
                                }
                            }

                            if (k == 31)
                            {
                                okno.draw(zaznaczeniePola[5]);
                                zaznaczeniePola[5].setPosition(f[i].getPosition().x+100,f[i].getPosition().y-100);
                                maxZaznaczen = 8;
                            }
                        }
                        for (int k = 0; k < 32; k++)
                        {
                            if (f[i].getPosition().x+100 == f[k].getPosition().x && f[i].getPosition().y+100 == f[k].getPosition().y)
                            {
                                if ( czyBiale[k] != czyBiale[i])
                                {
                                    okno.draw(zaznaczeniePola[6]);
                                    zaznaczeniePola[6].setPosition(f[i].getPosition().x+100,f[i].getPosition().y+100);
                                    czyKoniecGry(6);
                                    maxZaznaczen = 8;
                                    break;
                                }
                                else if (czyBiale[k] == czyBiale[i])
                                {
                                    break;
                                }
                            }
                            if (k == 31)
                            {
                                okno.draw(zaznaczeniePola[6]);
                                zaznaczeniePola[6].setPosition(f[i].getPosition().x+100,f[i].getPosition().y+100);
                                maxZaznaczen = 8;
                            }
                        }

                        for (int k = 0; k < 32; k++)
                        {
                            if (f[i].getPosition().x-100 == f[k].getPosition().x && f[i].getPosition().y+100 == f[k].getPosition().y)
                            {
                                if (czyBiale[k] != czyBiale[i])
                                {
                                    okno.draw(zaznaczeniePola[7]);
                                    zaznaczeniePola[7].setPosition(f[i].getPosition().x-100,f[i].getPosition().y+100);
                                    czyKoniecGry(7);
                                    maxZaznaczen = 8;
                                    break;
                                }
                                else if (czyBiale[k] == czyBiale[i])
                                {
                                    break;
                                }
                            }
                            if (k == 31)
                            {
                                okno.draw(zaznaczeniePola[7]);
                                zaznaczeniePola[7].setPosition(f[i].getPosition().x-100,f[i].getPosition().y+100);
                                maxZaznaczen = 8;
                            }
                        }
                    }



                }
            }


        }

        //zmiana pozycji
        else if (czyPoleZaznaczone % 2 == 0)
        {
            if (czyBiale[zaznaczonyPionek] == ruchBialych)
            {

                for (int i = 0; i < maxZaznaczen; i++)
                {
                    if (pozycjaMyszy.x == zaznaczeniePola[i].getPosition().x && pozycjaMyszy.y == zaznaczeniePola[i].getPosition().y)
                    {


                        f[zaznaczonyPionek].setPosition(pozycjaMyszy.x,pozycjaMyszy.y);

                        if (zaznaczonyPionek < 16)
                        {
                            czyNastRPionka[zaznaczonyPionek] = true;
                        }
                        czyPoleZaznaczone = 0;
                        ruchBialych = !ruchBialych;

                    }
                    else if (pozycjaMyszy.x != zaznaczeniePola[i].getPosition().x || pozycjaMyszy.y != zaznaczeniePola[i].getPosition().y)
                    {
                        ruchBialych = ruchBialych;
                    }

                    for (int j = 0; j < 32; j++)
                        {

                            if (f[j].getPosition().x == f[zaznaczonyPionek].getPosition().x && f[j].getPosition().y == f[zaznaczonyPionek].getPosition().y && j != zaznaczonyPionek)
                            {
                                f[j].setPosition(1000,1000);
                                break;
                            }

                        }







                }
                maxZaznaczen = 0;

            }

        }



        okno.display();

    }

    return 0;

}
