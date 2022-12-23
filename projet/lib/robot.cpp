#include "robot.h"

/**
 * @brief Fonction pour lancer l'exécution du parcours
 * 
 */
void Robot::start() {
    while (!parcoursFini()) {
      choisirEtape();
      executerEtape();
    }
}

/**
 * @brief Module3: Suivi de ligne.
 * 
 * Utilisation du _capteur de ligne "Maker Line de Cytron".
 * 
 * Plus d'informations dans la fonction CapteurLigne::choisirMouvement().
 * 
 * Le code ci-dessous a été réfléchi et écrit par les membres de l'équipe 1617 du cours INF1900:
 * @authors Evan BLANC, Ahmed ZGHAL, Ali MOUCHAHID, Ryan LAHBABI.
 */
void Robot::executerMouvement() {
    switch (_materiel.getCapteurLigne().choisirMouvement()) {
            case (Mouvement::ARRET):
                if (_etape == Etape::A_VERS_B) {
                    _finEtape = true;
                     arret();
                }      
                else if (_etape == Etape::B_VERS_S && _autorise) {
                    _finEtape = true;
                }
            break;

            case Mouvement::TOURNER_GAUCHE:
                tournerGauche();
            break;

            case Mouvement::TOURNER_DROITE:
                tournerDroite();
            break;

            case Mouvement::AVANCER:
                avancer();
            break;

            case Mouvement::CHOIX:

                if (_etape == Etape::B_VERS_S && _autorise) 
                    choisirChemin();

            break;

            case Mouvement::ANCIEN:
                executerAncienMouvement();
            break;

            default:
                avancer(Pwm::DEFAULT);
            break;   
        }
}

/**
 * @brief Execute le dernier mouvement connu
 * 
 */
void Robot::executerAncienMouvement() {
    if (_ancienMouvement == 0) {
        Moteur::avancer(Pwm::AVANCER);
        _delay_ms(200);
    } else if (_ancienMouvement == 1) {
        Moteur::tourner(Pwm::AVANCER_TOURNER, Pwm::TOURNER);
        _delay_ms(200);
    } else if (_ancienMouvement == 2) {
        Moteur::tourner(Pwm::TOURNER, Pwm::AVANCER_TOURNER);
        _delay_ms(200);
    }
    Moteur::arret();
}

/**	
 * @brief Fonction qui permet de s'assurer que l'on est bien sur une base.
 * 
 * On avance légèrement avant de s'arreter à nouveau, si les 5 _capteurs sont toujours allumés,	
 * celà signifie que nous somme bel et bien sur une base (checkpoint).	
 * 
 * @return true si le robot est vraiment sur une base
 * @return false si c'etait une détection accidentelle
 * 
 * Le code ci-dessous a été réfléchi et écrit par les membres de l'équipe 1617 du cours INF1900:
 * @authors Evan BLANC, Ahmed ZGHAL, Ali MOUCHAHID, Ryan LAHBABI.
 */
bool Robot::estSurUneBase() {
        avancer(Pwm::AVANCER_BASE);
        _delay_ms(300);
        Moteur::arret();
        _delay_ms(500);
    return (_materiel.getCapteurLigne().choisirMouvement() == Mouvement::ARRET);
}

/**
 * @brief Fonction qui permet au robot de choisir un chemin en fonction de sa mémoire.
 * 
 */
void Robot::choisirChemin() {
    if (_nbChoix == 0) {
        if (_poteaux[2] == POTEAU_LOIN) {
            Moteur::tourner(Pwm::TOURNER, Pwm::AVANCER_TOURNER_CHOIX);
            _ancienMouvement = 2;
        }
        else if (_poteaux[2] == POTEAU_PROCHE) {
            Moteur::tourner(Pwm::AVANCER_TOURNER_CHOIX, Pwm::TOURNER);
            _ancienMouvement = 1;
        }
        _nbChoix++;
    }
    else {
        if (_poteaux[0] == POTEAU_LOIN) {
            Moteur::tourner(Pwm::TOURNER, Pwm::AVANCER_TOURNER_CHOIX);
            _ancienMouvement = 2;
        }
        else if (_poteaux[0] == POTEAU_PROCHE) {
            Moteur::tourner(Pwm::AVANCER_TOURNER_CHOIX, Pwm::TOURNER);
            _ancienMouvement = 1;
        }
    }
    _delay_ms(300);
}

