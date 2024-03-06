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
      Serial.print("Bienvenido agente de Disedentes del tiempo, listo para armar la bomba de emision?\n");
      Serial.print("En este momento la bomba tiene 5 segundos de duracion, pulsa S para subir el tiempo o B para bajarlo");
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

    case Task1States :: TRY :{

      //TIMER
      for (int i = TimeToExplode; i > 0; --i) 
      {
      Serial.print("Tiempo restante: ");
      Serial.print(i);
      Serial.println(" Segundos");
      delay(1000);

      //Clave
        if (Serial.available() > 0) {
        char UserCode = Serial.read();

        if (UserCode == Clave){
          Serial.print("Nice\n");
          task1State = Task1States:: DISARM;
          break;
          }
        
        }

      //BOOM
      if(i == 1){
        task1State = Task1States:: EXPLODE;
        }
      }
        break;
  
    }

    case Task1States :: EXPLODE :{
      Serial.print("RADIACION NUCLEAR ACTIVA, SE TE VAN A CAER LOS WEBOS\n");
      static uint32_t previousTime = 0;
      static bool ledState = true;

      uint32_t currentTime = millis();

      if( (currentTime - previousTime) > 100){
        previousTime = currentTime;
         ledState = !ledState;
          digitalWrite(LED_BUILTIN, ledState);}
          

    }

    case Task1States :: DISARM :{
      Serial.print("Salvaste al mundo\n");
    }
  } 
}

void setup(){
  task1();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  task1();
}
