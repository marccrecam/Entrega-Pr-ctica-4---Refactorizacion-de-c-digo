#include <iostream>

using namespace std;
//Atributos del enemigo1
bool enemy1IsAlive = true;
int enemy1HP = 1000;
int enemyDamage;
int atack;
string enemyname = "Malo";
//Atributos del heroe
string heroName;
int heroHP = 5000;
bool heroIsAlive = true;
int escoger = 0;
int heroDamage;
//Atributos del enemigo2
bool villanoIsAlive = true;
int villanoHP = 1000;
int villanoDamage;
int attack;
string enemyname2 = "Malisimo";
//ataques especiales 
int espada = 350;
int golpe = 250;
int magia = 500;
int limitado = 2;
int ataque;
//variables pelea
int vida;

void gameStart() {
    cout << "El enemigo " << enemyname << " y " << enemyname2 << " acaban de aparecer\nY tienen " << enemy1HP << " puntos de vida \n";
    cout << "Inserta el nombre del heroe que lo va a derrotar\n";
    cin >> heroName;
    cout << "\nEl nombre del heroe es: " << heroName << "\n";
}
int enemyChoose() {
    escoger = 0;
    //PREGUNTAMOS A QUE ENEMIGO QUEREMOS REALIZAR EL ATAQUE
    cout << "A que enemigo quieres atacar [1/2]\n";
    cin >> escoger;
    //EN EL CASO DE SELCCIONAR UN NUMERO INCORRECTO NOS LO VA A VOLVER A PREGUNTAR HASTA QUE ESTE LO ESTE
    while (escoger != 1 && escoger != 2)
        //TENEMOS EL ENEMIGO SELECCIONADO
        if (escoger == 1 || escoger == 2) {
            cout << "Lanzas un ataque al enemigo " << escoger << "\n\n";
            return escoger;
        }
        else if (escoger != 1 && escoger != 2) {
            cout << "El enemigo escogido no existe\n";
            cout << "A que enemigo quieres atacar [1/2]\n";
            cin >> escoger;
        }
}
void attackChose(int& enemyHP) {
    if (ataque == 1) {
        enemyHP = enemyHP - espada;
    }
    else if (ataque == 2) {
        enemyHP = enemyHP - golpe;
    }
    else if (ataque == 3) {
        if (limitado != 0) {
            enemyHP = enemyHP - magia;
            limitado -= 1;
        }
        else {
            cout << "no has podido atacar con el ataque especial de magia porque no te quedan usos restantes\n";
        }
    }
    else
    {
        "Has fallado, este ataque no existe";
    }
}
bool checkStatus(bool& enemyIsAlive, int& enemyHP, string& enemynamef) {
    if (enemyHP <= 0) {
        enemyHP = 0;
        enemyIsAlive = false;
        cout << "Has derrotado al " << enemynamef << "\n";
    }
    else {
        return true;
    }
}
void  atackChoose() {
    //ESCOGEMOS EL ATAQUE QUE QUEREMOS REALIZAR
    cout << "Que ataque quieres realizar:\n" "Espada[1]\n" "Golpe[2]\n" "Magia[3] Quedan " << limitado << " ataques restantes\n";
    cin >> ataque;
    //ATACAMOS AL ENEMIGO 1 Y TAMBIÉN COMPROBAMOS SI ESTA VIVO O ESTA MUERTO
    if (enemy1IsAlive) {
        if (escoger == 1) {
            attackChose(enemy1HP);
            enemy1IsAlive = checkStatus(enemy1IsAlive, enemy1HP, enemyname);
        }
    }
    else {
        cout << "\nEl " << enemyname << " esta muerto no puedes segir atacandole, has perdido el turno\n";
    }

    //ATACAMOS AL ENEMIGO 2 Y TAMBIÉN COMPROBAMOS SI ESTA VIVO O ESTA MUERTO
    if (villanoIsAlive) {
        if (escoger == 2) {
            attackChose(villanoHP);
            villanoIsAlive = checkStatus(villanoIsAlive, villanoHP, enemyname2);
        }
    }
    else {
        cout << "\nEl " << enemyname2 << " esta muerto no puedes segir atacandole, has perdido el turno\n";
    }

    cout << "\nAl " << enemyname << " le quedan " << enemy1HP << " puntos de vida\n";
    cout << "\nAl " << enemyname2 << " le quedan " << villanoHP << " puntos de vida\n";
}

void enemiesAttack() {
    enemyDamage = rand() % 999 + 30;
    villanoDamage = rand() % 999 + 30;
    if (enemy1IsAlive && villanoIsAlive) {
        vida = enemyDamage + villanoDamage;
        heroHP = heroHP - vida;
        if (heroHP <= 0) {
            heroHP = 0;
        }
        cout << "\nLos enemigos te han hecho " << vida << " te quedan " << heroHP << " puntos de vida\n\n";
    }
    else if (enemy1IsAlive && villanoIsAlive == false) {
        heroHP = heroHP - enemyDamage;
        if (heroHP <= 0) {
            heroHP = 0;
        }
        cout << "\nEl " << enemyname << " te ha hecho " << enemyDamage << " te quedan " << heroHP << " puntos de vida\n\n";
    }
    else if (enemy1IsAlive == false && villanoIsAlive) {
        heroHP = heroHP - villanoDamage;
        if (heroHP <= 0) {
            heroHP = 0;
        }
        cout << "\nEl " << enemyname2 << " te ha hecho " << villanoDamage << " te quedan " << heroHP << " puntos de vida\n\n";
    }
    else if (enemy1IsAlive == false && villanoIsAlive == false) {
        cout << "Has Ganado el combate\n";
    }
}
bool checkHeroStatus() {
    if (heroHP <= 0) {
        cout << "El heroe ha sido derrotado\n ";
        return false;
    }
    else
    {
        return true;
    }
}
int main() {
    srand(time(NULL));
    gameStart();
    while ((enemy1IsAlive || villanoIsAlive) && heroIsAlive) {
        //SELECCIONAMOS AL ENEMIGO QUE QUEREMOS ATACAR
        enemyChoose();
        //SELECCIONAMOS EL ATAQUE QUE QUEREMOS HACERLE AL ENEMIGO
        atackChoose();
        //NOS ATACAN LOS ENEMIGOS Y COMPROBAMOS SI AUN LES QUEDA VIDA RESTANTE
        enemiesAttack();
        //COMPROBAMOS SI AL HEROE AUN LE QUEDA VIDA RESTANTE
        heroIsAlive = checkHeroStatus();
    }
}
