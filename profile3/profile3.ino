
#include <EEPROM.h>

#define DEBUG
#define CLEARMODE   0
#define NORMALMODE  1
#define EXMODE      2

#define BUILDMODE EXMODE

typedef struct nutrition{
     uint8_t p;
     uint8_t n;
     uint8_t fe;

  };

typedef struct dailyPlanSegment{  // required envirment condition
    uint8_t temp;
    uint8_t humidity;
    uint8_t oxygen;
    uint8_t light;
    uint8_t water;  // milileters
    nutrition plannNtrition;
 };

typedef struct fullDailyPlan{  // required envirment condition
    uint8_t period;
    dailyPlanSegment s00A06A;
    dailyPlanSegment s06A10A;
    dailyPlanSegment s10A02P;
    dailyPlanSegment s02P06P;
    dailyPlanSegment s06P12A;
    
 };


  // main data for running  
  uint8_t      numOfseason;
  fullDailyPlan  *runningProfile; 

  
void cleareeprom(int clearbyte){
  for(int i=0; i<clearbyte; i++){
        //Serial.println(EEPROM.read(i));
          EEPROM.write(i,0);
        }
     EEPROM.commit(); 
  }

void programmeCountIn(){
  byte val = EEPROM.read(0);
  val++;
  EEPROM.write(0, val);
  EEPROM.commit();
 
  }
// get number of season, plans as arry
void AddData(byte season, fullDailyPlan day1[]){
    
    // get last index
    long lastin = EEPROMReadlong(1);
    #ifdef DEBUG
    Serial.print("[DEBUG] final memory location = ");
    Serial.println(lastin);    
    #endif
    
    if(lastin<100){  
      lastin = 100;
      }
     
     // update hedder meta data
      byte pcount = EEPROM.read(0);
      pcount = (pcount*5)+10;  // 10, 15 20 start value
      
      EEPROM.write(pcount,season);
      EEPROMWritelong(pcount+1,lastin);
     

  for(byte i=0; i<season; i++)
      {
        EEPROM.put(lastin, day1[i]);
        lastin = lastin + (long)sizeof(fullDailyPlan);
      
      } 
       EEPROMWritelong(1,lastin);  // update new last memory location
       programmeCountIn();  // increse programme count and commit eeprom
  
  }


void readProfile(uint8_t profileNo)
    {
      if(profileNo<=EEPROM.read(0))
        {
       numOfseason = EEPROM.read((profileNo*5)+5);
         int startAddress = EEPROMReadlong((profileNo*5)+6);
         int currentAddress;

        runningProfile = new fullDailyPlan[numOfseason];

         for(int i =0; i<numOfseason; i++)
            {
              currentAddress = startAddress + i*sizeof(fullDailyPlan);
              EEPROM.get(currentAddress,runningProfile[i]);
              
              }

          }else
            {
              Serial.println("Invalid proile no");
         }
    }



void EEPROMWritelong(int address, long value)
      {
      //Decomposition from a long to 4 bytes by using bitshift.
      //One = Most significant -> Four = Least significant byte
      byte four = (value & 0xFF);
      byte three = ((value >> 8) & 0xFF);
      byte two = ((value >> 16) & 0xFF);
      byte one = ((value >> 24) & 0xFF);

      //Write the 4 bytes into the eeprom memory.
      EEPROM.write(address, four);
      EEPROM.write(address + 1, three);
      EEPROM.write(address + 2, two);
      EEPROM.write(address + 3, one);
      }

long EEPROMReadlong(long address)
      {
      //Read the 4 bytes from the eeprom memory.
      long four = EEPROM.read(address);
      long three = EEPROM.read(address + 1);
      long two = EEPROM.read(address + 2);
      long one = EEPROM.read(address + 3);

      //Return the recomposed long by using bitshift.
      return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
      }



void setup() {

    Serial.begin(115200);  
    Serial.println();
    EEPROM.begin(512);
    
    //nutrition nn ={3,4,5};  
    fullDailyPlan days[2] ={ 
                              { 11,
                                85,25,34,23,12,{2,3,2},
                                45,90,34,23,21,{11,3,18},
                                45,90,34,23,21,{11,3,18},
                                45,90,34,23,21,{11,3,18},
                                45,90,34,23,21,{11,3,76}
                                                                          
                              },

                              { 22,
                                49,20,34,23,12,{2,3,2},
                                45,90,34,23,21,{11,3,18},
                                45,90,34,23,21,{11,3,18},
                                45,90,34,23,21,{11,3,18},
                                45,90,34,23,21,{11,22,15}
                                                                          
                              }

                              
                              
                                               
                        
                        };
     

   // pass number of season and season data array to eeprom
     
#if(BUILDMODE==CLEARMODE)
      cleareeprom();
#elif(BUILDMODE==NORMALMODE) 
      AddData(2,days);      // pass number of season and data array
      Serial.println("Data writing mode");
#else
        Serial.println("EXmode");
#endif

      Serial.println("----------");
      readProfile(5);

      Serial.println(runningProfile[0].period);
    Serial.println(runningProfile[0].s00A06A.temp);
    Serial.println(runningProfile[0].s00A06A.humidity);

      Serial.println("----------");
               
      //Serial.println(EEPROM.read(30));
      //Serial.println(EEPROMReadlong(31));


      
      Serial.println("show eeprom data");  
    for(int i=0; i<100; i++){
    
        Serial.println(EEPROM.read(i));

      }

      
  }





void loop() {
  // put your main code here, to run repeatedly:

}