/**
*  @brief Module2: Choix de l'étape.
*  
* Nous avons choisi d'utiliser une machine à 3 états décrits dans l'enum class Etape.
* La sortie est la DEL de la carte et les sorties sont décrites dans le tableau ci-dessous.
*
* L'interruption INTO_vect est utilisée avec le bouton externe en front montant branché sur
* les pin D3, D4 sur la carte et PD2, PD3 dans le code. Ce dernier permet de changer d'etat.
*
* Le bouton de la carte déporté sur les pin A1, A2 sur la carte et PA0, PA1 dans le code
* est lu par scrutation afin de valider le choix du parcours.
*
*+────────────────+──────────────────────────────────+──────────────+────────────────────+
*|   ETAT:PARCOUS A,PARCOUS B,PARCOUS S                                                  |
*+────────────────+──────────────────────────────────+──────────────+────────────────────+
*| Present State  | Constraints                      | NextState    | Output             |
*+────────────────+──────────────────────────────────+──────────────+────────────────────+
*| PARCOUS A      | Button pressed                   | ROUGE        | VERT               |
*| PARCOUS B      | Button pressed                   | AMBRER       | ROUGE              |
*| PARCOUS S      | Button pressed                   | VERTT        | AMBRER             |
*+────────────────+──────────────────────────────────+──────────────+────────────────────+
* Le code ci-dessous a été réfléchi et écrit par les membres de l'équipe 1617 du cours INF1900:
* @authors Evan BLANC, Ahmed ZGHAL, Ali MOUCHAHID, Ryan LAHBABI.
*/
volatile bool boutonRelacher = false;

ISR(INT0_vect)
{
   _delay_ms(30);
    boutonRelacher = true;
}

void Robot::choisirEtape() {
    Del::initialiser();
    Bouton::initialiser();
    BoutonInterruption::initialiser( INT0, ModeInterruption::FallingEdgeInterrupt);
    
    bool confirmation = false;
    while (!confirmation) {
        switch (_etape) {
            case Etape::A_VERS_B:
                boutonRelacher = false;
                Del::allumerCouleurLumiere(Couleur::VERTE);
                if(Bouton::appuiBouton()) 
                    confirmation = !confirmation;
                
                if(boutonRelacher) {
                    Del::initialiser();
                    _etape = Etape::B_VERS_S;
                }
            break;

            case Etape::B_VERS_S:
                boutonRelacher = false;
                Del::allumerCouleurLumiere(Couleur::ROUGE);
                if(Bouton::appuiBouton())
                    confirmation = !confirmation;
                
                if(boutonRelacher) {
                    Del::initialiser();
                    _etape = Etape::S_VERS_FIN;
                }
            break;

            case Etape::S_VERS_FIN:
                boutonRelacher = false;
                Del::ambrer();
                if(Bouton::appuiBouton())
                    confirmation = !confirmation;
                
                if(boutonRelacher) {
                    Del::initialiser();
                    _etape = Etape::A_VERS_B;
                }
            break;

            default:
            break;
        }
    }
    Del::clignoter(2,4,Couleur::VERTE);
    Del::allumerCouleurLumiere(Couleur::ETEINTE);
}

/**
 * @brief Fonction qui permet d'executer les bonnes actions en fonction de l'étape à laquelle nous sommes rendu.
 * 
 * @param Etape etape 
 */
void Robot::executerEtape() {

    switch (_etape) {
        case Etape::A_VERS_B:
            executerEtape_A_B();
        break;

        case Etape::B_VERS_S:
            executerEtape_B_S();
        break;

        case Etape::S_VERS_FIN:
            executerEtape_S_FIN();
        break;

        default:
        break;
    }
}

/**
 * @brief Etape_A->B
 * 
 * Ce code est le résultat de la fusion des modules 1 et 3 : Détection de poteaux et Suivi de ligne
 * 
 * Le robot est au point de départ (A) puis s'élance en direction de (B) en détectant les poteaux.
 * 
 * Il les enregistrent en mémoire (localement grace a poteaux[] puis en mémoire externe) afin de
 * s'en servir dans l'étape de B vers S.
 *
 * 
 * Le code ci-dessous a été réfléchi et écrit par les membres de l'équipe 1617 du cours INF1900:
 * @authors Evan BLANC, Ahmed ZGHAL, Ali MOUCHAHID, Ryan LAHBABI.
 */
void Robot::executerEtape_A_B() {
    _finEtape = false;
    _etape = Etape::A_VERS_B;
    avancer();
    _delay_ms(1000);
    while (!etapeFinie()) {
        lirePoteau();
        executerMouvement();
    }
    ecrireMemoire();
    Moteur::arret();
}

