#include <string>

void task1()
{
  enum class Task1States {
    INIT,
    CONFIG,
    TRY,
    EXPLODE
  };
  static Task1States task1State = Task1States:: INIT;
  uint32_t TimeToExplode = 5;

  switch (task1State)
  {
    case Task1States::INIT: {
    Serial.begin(115200);
    task1State = Task1States:: CONFIG;
    break;
    }

    case Task1States::CONFIG:{
      
      //Serial.print("Bienvenido agente de Disedentes del tiempo, listo para armar la bomba de emision?\n");
      //Serial.print("En este momento la bomba tiene 5 segundos de duracion, pulsa S para subir el tiempo o B para bajarlo");
      //Serial.print("Cuando quiera armar la bomba presione la L de listo\n");

      if (Serial.available() > 0){
        char UserInput = Serial.read();

        switch (UserInput){
          case 's':
          Serial.print("EL TIEMPO DE LA BOMBA HA SUBIDO, AHORA DETONARA EN...\n");
          TimeToExplode = TimeToExplode + 1;
          Serial.print(TimeToExplode);
          Serial.print(" Segundos\n");
          break;

          case 'b':
          Serial.print("EL TIEMPO DE LA BOMBA HA DISMINUIDO, AHORA DETONARA EN...\n");
          TimeToExplode = TimeToExplode - 1;
          Serial.print(TimeToExplode);
          Serial.print(" Segundos\n");
          break;

          case 'l':
          Serial.print("LA CONFIGURACION DE LA BOMBA ESTA LISTA, PASANDO A MODO DE INTENTAR CLAVES...\n");
          task1State = Task1States::TRY;

          default:
          Serial.print("Porfavor ingrese un valor aceptado (S = subir tiempo / B = bajar tiempo / L = Listo la configuracion)\n");
          break;
        }
      }



               
    }




    
  } 
  
}

void setup(){
  task1();
}

void loop(){
  task1();
}
