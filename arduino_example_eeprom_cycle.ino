#include <EEPROM.h>
#include <TimerOne.h>
                      // 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
uint32_t hidro[20]  = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
//uint32_t hidro0[20]  = {00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00};
//uint32_t hidro1[20]  = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
//uint32_t hidro2[20]  = {20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20};
//uint32_t hidro3[20]  = {30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30};
//uint32_t hidro4[20]  = {40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40};
//uint32_t hidro5[20]  = {50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50};
//uint32_t hidro6[20]  = {60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60};
uint32_t hidro7[20]  = {70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70};
//uint32_t hidro8[20]  = {140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140};
//uint32_t hidro9[20]  = {150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150};
//uint32_t hidro10[20] = {160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160};
//uint32_t hidro11[20] = {170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170};  

uint32_t hidrox[20];
uint32_t hidroy[20];

uint16_t contTime    = 0;

uint16_t current     = 0;

void setup() {
  Serial.begin(115200);
  delay(10);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(callback);

  current = getCont(0);
  delay(10);
  Serial.print("\r\ngetCont: ");
  Serial.println(current);
  _readH(current);
  delay(10);

  _printH(0);
  _printH(1);
  _printH(2);
  _printH(3);
  _printH(4);
  _printH(5);
  _printH(6);
  _printH(7);
  _printH(8);
  _printH(9);
  _printH(10);
  _printH(11);

  
//  _writeH(0,hidro0);
//  delay(50);
//  _writeH(1,hidro1);
//  delay(50);
//  _writeH(2,hidro2);
//  delay(50);
//  _writeH(3,hidro3);
//  delay(50);
//  _writeH(4,hidro4);
//  delay(50);
//  _writeH(5,hidro5);
//  delay(50);
//  _writeH(6,hidro6);
//  delay(50);
//  _writeH(7,hidro7);
//  delay(50);
//  _writeH(8,hidro8);
//  delay(50);
//  _writeH(9,hidro9);
//  delay(50);
//  _writeH(10,hidro10);
//  delay(50);
//  _writeH(11,hidro11);
//  delay(50);
}

void callback()
{
  contTime++;
  if (contTime>60)
  {
    if (current<11)
      _writeH(++current,hidro);
    else 
    {
      current = 0;
      _writeH(current,hidro);
    }
      
    contTime = 0;
  }
}

uint8_t getCont(uint8_t cont){
  uint8_t aux = 0;
  if (cont<11){
    for (int i=0; i<20; i++){
      hidrox[i] = (
                   ((unsigned long)EEPROM.read((cont*80)    +(i*4)  )<<24) | // 0   4   8  12  16  20  24  28  32  36  40  44  48  52  56  60  64  68  72  76
                   ((unsigned long)EEPROM.read((cont*80)    +(i*4)+1)<<16) | // 1   5   9  13  17  21  25  29  33  37  41  45  49  53  57  61  65  69  73  77
                   ((unsigned long)EEPROM.read((cont*80)    +(i*4)+2)<<8 ) | // 2   6  10  14  18  22  26  30  34  38  42  46  50  54  58  62  66  70  74  78
                   ((unsigned long)EEPROM.read((cont*80)    +(i*4)+3)    )   // 3   7  11  15  19  23  27  31  35  39  43  47  51  55  59  63  67  71  75  79
                  );
      hidroy[i] = (
                   ((unsigned long)EEPROM.read(((cont+1)*80)+(i*4)  )<<24) | //80  84  88  92  96 100 104 108 112 116 120 124 128 132 136 140 144 148 152 156
                   ((unsigned long)EEPROM.read(((cont+1)*80)+(i*4)+1)<<16) | //81  85  89  93  97 101 105 109 113 117 121 125 129 133 137 141 145 149 153 157
                   ((unsigned long)EEPROM.read(((cont+1)*80)+(i*4)+2)<<8 ) | //82  86  90  94  98 102 106 110 114 118 122 126 130 134 138 142 146 150 154 158
                   ((unsigned long)EEPROM.read(((cont+1)*80)+(i*4)+3)    )   //83  87  91  95  99 103 107 111 115 119 123 127 131 135 139 143 147 151 155 159
                  );
      //Serial.print(String(hidrox[i])+"<"+String(hidroy[i])+" \r\n");
    }
  }
  if ((hidrox[aux]<=hidroy[aux++]) && // x[ 0]<y[ 0]
      (hidrox[aux]<=hidroy[aux++]) && // x[ 1]<y[ 1]
      (hidrox[aux]<=hidroy[aux++]) && // x[ 2]<y[ 2]
      (hidrox[aux]<=hidroy[aux++]) && // x[ 3]<y[ 3]
      (hidrox[aux]<=hidroy[aux++]) && // x[ 4]<y[ 4]
      (hidrox[aux]<=hidroy[aux++]) && // x[ 5]<y[ 5]
      (hidrox[aux]<=hidroy[aux++]) && // x[ 6]<y[ 6]
      (hidrox[aux]<=hidroy[aux++]) && // x[ 7]<y[ 7]
      (hidrox[aux]<=hidroy[aux++]) && // x[ 8]<y[ 8]
      (hidrox[aux]<=hidroy[aux++]) && // x[ 9]<y[ 9]
      (hidrox[aux]<=hidroy[aux++]) && // x[10]<y[10]
      (hidrox[aux]<=hidroy[aux++]) && // x[11]<y[11]
      (hidrox[aux]<=hidroy[aux++]) && // x[12]<y[12]
      (hidrox[aux]<=hidroy[aux++]) && // x[13]<y[13]
      (hidrox[aux]<=hidroy[aux++]) && // x[14]<y[14]
      (hidrox[aux]<=hidroy[aux++]) && // x[15]<y[15]
      (hidrox[aux]<=hidroy[aux++]) && // x[16]<y[16]
      (hidrox[aux]<=hidroy[aux++]) && // x[17]<y[17]
      (hidrox[aux]<=hidroy[aux++]) && // x[18]<y[18]
      (hidrox[aux]<=hidroy[aux++]) && // x[19]<y[19]
      (cont<11)                       // break before hidro12
    )
   {
      //Serial.print("\r\n");
      getCont(cont+1);
   }
    
  else return cont;
}

