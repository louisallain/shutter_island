
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
unsigned long initShutterTravelTime() {
  float tension = 12.00;
  unsigned long t1;
  t1 = millis();
  while((tension = readShutterTension(tension - 0.01)) > (0+TENSION_SENSOR_PRECISION)) delay(5); // bloque tant que le volet n'est pas arrivé en fin de course
  return (millis() - t1);
}

/**
 * Ouvre ou ferme le volet selon le pourcentage en paramètre.
 * Définit si c'est une ouverture ou une fermeture.
 */
unsigned short int travelShutterFor(unsigned short int travelPercentage, unsigned long shutterTravelTimeTotal, unsigned short int currentTravelPercentage) {

  if(travelPercentage == currentTravelPercentage) return travelPercentage;
  short int deltaPercentage = currentTravelPercentage - travelPercentage;
  unsigned long travelTime = computeTravelTime(shutterTravelTimeTotal, abs(deltaPercentage));
  boolean isOpenningTravel = travelPercentage < currentTravelPercentage;
  Serial.println("isOpenning : ");
  Serial.println(isOpenningTravel);
  Serial.println("durée : ");
  Serial.println(travelTime);

  // TODO allumer l'un ou l'autre relais selon si c'est l'ouverture ou fermeture pendant x temps où x correspond au temps calculé selon le pourcentage donnée et en fonction du temps de course total.
  // Pour l'instant simulation en allumant une led
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(travelTime);         
  digitalWrite(LED_BUILTIN, LOW);

  return travelPercentage;
}

/**
 * Calcul le temps de course selon le pourcentage de course souhaité.
 */
unsigned long computeTravelTime(unsigned long shutterTravelTimeTotal, unsigned short int percentage) {
  return (float)percentage / 100 * shutterTravelTimeTotal;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  
  shutterTravelTime = initShutterTravelTime();
  Serial.println("Temps de course en ms : ");
  Serial.println(shutterTravelTime);
}

/**
 * Au départ effectuer un cycle complet du volet (totalement ouvert jusqu'à totalement fermé)
 * afin de calculer le temps de course du volet.
 */
void loop() {

  delay(1000);
  // Important de mettre à jour le pourcentage d'ouverture courant pour vérifier si c'est une ouverture ou une fermeture ou si c'est déjà la valeur courante.
  shutterTravelPercentage = travelShutterFor(100, shutterTravelTime, shutterTravelPercentage);
  delay(1000);
  shutterTravelPercentage = travelShutterFor(50, shutterTravelTime, shutterTravelPercentage);
  delay(1000);
  shutterTravelPercentage = travelShutterFor(100, shutterTravelTime, shutterTravelPercentage);
  delay(1000);
  shutterTravelPercentage = travelShutterFor(0, shutterTravelTime, shutterTravelPercentage);
  delay(1000);
  shutterTravelPercentage = travelShutterFor(33, shutterTravelTime, shutterTravelPercentage);
  delay(1000);
}
