static void changeVar(uint32_t *pdata, uint32_t *pdata2)
{
  *pdata = 10;
  *pdata2 = 15;
}

static void printVar(uint32_t value1, uint32_t value2)
{
  Serial.print("Var1 content: ");
  Serial.print(value1);
  Serial.print("\n");
  Serial.print("Var2 content: ");
  Serial.print(value2);
  Serial.print("\n");
}

void task1()
{
  enum class Task1State{
    INIT,
    WAIT_ENTRY
  };
  static Task1State task1State = Task1State::INIT;

  switch (task1State)
  {
    case Task1State:: INIT:
    {
      Serial.begin(115200);
      task1State = Task1State::WAIT_ENTRY;
      break;
    }

    case Task1State::WAIT_ENTRY:
    {
      if (Serial.available() > 0)
      {
        Serial.read();
        uint32_t var1 = 0;
        uint32_t var2 = 0;
        uint32_t *pvar = &var1;
        uint32_t *pvar2 = &var2;
        printVar(*pvar,*pvar2);
        changeVar(pvar,pvar2);
        printVar(var1,var2);
      }
      break;
    }
    
    default:
    {
      break;
    }
  }
}

void setup()
{
  task1();
}

void loop()
{
  task1();
}
