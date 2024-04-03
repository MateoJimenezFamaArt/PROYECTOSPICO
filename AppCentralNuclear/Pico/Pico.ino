#include <string>


//Variables Globales
int TimeToExplode = 5;

//Codigo generico para limpiar el buffer del monitor serial
void CleanSerialBuffer() 
{
  while (Serial.available()>0)
  {
    char _ = Serial.read();  //Lee y descarta los datos hasta que el Serial.available este vacio
  }  
}

void task1(){

  enum class Task1States {
    INIT,
    STARTTIME,
    INTERVALS,
    COOLDOWN,
    DISARM,
    EXPLODE
  };

  static Task1States task1State = Task1States:: INIT;

  switch (task1State)
  {
    case Task1States:: INIT : {
        Serial.begin(115200);
        TimeToExplode = 60;
        Serial.print("Bienvenido empleado de la central nuclear super mega nuclear\n");
        Serial.print ("El dia de hoy haremos un ensayo de emergencia este dura normalmente 1 minuto sin embargo, \n pulsa S para subir el tiempo o B para bajar \n");
        Serial.print("Cuando estes listo preciona la L para iniciar tu prueba\n");
        task1State = Task1States::STARTTIME;
        break;
    }

    case Task1States::STARTTIME:{
        int *TimeToExplodeP;
        TimeToExplodeP = &TimeToExplode;

        if (Serial.available() > 0){
            int UserInput = Serial.read();

            if (TimeToExplode == 300){
              Serial.print("Esa pureba esta muy larga, demasiado sencillo MARICONA...\n");
              Serial.print("Tienes /n "); 
              Serial.print (TimeToExplode);
              Serial.print(" para completar tu prueba, buena suerte/n");
              Serial.print("Buena suerte Esclavo, digo empelado");
              task1State = Task1States:: INTERVALS;
              break;
            }

           if (TimeToExplode == 30){
              Serial.print("Esa pureba esta muy corta, demasiado dificl MACHO...\n");
               Serial.print("Tienes /n "); 
              Serial.print (TimeToExplode);
              Serial.print(" para completar tu prueba, buena suerte/n");
              Serial.print("Buena suerte Esclavo, digo empelado\n");
              task1State = Task1States:: INTERVALS;
              break;
            }

            switch (UserInput)
            { 
              //ASCII s
              case 115 :
              Serial.print("El tiempo de la prueba ha subido\n");
              *TimeToExplodeP = *TimeToExplodeP + 5;
              Serial.print("Tienes /n "); 
              Serial.print (TimeToExplode);
              Serial.print(" para completar tu prueba, buena suerte/n");
              break;

              //ASCII b
              case 98 :
              Serial.print("El tiempo de la prueba ha bajado\n");
              *TimeToExplodeP = *TimeToExplodeP - 5;
              Serial.print("Tienes /n "); 
              Serial.print (TimeToExplode);
              Serial.print(" para completar tu prueba, buena suerte/n");
              break;

              //ASCII l
              case 108 :
              Serial.print("La prueba comenzara prontamente, buena suerte\n");
              Serial.print("Tienes /n "); 
              Serial.print (TimeToExplode);
              Serial.print(" para completar tu prueba, buena suerte/n");
              task1State = Task1States::INTERVALS;
              break;
            }
          }
          break;
        }

      case Task1States :: INTERVALS :
      {
        Serial.print("Quiero un aumento");
        task1State = Task1States::INIT;



      }
    }




  }
























void setup() {
  task1();

}

void loop() {
  task1();
}
