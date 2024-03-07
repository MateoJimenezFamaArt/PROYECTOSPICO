#include <string>

//Variables Globales
uint32_t TimeToExplode = 5;
char Clave = 'C1234';


void task1()
{
  enum class Task1States {
    INIT,
    CONFIG,
    TRY,
    EXPLODE,
    DISARM
  };
  static Task1States task1State = Task1States:: INIT;


  switch (task1State)
  {
    case Task1States::INIT: {
    Serial.begin(115200);
    TimeToExplode = 5;
      Serial.print("Bienvenido agente de Disedentes del tiempo, listo para armar la bomba de emision?\n");
      Serial.print("En este momento la bomba tiene 5 segundos de duracion, pulsa S para subir el tiempo o B para bajarlo\n");
      Serial.print("Cuando quiera armar la bomba presione la L de listo\n");
      task1State = Task1States:: CONFIG;
       break;
    }

    case Task1States::CONFIG:{

      uint32_t *TimeToExplodeP;
      TimeToExplodeP = &TimeToExplode;

      if (Serial.available() > 0){
        char UserInput = Serial.read();

        if (TimeToExplode == 40){
          
          Serial.print("La bomba ha llegado a su maximo de tiempo disponible detonara en \n");
          Serial.print(TimeToExplode);
          Serial.print(" Segundos\n");
          Serial.print("LA CONFIGURACION DE LA BOMBA ESTA LISTA, PASANDO A MODO DE INTENTAR CLAVES...\n");
          task1State = Task1States::TRY;
          break;
          }

        if (TimeToExplode == 1){
          
          Serial.print("La bomba ha llegado a su minimo de tiempo disponible detonara en \n");
          Serial.print(TimeToExplode);
          Serial.print(" Segundo\n");
          Serial.print("LA CONFIGURACION DE LA BOMBA ESTA LISTA, PASANDO A MODO DE INTENTAR CLAVES...\n");
          task1State = Task1States::TRY; 
          break;
          }

        switch (UserInput){
          case 's':
          Serial.print("EL TIEMPO DE LA BOMBA HA SUBIDO, AHORA DETONARA EN...\n");
          *TimeToExplodeP = *TimeToExplodeP + 1;
          Serial.print(TimeToExplode);
          Serial.print(" Segundos\n");
          break;

          case 'b':
          Serial.print("EL TIEMPO DE LA BOMBA HA DISMINUIDO, AHORA DETONARA EN...\n");
          *TimeToExplodeP = *TimeToExplodeP - 1;
          Serial.print(TimeToExplode);
          Serial.print(" Segundos\n");
          break;

          case 'l':
          Serial.print("LA CONFIGURACION DE LA BOMBA ESTA LISTA, PASANDO A MODO DE INTENTAR CLAVES...\n");
          Serial.print("La bomba ha sido armada, explotara en ");
          Serial.print(TimeToExplode);
          Serial.print(" segundos\n");
          Serial.print("Buena suerte...\n");
          task1State = Task1States::TRY;
          break;
        }
      }
      break;   
    }

    case Task1States :: TRY :
    {
      uint32_t referenceTimeBombCounter = millis(); 
      
      while(TimeToExplode > 0)
      {
       if ((millis() - referenceTimeBombCounter) >= 1000) 
       {
          referenceTimeBombCounter = millis();
          TimeToExplode--;
          Serial.print("Tiempo antes de explotar: ");
          Serial.print(TimeToExplode);
          Serial.println(" segundos");
       } 

       if (Serial.available() > 0)
       {
        char UserCode = Serial.read();
        if (UserCode == Clave)
        {
          Serial.print("Clave correcta ingresada desarmando bomba...\n");
          delay(3000);
          task1State = Task1States::DISARM;
          break;
        }
       }

       if (TimeToExplode == 0)
       {
          task1State = Task1States::EXPLODE;
          break; 
       }
      }
        break;
    }

    case Task1States :: EXPLODE :
    {
      Serial.print("RADIACION NUCLEAR ACTIVA!!!\n");
      static uint32_t previousTime = 0;
      static bool ledState = true;
      uint32_t currentTime = millis();
      if( (currentTime - previousTime) > 100){
        previousTime = currentTime;
         ledState = !ledState;
          digitalWrite(LED_BUILTIN, ledState);}

         static uint32_t explosionStartTime = millis();
         if ((currentTime - explosionStartTime) > 3000)
          {
          ledState = false; 
          Serial.print("El dios del tiempo chronos ha aparecido, el mundo se ha destruido\n");
          Serial.print("Sin embargo el te ha otorgado su bendicion y te permite volverlo a intentar\n");
          Serial.print("No falles ahora campeon de chronos,\n ya sabes que si la sequencia quieres encontrar las palabras deberas recordar\n");
          Serial.println("Del Cielo un gran Cometa Cae Con fuerza");
          Serial.println("UNA vez choco con nuestro mundo");
          Serial.println("DOS veces acabo con la vida");
          Serial.println("TRES veces extinguio a la humanidad");
          Serial.println("CUATRO veces lo hizo para acabar con toda la vida...\n");
          delay(1000);
          task1State = Task1States :: INIT;
          }
          break;
    }

    case Task1States :: DISARM :{
      Serial.print("Enhorabuena,salvaste al mundo!!!\n");
      delay(2000);
      task1State = Task1States::INIT;
      break;
    }
  } 
}

void setup(){
  delay(3000);
  task1();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  task1();
}