/**
 * @brief Fonction qui réalise la suite d'actions de l'étape B vers S.
 * 
 */
void Robot::executerEtape_B_S() {
    _autorise = false;
    Del::allumerCouleurLumiere(Couleur::ROUGE);
    _etape = Etape::B_VERS_S;
    lireMemoire();
    avancer();
    _delay_ms(1000);

    executerMouvement(9000);
    //true
    _autorise = true;
    Del::allumerCouleurLumiere(Couleur::VERTE);
    executerMouvement(6000);
    //false
    _autorise = false;
    Del::allumerCouleurLumiere(Couleur::ROUGE);
    executerMouvement(6000);

    //true
    _autorise = true;
    Del::allumerCouleurLumiere(Couleur::VERTE);
    executerMouvement(2000);
    //false
    _autorise = false;
    Del::allumerCouleurLumiere(Couleur::ROUGE);
    executerMouvement(20000);
    //true
    _autorise = true;
    Del::allumerCouleurLumiere(Couleur::VERTE);
    _finEtape = false;
    while (!etapeFinie()) {
        executerMouvement();
    }
    executerEtape_S_FIN();
}

/**
 * @brief Fonction qui réalise la suite d'actions de l'étape S vers FIN.
 * 
 */
void Robot::executerEtape_S_FIN() {
    _finEtape = false;

    _etape = Etape::S_VERS_FIN;
    avancer();
    _delay_ms(500);
    executerMouvement(DUREE_SUIVI_LIGNE);
    tournerDroite();
    _delay_ms(400);

    zigzag(NB_ZIGZAG);

    executerMouvement(DUREE_SUIVI_LIGNE);

    while ((PINC & 0b10111100) != 0) executerMouvement();

    park();

    _finParcours = true;
}

   



/**
 * @brief Fonction d'écriture en mémoire externe.
 * 
 * @param _poteaux[] uint8_t
 * 
 * Différentes valeurs possibles dans le tableau:
 *  -0x00: pas de poteau détecté.
 *  -0x0F: le poteau détecté est proche.
 *  -0xF0: le poteau détecté est loin.
 * 
 * Il y a deux cas possible:
 *  -3 _poteaux ont été détectés, le tableau est donc rempli de valeurs différentes de 0x00.
 *      _poteaux[0] est le poteau 1, _poteaux[1] est le poteau 2 et _poteaux[2] est le poteau 3.
 * 
 *  -2 _poteaux ont été détectés, le tableau à la position [2] vaut 0x00.
 *      _poteaux[0] est le poteau 1 et _poteaux[1] est le poteau 3.
 *  
 * De cette facon, nous écrivons toujours 3 octets en mémoire, dans l'odre :
 *      -Poteau1
 *      -Poteau2
 *      -Poteau3
 * 
 * Nous permettons ainsi une écriture et lecture uniforme.
 * 
 * 
 * Le code ci-dessous a été réfléchi et écrit par les membres de l'équipe 1617 du cours INF1900:
 * @authors Evan BLANC, Ahmed ZGHAL, Ali MOUCHAHID, Ryan LAHBABI.
 */
void Robot::ecrireMemoire() {
    if (_poteaux[2] == 0x00) {
      _materiel.getMemoire().ecriture(0x0000, _poteaux[0]);
      _delay_ms(5);
      _materiel.getMemoire().ecriture(0x0001, _poteaux[2]);
      _delay_ms(5);
      _materiel.getMemoire().ecriture(0x0002, _poteaux[1]);
      _delay_ms(5);
   } else {
      _materiel.getMemoire().ecriture(0x0000, _poteaux[0]);
      _delay_ms(5);
      _materiel.getMemoire().ecriture(0x0001, _poteaux[1]);
      _delay_ms(5);
      _materiel.getMemoire().ecriture(0x0002, _poteaux[2]);
      _delay_ms(5);
   }
}

