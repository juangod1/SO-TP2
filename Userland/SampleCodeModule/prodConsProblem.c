#define SEM_MUTEX_KEY 40
#define SEM_OVERFLOW_KEY 41
#define SEM_UNDERFLOW_KEY 42

int sharedInt=0;

int prodConsDemo(int value)
{
  semStart(SEM_MUTEX_KEY,1);
  semStart(SEM_OVERFLOW_KEY,value);
  semStart(SEM_UNDERFLOW_KEY,0);
  int exitFlag=0; char input=0;
  sysPrintString("1. Producer\n 2. Consumer\n 3. Exit\n",255,255,0);
  while(!exitFlag)
  {
    sysGetChar(&input)
    if(input!=0)
    {
      switch(input)
      {
        case '1':
          sysPrintString("Generated a Producer!\n",255,255,0);
          sysExecute(producer, "Producer");
        break;
        case '2':
          sysPrintString("Generated a Consumer!\n",255,255,0);
          sysExecute(consumer, "Consumer");
        break;
        case '3':
          exitFlag=1;
        break;
        case default:
          sysPrintString("Wrong input!\n",255,255,0);
        break;
      }
    }
  }
  semStop(SEM_MUTEX_KEY);
  semStop(SEM_OVERFLOW_KEY);
  semStop(SEM_UNDERFLOW_KEY);
}

void producer()
{
  semWait(SEM_OVERFLOW_KEY);
  semWait(SEM_MUTEX_KEY);
  sharedInt++;
  sysPrintInt(sharedInt, 255,255,0);
  semSignal(SEM_UNDERFLOW_KEY);
  semSignal(SEM_MUTEX_KEY);
}

void consumer()
{
  semWait(SEM_UNDERFLOW_KEY);
  semWait(SEM_MUTEX_KEY);
  sysPrintInt(sharedInt, 255,255,0);
  sharedInt--;
  semSignal(SEM_OVERFLOW_KEY);
  semSignal(SEM_MUTEX_KEY);
}
