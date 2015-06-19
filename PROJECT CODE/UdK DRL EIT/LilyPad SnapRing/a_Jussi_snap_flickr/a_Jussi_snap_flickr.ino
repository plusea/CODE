// snap-flicker jvm2013

// "bap" and "parp" are on loan from Hyperbole and a half.

/* ************************************** */
/* these values are for setting things up */

int normalmode=1; // change this to 1 if you want just pseudorandom blinking

// delays/effect "distances" to the left and right
int fdelaysleft[7]={
 0,13,12,12,20,20,15}; // first one is zero, no left one
int fdelaysright[7]={
 13,12,12,20,20,15,0}; //last one is zero, no right one
int slownessvalue[7]={
 0,1,2,3,4,5,0}; // these values can be used to slow down the effects on individual LEDs
/* ************************************** */

/* ******************************************* */
/* the stuff below is for the led light engine */
int rand_seed_pin=4; // or a1, if possible. It is not connected.

int led[7]={  
 3,5,6,9,10,11,14}; // LED pins

unsigned char sucRAND0=0x01; // pseudo-random generator (modified from someones implementation)
unsigned char sucRAND1=0x01; // four variables
unsigned char sucRAND2=0x01;
unsigned char sucRAND3=0x01;

//some variables for controlling the LEDs
int dval[7]={
 0,0,0,0,0,0,0};  // displayed brightness value
int val[7]={
 0,0,0,0,0,0,0};   // calculated brightness
int trg[7]={
 0,0,0,0,0,0,0};   // target brightness
int stepspeed[7]={
 1,1,1,1,1,1,1};  // speed of the effect
int dir[7]={
 0,0,0,0,0,0,0};  // direction of the effect
int flickerdiv[7]={
 0,0,0,0,0,0,0};  // used for attenuating the flicker (set to 0 in the code currently, as it is not prettylooking enough)
int flickerfreq[7]={
 0,0,0,0,0,0,0}; // brightness of the flicker (var name should be different)
int flickers[7]={
 0,0,0,0,0,0,0};  // ... forgot what this is
int flickdir[7]={
 0,0,0,0,0,0,0}; // direction of the flicker
int slowness[7]={
 0,0,0,0,0,0,0};  // delay that can be used to further slow down individual LEDs

// some variables for initiating new sparks/flickers.
int sparks=0;
int spark_delay=0;

// "gauss" table, to control the flicker max brightness to a more natural looking one
// modify with e.g. excel or similar
// can be used to create a candle effect quite nicely
const unsigned char pgauss_table[256]=
{
 0	,
 1	,
 2	,
 3	,
 4	,
 5	,
 6	,
 7	,
 8	,
 9	,
 10	,
 11	,
 11	,
 12	,
 13	,
 14	,
 15	,
 16	,
 17	,
 18	,
 19	,
 20	,
 21	,
 22	,
 23	,
 23	,
 24	,
 25	,
 26	,
 27	,
 28	,
 29	,
 30	,
 31	,
 32	,
 32	,
 33	,
 34	,
 35	,
 36	,
 37	,
 38	,
 39	,
 40	,
 41	,
 41	,
 42	,
 43	,
 44	,
 45	,
 46	,
 47	,
 48	,
 48	,
 49	,
 50	,
 51	,
 52	,
 53	,
 54	,
 55	,
 55	,
 56	,
 57	,
 58	,
 59	,
 60	,
 61	,
 61	,
 62	,
 63	,
 64	,
 65	,
 66	,
 66	,
 67	,
 68	,
 69	,
 70	,
 70	,
 71	,
 72	,
 73	,
 74	,
 75	,
 75	,
 76	,
 77	,
 78	,
 78	,
 79	,
 80	,
 81	,
 82	,
 82	,
 83	,
 84	,
 85	,
 85	,
 86	,
 87	,
 88	,
 88	,
 89	,
 90	,
 91	,
 91	,
 92	,
 93	,
 94	,
 94	,
 95	,
 96	,
 96	,
 97	,
 98	,
 98	,
 99	,
 100	,
 101	,
 101	,
 102	,
 103	,
 103	,
 104	,
 105	,
 105	,
 106	,
 107	,
 107	,
 108	,
 108	,
 109	,
 110	,
 110	,
 111	,
 112	,
 112	,
 113	,
 113	,
 114	,
 115	,
 115	,
 116	,
 116	,
 117	,
 118	,
 118	,
 119	,
 119	,
 120	,
 120	,
 121	,
 121	,
 122	,
 122	,
 123	,
 124	,
 124	,
 125	,
 125	,
 126	,
 126	,
 127	,
 127	,
 128	,
 128	,
 128	,
 129	,
 129	,
 130	,
 130	,
 131	,
 131	,
 132	,
 132	,
 133	,
 133	,
 133	,
 134	,
 134	,
 135	,
 135	,
 135	,
 136	,
 136	,
 137	,
 137	,
 137	,
 138	,
 138	,
 138	,
 139	,
 139	,
 139	,
 140	,
 140	,
 140	,
 141	,
 141	,
 141	,
 142	,
 142	,
 142	,
 142	,
 143	,
 143	,
 143	,
 144	,
 144	,
 144	,
 144	,
 145	,
 145	,
 145	,
 145	,
 145	,
 146	,
 146	,
 146	,
 146	,
 146	,
 147	,
 147	,
 147	,
 147	,
 147	,
 147	,
 148	,
 148	,
 148	,
 148	,
 148	,
 148	,
 148	,
 148	,
 149	,
 149	,
 149	,
 149	,
 149	,
 149	,
 149	,
 149	,
 149	,
 149	,
 149	,
 149	,
 149	,
 149	,
 149	,
 149	,
 149	,
 149	,
 150	,
 150
};