/**
 * @brief Fonction de lecture en mémoire externe.
 * 
 * @param _poteaux[] uint8_t
 * 
 * Différentes valeurs possibles dans le tableau:
 *  -0x00: pas de poteau détecté.
 *  -0x0F: le poteau détecté est proche.
 *  -0xF0: le poteau détecté est loin.
 * 
 * Il y a deux cas possible:
 *  -3 _poteaux ont été détectés, le tableau est donc rempli de valeurs différentes de 0x00.
 *      _poteaux[0] est le poteau 1, _poteaux[1] est le poteau 2 et _poteaux[2] est le poteau 3.
 * 
 *  -2 _poteaux ont été détectés, le tableau à la position [2] vaut 0x00.
 *      _poteaux[0] est le poteau 1 et _poteaux[1] est le poteau 3.
 *  
 * De cette facon, nous lisons toujours 3 octets en mémoire, dans l'odre :
 *      -Poteau1
 *      -Poteau2
 *      -Poteau3
 * 
 * Nous permettons ainsi une écriture et lecture uniforme.
 * 
 * 
 * Le code ci-dessous a été réfléchi et écrit par les membres de l'équipe 1617 du cours INF1900:
 * @authors Evan BLANC, Ahmed ZGHAL, Ali MOUCHAHID, Ryan LAHBABI.
 */
void Robot::lireMemoire() {
    _materiel.getMemoire().lecture(0x0000, &_poteaux[0]);
    _materiel.getMemoire().lecture(0x0001, &_poteaux[1]);
    _materiel.getMemoire().lecture(0x0002, &_poteaux[2]);
}

/**
 * @brief Module1: Détection des _poteaux.
 * 
 * @param _poteaux[] uint8_t
 * 
 * Notre _capteur infrarouge "Sharp GP2Y0A21YK0F" est branché sur la pin A7 sur la carte, PA6
 * dans le code.
 * 
 * Nous utilisons une formule mathématique afin de transformer le voltage en disctance en cm.
 * Celle-ci n'est pas parfaite mais nous suffit pour selectionner nos intervalles de détection.
 * 
 * Nous considérons comme loin les valeurs de Robot::getDistance appartiennent à ]70 ; 80[.
 * Nous considérons comme proche les valeurs de Robot::getDistance appartiennent à ]25 ; 35[.
 * 
 * Ces intervalles sont volontèrement le plus petit possible afin d'éviter les valeurs aléatoires
 * que nous lisons de temps en temps à cause de la fiabilité du matériel.
 * 
 * En cas de détection:
 *  -Cas ou le poteau est proche:
 *      -Le robot s'arrette.
 *      -Il emmet un son grave pendant 1 seconde.
 *      -Il se remet à avancer pendant 1 seconde afin de ne plus re-détecter le même poteau.
 * 
 *  -Cas ou le poteau est proche:
 *      -Le robot s'arrette.
 *      -Il emmet un son aigu pendant 1 seconde.
 *      -Il se remet à avancer pendant 1 seconde afin de ne plus re-détecter le même poteau.
 * 
 * 
 * Le code ci-dessous a été réfléchi et écrit par les membres de l'équipe 1617 du cours INF1900:
 * @authors Evan BLANC, Ahmed ZGHAL, Ali MOUCHAHID, Ryan LAHBABI.
 */
void Robot::lirePoteau() {
    Usart::initialiser();
    uint16_t distance = 0;
    
    distance = getDistance();

    Usart::transmettreEntier16bits(distance);
    if (distance > DISTANCE_PROCHE_MIN && distance < DISTANCE_PROCHE_MAX) {
        executerMouvement(50);
        distance = getDistance();
        if (distance > DISTANCE_PROCHE_MIN && distance < DISTANCE_PROCHE_MAX) {
            executerMouvement(50);
            distance = getDistance();
        
            if (distance > DISTANCE_PROCHE_MIN && distance < DISTANCE_PROCHE_MAX) {
                Moteur::arret();
                Sonorite::jouerNote(Note::GRAVE);
                _delay_ms(1000);
                Sonorite::arreter();
                _poteaux[_indexPoteau++] = 0xF0;
                executerMouvement(3000);
            }
        }    
    } 
    else if (distance > DISTANCE_LOIN_MIN && distance < DISTANCE_LOIN_MAX) {
        executerMouvement(50);
        distance = getDistance();
        if (distance > DISTANCE_LOIN_MIN && distance < DISTANCE_LOIN_MAX) {
            executerMouvement(50);
            distance = getDistance();
            if (distance > DISTANCE_LOIN_MIN && distance < DISTANCE_LOIN_MAX) {
                Moteur::arret();
                Sonorite::jouerNote(Note::AIGU);
                _delay_ms(1000);
                Sonorite::arreter();
                _poteaux[_indexPoteau++] = 0x0F;
                executerMouvement(3000);
            }
        }
    }
    else {
        Sonorite::arreter();
    }

}

