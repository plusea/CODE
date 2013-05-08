#if defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny84__)



const int Pin0 = 0;

const int Pin1 = 1;

const int Pin2 = 2;

const int Pin3 = 3;

const int pintemp = 4;



#else

// IOpins virtualisieren

const int Pin0 = 4;

const int Pin1 = 5;

const int Pin2 = 6;

const int Pin3 = 7;

// nicht 10/11/13 wg. interner Widerst‰nde



const int pintemp = 0;

#endif





const byte pins[] = {

  Pin0, Pin1, Pin2, Pin3};



byte pinssegment [7][2] = {

  { 

    Pin0 , Pin2                   }

  , { 

    Pin2 , Pin3                   }

  ,{ 

    Pin1 , Pin3                   }

  ,{ 

    Pin1 , Pin0                   }

  ,{ 

    Pin0 , Pin1                   }

  ,{ 

    Pin2 , Pin0                   }

  ,{ 

    Pin2 , Pin1                   }

};



byte segment[10] = {

  // ABCDEFG

  0b01111110,

  0b00110000,

  0b01101101,

  0b01111001,

  0b00110011,

  0b01011011,

  0b00011111,

  0b01110000,

  0b01111111,

  0b01111011 

};



byte displaydigit = 0;





void showdigit(){



  for (int segments=0;segments<7;segments++){ 

    // Mode setzen

    // alle auf Input

    for (int j=0;j<sizeof(pins);j++) {

      pinMode(pins[j],INPUT);

    }

    // und nun die entsprechenden Digits anschalten

    if ( (segment[displaydigit] & (64 >> segments))!=0) {

      pinMode(pinssegment[segments][0],OUTPUT);

      pinMode(pinssegment[segments][1],OUTPUT);

      digitalWrite(pinssegment[segments][0],HIGH);

    }

    delay(1);

  }

}





void setup(){ 

  analogReference(INTERNAL);

}



int start;



void loop(){



  int tempi;

  

  showdigit();

  if (millis()-start>1000){

    // daten vom lm35dz

    int tempi = analogRead(pintemp);

    tempi = tempi / 0.931;

    tempi = (tempi + 5) / 10;

    displaydigit = tempi % 10; 

    start=millis();

  }

}






