
#define TENSION_SENSOR_PIN 1
#define TENSION_SENSOR_PRECISION 0.05

#define RELAY_SHUTTER_PIN 2

/**
 * Temps de course du volet.
 */
unsigned long shutterTravelTime = 0;

/**
 * Valeur courante de la course du volet roulant.
 * 0 (%) = ouvert ; 100 (%) = fermé.
 */
unsigned short int shutterTravelPercentage = 0;

/**
 * Lit la tension d'alimentatin du volet.
 * Retourne la tension en volt selon la précision du capteur.
 * FONCTION QUI SIMULE POUR LE MOMENT : TODO : implémenter la vraie fonction.
 */
float readShutterTension(float tension) {
  return tension;
}

/**
 * Initialise le temps de course du volet (en ms).
 */
void initShutterTravelTime() {
  float tension = 12.00;
  unsigned long t1;
  t1 = millis();
  while((tension = readShutterTension(tension - 0.01)) > (0+TENSION_SENSOR_PRECISION)) delay(5); // bloque tant que le volet n'est pas arrivé en fin de course
  return (millis() - t1);
}

/**
 * Ouvre ou ferme le volet selon le pourcentage en paramètre.
 * Définit si c'est une ouverture ou une fermeture en fonction de la valeur courante @shutterTravelPercentage.
 * Renvoi 1 si ok, 2 si la valeur donnée n'est pas correcte, 3 si la valeur courante est égale à la valeur donnée.
 */
int setTravelPercentage(unsigned short int travelPercentage) {
  if(travelPercentage < 0 || travelPercentage > 100) return 2;
  if(travelPercentage == shutterTravelPercentage) return 3;
  boolean isOpening = (travelPercentage < shutterTravelPercentage);

  // TODO allumer l'un ou l'autre relais selon si c'est l'ouverture ou fermeture pendant x temps où x correspond au temps calculé selon le pourcentage donnée et en fonction du temps de course total.
}

void setup() {
  Serial.begin(115200);
  shutterTravelTime = initShutterTravelTime();
  Serial.println("Temps de course en ms : ");
  Serial.print(shutterTravelTime);
}

/**
 * Au départ effectuer un cycle complet du volet (totalement ouvert jusqu'à totalement fermé)
 * afin de calculer le temps de course du volet.
 */
void loop() {
  
  
}