/**
 * @brief Permet d'obtenir la Distance entre le robot et le poteau.
 * 
 * @return uint8_t la Distance.
 * 
 * 
 * Le code ci-dessous a été réfléchi et écrit par les membres de l'équipe 1617 du cours INF1900:
 * @authors Evan BLANC, Ahmed ZGHAL, Ali MOUCHAHID, Ryan LAHBABI.
 */
uint8_t Robot::getDistance() {
    can capteur;
    float volt = (capteur.lecture(PA6) >> 2);
    return volt;
}

/**
 * @brief getter de l'attribut _finParcours.
 * 
 * @return true si le parcours est fini. 
 */
bool Robot::parcoursFini() { return _finParcours; }

/**
 * @brief getter de l'attribut _finEtape.
 * 
 * @return true si l'etape est finie. 
 */
bool Robot::etapeFinie() { return _finEtape; }

/**
 * @brief Fonction qui fait tourner le robot à gauche.
 * 
 */
void Robot::tournerGauche() {
    switch (_etape) {
        case Etape::ZIGZAG:
            Moteur::tourner(Pwm::TOURNER_ZIGZAG, Pwm::AVANCER_TOURNER_ZIGZAG_DROITE);
        break;

        case Etape::A_VERS_B:
           Moteur::tourner(Pwm::TOURNER, Pwm::AVANCER_TOURNER_AB);
        break;

        default:
            Moteur::tourner(Pwm::TOURNER, Pwm::AVANCER_TOURNER);
        break;
    }
  
    _ancienMouvement = 2;
}

/**
 * @brief Fonction qui fait tourner le robot à droite.
 * 
 */
void Robot::tournerDroite() {
    switch (_etape) {
        case Etape::ZIGZAG:
            Moteur::tourner(Pwm::AVANCER_TOURNER_ZIGZAG_GAUCHE, Pwm::TOURNER_ZIGZAG);
        break;
        
        case Etape::A_VERS_B:
           Moteur::tourner(Pwm::AVANCER_TOURNER_AB, Pwm::TOURNER);
        break;

        default:
            Moteur::tourner(Pwm::AVANCER_TOURNER, Pwm::TOURNER);
        break;
    }
    _ancienMouvement = 1;
}

/**
 * @brief Fonction qui fait avancer le robot dépendament de l'étape.
 * 
 */
void Robot::avancer() {
    switch (_etape) {
        case Etape::A_VERS_B:
           Moteur::avancer(Pwm::AVANCER_AB);
        break;

        case Etape::B_VERS_S:
           Moteur::avancer(Pwm::AVANCER_BS);
        break;

        case Etape::S_VERS_FIN:
           Moteur::avancer(Pwm::AVANCER_ZIGZAG);
        break;

        default:
        break;
    }
}

/**
 * @brief Fonction qui fait avancer le robot selon un Pwm.
 * 
 */
void Robot::avancer(Pwm pwm) {
    Moteur::avancer(pwm);
}

/**
 * @brief Fonction qui fait avancer le robot pendant une duree en ms.
 * 
 */
void Robot::executerMouvement(uint16_t duree_ms) {
    for(uint16_t i = 0 ; i < duree_ms ; i++) {
        _delay_ms(1);
        executerMouvement(); 
    }
}

/**
 * @brief Fonction qui arrête le robot si il est dans l'etape A_VERS_B.
 * 
 */
void Robot::arret() {
        Moteur::arret();
        _delay_ms(500);
}

void Robot::zigzag(uint8_t nbVirageDroite) {
    uint8_t i = 0;
    _etape = Etape::ZIGZAG;
    while (true) {    
      while((PINC & U4) != (U4) && (PINC & U5) != (U5) )  tournerDroite();
      if (++i == nbVirageDroite) break;
      while((PINC & U1) != (U1) && (PINC & U2) != (U2) )  tournerGauche();
    }
    _etape = Etape::S_VERS_FIN;
}

/**
 * @brief park le robot
 * 
 */
void Robot::park()
{
    Moteur::arret();
    _delay_ms(2000);
    Moteur::reculer(Pwm::RECULER_PARK);
    _delay_ms(2000);
    Moteur::tourner(Pwm::TOURNER_PARK, Pwm::AVANCER);
    _delay_ms(1200);

    Moteur::arret();
    _delay_ms(800);
    Moteur::avancer(Pwm::AVANCER_PARK);
    _delay_ms(800);
    
    Moteur::arret();
    Sonorite::jouerNote(Note::GRAVE);
    _delay_ms(3000);
    Sonorite::arreter();
}