/***************************************************/
/***************************************************/
/***************************************************/
/*****************program below*********************/
/***************************************************/
/***************************************************/
/***************************************************/
void setup()
{
 Serial.begin(57600);

 // initialise the prandom-seed with noise
 sucRAND0=(char)analogRead(rand_seed_pin);
 if( sucRAND0==0)
 {
   sucRAND0=1;
 }
 Serial.print("Seed: ");  // to confirm that seed works
 Serial.println(sucRAND0);
}
/***************************************************/
unsigned char prand(void) // pseudorandom generator (modified from some example from the internet)
{
 unsigned char ucX=0;
 unsigned char ucY=0;

 if( (sucRAND3&0x80)==0x80 )
 {
   ucX=0x01;
 }
 if( (sucRAND2&0x02)==0x02 )
 {
   ucY=0x01;
 }
 ucX=(ucX^ucY);

 sucRAND3=sucRAND3<<1;
 sucRAND3=sucRAND3&0xFE;
 if( (sucRAND2&0x80)==0x80)sucRAND3|=0x01;
 sucRAND2=sucRAND2<<1;
 sucRAND2=sucRAND2&0xFE;
 if( (sucRAND1&0x80)==0x80)sucRAND2|=0x01;
 sucRAND1=sucRAND1<<1;
 sucRAND1=sucRAND1&0xFE;
 if( (sucRAND0&0x80)==0x80)sucRAND1|=0x01;
 sucRAND0=sucRAND0<<1;
 sucRAND0=sucRAND0&0xFE;

 if( (ucX&0x01) == 0x01 )
 {
   sucRAND0|=0x01;
 }
 return sucRAND3;
}
/***************************************************/
unsigned char pgauss(unsigned char ucNum)
{
 ucNum=pgauss_table[ucNum];
 return ucNum;
}
/***************************************************/
void target(int unit)
{
 if( normalmode==0)     // in this, a light reaches a target and then goes to zero
 {
   if( dir[unit]==1)// rise
   {
     if( trg[unit] > val[unit])
     {
       if( slowness[unit]>0)
       {
         slowness[unit]--;
       }
       else
       { 
         val[unit]+=stepspeed[unit];
         dval[unit]=val[unit];
         slowness[unit]=slownessvalue[unit];

       }
     }
     else
     {
       dir[unit]=0;
       trg[unit]=0;
       slowness[unit]=slownessvalue[unit];

       stepspeed[unit]=stepspeed[unit]/2;
       if( stepspeed[unit]==0)
       {
         stepspeed[unit]=1;
       }
       flickdir[unit]=1;
       flickerdiv[unit]=1;    
       flickers[unit]=flickerfreq[unit]/2+1;
     }
   }
   else
   {
     if( trg[unit] < val[unit])
     {
       if( slowness[unit]>0)
       {
         slowness[unit]--;
       }
       else
       {
         val[unit]-=stepspeed[unit];
         slowness[unit]=slownessvalue[unit];
       }
       if( flickerfreq[unit]>0)
       {
         if( flickdir[unit]==1)
         {
           if(flickers[unit]<flickerfreq[unit])
           {
             flickers[unit]++;
           }
           else
           {
             flickdir[unit]=0;
           }
         }
         else
         {
           if( flickers[unit]>0)
           {
             flickers[unit]--;
           }
           else
           {
             flickdir[unit]=1;
           }
         }
       }
     }
   }
 }
 else  // this code initiates a next target when the target is reached
 {
   if( dir[unit]==1)// rise
   {
     if( trg[unit] > val[unit])
     {
       if( slowness[unit]>0)
       {
         slowness[unit]--;
       }
       else
       { 
         val[unit]+=stepspeed[unit];
         slowness[unit]=slownessvalue[unit];
       }
     }
     else
     {
       trg[unit]=pgauss(prand())+90;
       stepspeed[unit]=(prand()/32)+1;
       if( trg[unit]>val[unit])
       {
         dir[unit]=1;
       }
       else
       {
         dir[unit]=0;
       }
     }
   }
   else // fall
   {
     if( trg[unit] < val[unit])
     {
       if( slowness[unit]>0)
       {
         slowness[unit]--;
       }
       else
       { 
         val[unit]-=stepspeed[unit];
         slowness[unit]=slownessvalue[unit];
       }
     }
     else
     {
       trg[unit]=pgauss(prand())+90;
       stepspeed[unit]=(prand()/32)+1;
       if( trg[unit]>val[unit])
       {
         dir[unit]=1;
       }
       else
       {
         dir[unit]=0;
       }
     }
   }
 }
} 
/***************************************************/
int spark()
{
 int newspark=prand()%7;   // cap pseudorandomness to 0-7
 return newspark;
}
/***************************************************/
void generate_spark()  // this generates a new spark to a random slot
{
 if( normalmode==0)
 {
   if( spark_delay==0)
   {
     sparks=spark();
     if( val[sparks]<2 )
     {
       spark_delay=prand()*2;
       trg[sparks]=pgauss(prand()+80);
       stepspeed[sparks]=(prand()/64)+1;
       flickerfreq[sparks]=0;//(prand()/8)+6; // this is what makes the flickering, and is not so good, part 1
       dir[sparks]=1;
     }
   }
   else
   {
     spark_delay--;
   }
 }
}
/***************************************************/
void propagate(int unit)
{
 if( normalmode==0)
 {
// special cases at the beginning, as to not go over the edges
// do first and last LED as last and first.
   if( unit == 7)
   {
     if( val[unit-1] < val[unit]-fdelaysleft[unit] )
     {
       trg[unit-1]=val[unit]-fdelaysleft[unit];
       dir[unit-1]=1;
       stepspeed[unit-1]=1;

       if( trg[unit-1]<0)
       {
         trg[unit-1]=0;
         dir[unit-1]=0;
       }
     }
   }
   else if (unit > 0)
   {
     if( val[unit-1] < val[unit]-fdelaysleft[unit] )
     {
       trg[unit-1]=val[unit]-fdelaysleft[unit];
       dir[unit-1]=1;
       stepspeed[unit-1]=1;

       if( trg[unit-1]<0)
       {
         trg[unit-1]=0;
         dir[unit-1]=0;
       }
     }
     if( val[unit+1] < val[unit]-fdelaysright[unit])
     {
       trg[unit+1]=val[unit]-fdelaysright[unit];
       dir[unit+1]=1;
       stepspeed[unit+1]=1;

       if( trg[unit+1]<0)
       {
         trg[unit+1]=0;
         dir[unit+1]=0;
       }
     }
   }
   else if(unit == 0)
   {
     //special cases

     if( val[unit+1] < val[unit]-fdelaysright[unit])
     {
       trg[unit+1]=val[unit]-fdelaysright[unit];
       dir[unit+1]=1;
       stepspeed[unit+1]=1;

       if( trg[unit+1]<0)
       {
         trg[unit+1]=0;
         dir[unit+1]=0;
       }
     }
   }
 }
}
/***************************************************/
void visiblespark(int unit)
{
 if(normalmode==0)
 {
   // this is what makes the flickering, part 2
   dval[unit]=val[unit]+(flickerfreq[unit]/2-flickers[unit]);

// check that there is no underrun
   if( dval[unit] < 0)
   {
     dval[unit]=0;
   }
// check that there is no overrun
   if( dval[unit]>255)
   {
     dval[unit]=255;
   }
//slow down at the end, if possible
   /*  if( val[unit] < 10 )  // makes the effect slow down a bit just before the end
    {
    stepspeed[unit]=1;
    }*/

// if actual value less than zero, force to zero, to keep sanity
   if( val[unit]<=0)
   {
     val[unit]=0;
     dval[unit]=0;
   }
 }
 else
 {
   dval[unit]=val[unit];    
 }
}
/***************************************************/
// flicker does... flickering.
void flicker()
{
 // do this for each separately.
 // The order of LEDs here determines the priority of propagation.
 for( int parp=0;parp<7;parp++)
 {
   target(parp);
   propagate(parp);
   visiblespark(parp);
 }
}
/***************************************************/
void loop() 
{
 generate_spark();
 flicker();

 // please note, that the last LED is not used in updating.
 for(int bap=0;bap<6;bap++)
 {
   analogWrite(led[bap], dval[bap]);
 }

 delay(4); // delay between 5 and 10 works fine
}
/***************************************************/
/***************************************************/
/*
And the raven, never flitting, still is sitting, still is sitting
*/
