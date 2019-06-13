#include <ConversionMemoire.h>

//#define DEBUG // à mettre en commentaire au besoin
#ifdef DEBUG
#define DEBUG_INIT debugInitialisation() //Permet de débuter le déboguage
#define DEBUG_VAR(x) debugValeur(x, __LINE__) // ou par RS-232
#define DEBUG_VAR16(x) debugValeur16(x, __LINE__) // ou par RS-232
#else
#define DEBUG_VAR(x) do {} while (0) // code mort
#define DEBUG_INIT do {} while (0)
#endif

// Initialise le UART et definit debug
void debugInitialisation(); 
// Renvoit au UART la valeur et la ligne dune variable
void debugValeur(uint8_t valeur, uint8_t ligne); 
void debugValeur16(uint16_t valeur, uint8_t ligne); 
//Renvoit la ligne d'une erreur
void erreur();