void _writeH(uint8_t cont, uint32_t hid[]){
  for (int i = 0; i < 20; i++){
    EEPROM.update(((cont*80)+(i*4)  ), (hid[i]>>24)&0xFF  );
    EEPROM.update(((cont*80)+(i*4)+1), (hid[i]>>16)&0xFF  );
    EEPROM.update(((cont*80)+(i*4)+2), (hid[i]>>8 )&0xFF  );
    EEPROM.update(((cont*80)+(i*4)+3), (hid[i]    )&0xFF  );  
  }
}

void _readH(uint8_t cont){
  uint32_t temp = 0;
  for (int i = 0; i < 20; i++){
    temp = (((unsigned long)EEPROM.read((cont*80)+(i*4)  )<<24) | // 0   4   8  12  16  20  24  28  32  36  40  44  48  52  56  60  64  68  72  76
            ((unsigned long)EEPROM.read((cont*80)+(i*4)+1)<<16) | // 1   5   9  13  17  21  25  29  33  37  41  45  49  53  57  61  65  69  73  77
            ((unsigned long)EEPROM.read((cont*80)+(i*4)+2)<<8 ) | // 2   6  10  14  18  22  26  30  34  38  42  46  50  54  58  62  66  70  74  78
            ((unsigned long)EEPROM.read((cont*80)+(i*4)+3)    )   // 3   7  11  15  19  23  27  31  35  39  43  47  51  55  59  63  67  71  75  79
           );
    hidro[i] = temp;
  }
}

void _printH(uint8_t cont){
  Serial.print("Cont: "+String(cont)+" ");
  uint32_t temp = 0;
  for (int i = 0; i < 20; i++){
    temp = (((unsigned long)EEPROM.read((cont*80)+(i*4)  )<<24) | // 0   4   8  12  16  20  24  28  32  36  40  44  48  52  56  60  64  68  72  76
            ((unsigned long)EEPROM.read((cont*80)+(i*4)+1)<<16) | // 1   5   9  13  17  21  25  29  33  37  41  45  49  53  57  61  65  69  73  77
            ((unsigned long)EEPROM.read((cont*80)+(i*4)+2)<<8 ) | // 2   6  10  14  18  22  26  30  34  38  42  46  50  54  58  62  66  70  74  78
            ((unsigned long)EEPROM.read((cont*80)+(i*4)+3)    )   // 3   7  11  15  19  23  27  31  35  39  43  47  51  55  59  63  67  71  75  79
           );
    Serial.print("Hidro"+String(i)+":"+String(temp)+" ");
  }
  Serial.print("\r\n");
}

bool _zera(){
  for (int i = 0; i < 1024; i++)
    EEPROM.update(i, 0x00); 
}

void _incrementa(){
  for (int i = 0; i < 20; i++)
    hidro[i]= hidro[i] + i;
}

void loop() {
  delay(10000);
  _incrementa();
  _printH(current);
  
}
