import oscP5.*;
import netP5.*;

public class GlovesData {

  OscP5 oscP5;
  NetAddress destination;

  //==================================================
  // Declare glove variables
  public float pitchL, pitchR;
  public float yawL, yawR;
  public float rollL, rollR;
  public int drumRegionL, drumRegionR;
  public float drumIntensityL, drumIntensityR;
  public int directionL, directionR;
  public int postureL, postureR;
  public boolean gyroPeakXL, gyroPeakXR;
  public boolean gyroPeakYL, gyroPeakYR;
  public boolean gyroPeakZL, gyroPeakZR;
  public boolean drumL, drumR;
  public float magnitudeL, magnitudeR;
  public float[] flexL = new float[numberOfSensors];
  public float[] flexR = new float[6];
  public float averageFlexL, averageFlexR;
  public float wristAngle;

  //==================================================
  // constructor
  public GlovesData() {

    // start oscP5, telling it to listen for incoming messages at port 8080 */
    oscP5 = new OscP5(this, 8000);

    destination = new NetAddress("169.254.1.1", 9000);

    // initialise glove variables
    pitchL = 0.0; 
    pitchR = 0.0;
    yawL = 0.0;
    yawR = 0.0;
    rollL = 0.0;
    rollR = 0.0;
    drumRegionL = 0;
    drumRegionR = 0;
    drumIntensityL = 0.0;
    drumIntensityR = 0.0;
    directionL = 0;
    directionR = 0;
    postureL = -1; // (i.e. null posture)
    postureR = -1; // (i.e. null posture)
    gyroPeakXL = false;
    gyroPeakXR = false;
    gyroPeakYL = false;
    gyroPeakYR = false;
    gyroPeakZL = false;
    gyroPeakZR = false;
    drumL = false;
    drumR = false;
    magnitudeL = 0.0;
    magnitudeR = 0.0;
    for (int i = 0;i < 6;i++)
    {
      flexL[i] = 0.0;
      flexR[i] = 0.0;
    }

    averageFlexL = 0.0;
    averageFlexR = 0.0;
    wristAngle = 0.0;


  }

  public void pulseMotor()
  {
    {
      // create an osc message
      OscMessage m = new OscMessage("/output/digital/state/15");
      m.add(1); // add an int to the osc message
      oscP5.send(m, destination);
    }
    delay(100);
    {   
      // create an osc message
      OscMessage m = new OscMessage("/output/digital/state/15");
      m.add(0); // add an int to the osc message
      oscP5.send(m, destination);
    }
    {
      // create an osc message
      OscMessage m = new OscMessage("/output/digital/state/16");
      m.add(1); // add an int to the osc message
      oscP5.send(m, destination);
    }
    delay(100);
    {
      // create an osc message
      OscMessage m = new OscMessage("/output/digital/state/16");
      m.add(0); // add an int to the osc message
      oscP5.send(m, destination);
    }    
  }  

  public void setLeftLEDColour(int red, int green, int blue)
  {
    {
      // create an osc message
      OscMessage m = new OscMessage("/output/pwm/duty/2");
      m.add(red); // add an int to the osc message
      oscP5.send(m, destination);
    }
    {
      // create an osc message
      OscMessage m = new OscMessage("/output/pwm/duty/1");
      m.add(green); // add an int to the osc message
      oscP5.send(m, destination);
    }
    {
      // create an osc message
      OscMessage m = new OscMessage("/output/pwm/duty/3");
      m.add(blue); // add an int to the osc message
      oscP5.send(m, destination);    
    }
  }

  public void setRightLEDColour(int red, int green, int blue)
  {
    // create an osc message
    OscMessage m = new OscMessage("/glover/leds/");

    m.add(1); // first number indicates hand (0 = left, 1 = right)

    // then we add RGB values
    m.add(red); // add an int to the osc message
    m.add(green); // add a float to the osc message 
    m.add(blue); // add a string to the osc message

      // send the message
    oscP5.send(m, destination);
  }

  void oscEvent(OscMessage theOscMessage)
  {
    update(theOscMessage);
  }

  //==================================================
  // Retrieve updates via OSC
  public void update(OscMessage theOscMessage) 
  {  
    // retrieve the message address pattern as a string (e.g. /my/message)
    String messageType = theOscMessage.addrPattern();

    //================= ORIENTATION ===================
    //======== hand orientation in 3 dimensions =======

    //-------------------------------------------------
    // /glover/orientationL - left hand orientation
    // Three values: pitch, yaw and roll
    // range: [-180,180] for each value
    //
    if (messageType.equals("/glover/orientationL")) 
    {
      pitchL = theOscMessage.get(0).floatValue();
      rollL = theOscMessage.get(1).floatValue();
      yawL = theOscMessage.get(2).floatValue();
    }

    //-------------------------------------------------
    // /glover/orientationR - right hand orientation
    // Three values: pitch, yaw and roll
    // range: [-180,180] for each value
    //
    if (messageType.equals("/glover/orientationR")) 
    {
      pitchR = theOscMessage.get(0).floatValue();
      rollR = theOscMessage.get(1).floatValue();
      yawR = theOscMessage.get(2).floatValue();
    }




    //================== AVERAGE FLEX =================
    //=========== finger flex: open hand to fist ======

    //-------------------------------------------------
    // /glover/averageFlexL - left hand average flex
    // range: [0,1]
    //
    if (messageType.equals("/glover/averageFlexL")) 
    {
      averageFlexL = theOscMessage.get(0).floatValue();
    }


    //-------------------------------------------------
    // /glover/averageFlexR - right hand average flex
    // range: [0,1]
    //
    if (messageType.equals("/glover/averageFlexR")) 
    {
      averageFlexR = theOscMessage.get(0).floatValue();
    }

    //=================== DRUM HITS ===================
    //============== drum hitting gestures ============

    //-------------------------------------------------
    // /glover/drumL - left hand drum hit
    // event, with region and intensity
    //
    if (messageType.equals("/glover/drumL")) 
    {
      drumL = true;
      drumRegionL = theOscMessage.get(0).intValue();
      drumIntensityL = theOscMessage.get(1).floatValue();
    }

    //-------------------------------------------------
    // /glover/drumR - right hand drum hit
    // event
    //
    if (messageType.equals("/glover/drumR")) 
    {
      drumR = true;
      drumRegionR = theOscMessage.get(0).intValue();
      drumIntensityR = theOscMessage.get(1).floatValue();
    }


    //==================== DIRECTION ==================
    //======== number indicating hand direction =======

    //-------------------------------------------------
    // /glover/directionL - direction of left hand
    // values:
    // 0 forward
    // 1 backward
    // 2 left
    // 3 right
    // 4 down
    // 5 up
    //
    if (messageType.equals("/glover/directionL")) 
    {
      directionL = theOscMessage.get(0).intValue();
    }


    //-------------------------------------------------
    // /glover/directionR - direction of right hand
    // values:
    // 0 forward
    // 1 backward
    // 2 left
    // 3 right
    // 4 down
    // 5 up
    //
    if (messageType.equals("/glover/directionR")) 
    {
      directionR = theOscMessage.get(0).intValue();
    }


    //===================== POSTURE ===================
    //============= the current hand posture ==========

    //-------------------------------------------------
    // /glover/postureL - the current left hand posture
    // values:
    // -1 no posture
    // 0 fist
    // 1 puppet hand
    // 2 open hand
    // 3 one finger point
    // 4 secret thumb
    //
    if (messageType.equals("/glover/postureL")) 
    {
      postureL = theOscMessage.get(0).intValue();
    }


    //-------------------------------------------------
    // /glover/postureR - the current right hand posture
    // values:
    // -1 no posture
    // 0 fist
    // 1 puppet hand
    // 2 open hand
    // 3 one finger point
    // 4 secret thumb
    //
    if (messageType.equals("/glover/postureR")) 
    {
      postureR = theOscMessage.get(0).intValue();
    }




    //=============== HORIZONTAL GYRO PEAKS ===========
    //============= horizontal gyroscope peaks  =======

    //-------------------------------------------------
    // /glover/gyroPeakXL - left hand horizontal gyro peak
    // event
    //
    if (messageType.equals("/glover/gyroPeakXL")) 
    {
      gyroPeakXL = true;
    }


    //-------------------------------------------------
    // /glover/gyroPeakXR - right hand horizontal gyro peak
    // event
    //
    if (messageType.equals("/glover/gyroPeakXR")) 
    {
      gyroPeakXR = true;
    }


    //================ VERTICAL GYRO PEAKS ============
    //============== vertical gyroscope peaks  ========

    //-------------------------------------------------
    // /glover/gyroPeakYL - left hand vertical gyro peak
    // event
    //
    if (messageType.equals("/glover/gyroPeakYL")) 
    {
      gyroPeakYL = true;
    }


    //-------------------------------------------------
    // /glover/gyroPeakYR - right hand vertical gyro peak
    // event
    //
    if (messageType.equals("/glover/gyroPeakYR")) 
    {
      gyroPeakYR = true;
    }


    //================ WRIST GYRO PEAKS ===============
    //=========== wrist flick gyroscope peaks  ========

    //-------------------------------------------------
    // /glover/gyroPeakZL - left wrist flick gyro peak
    // event
    //
    if (messageType.equals("/glover/gyroPeakZL")) 
    {
      gyroPeakZL = true;
    }


    //-------------------------------------------------
    // /glover/gyroPeakZR - right wrist flick gyro peak
    // event
    //
    if (messageType.equals("/glover/gyroPeakZR")) 
    {
      gyroPeakZR = true;
    }


    //=================== WRIST ANGLE =================
    //============= the angle between wrists ==========

    //-------------------------------------------------
    // /glover/wristAngle - the angle between wrists
    // range: [0,180]
    //
    if (messageType.equals("/glover/wristAngle")) 
    {
      wristAngle = theOscMessage.get(0).floatValue();
    }

    //=================== MAGNITUDE =================
    //================ magnitude peaks ==============

    //-------------------------------------------------
    // /glover/magnitudeL - left hand magnitude peak
    // range: [0,12]
    //
    if (messageType.equals("/glover/magnitudeL")) 
    {
      magnitudeL = theOscMessage.get(0).floatValue();
    }

    //-------------------------------------------------
    // /glover/magnitudeL - right hand magnitude peak
    // range: [0,12]
    //
    if (messageType.equals("/glover/magnitudeR")) 
    {
      magnitudeR = theOscMessage.get(0).floatValue();
    }


    //===================== FLEX ====================
    //=========== flex values for fingers ===========

    //-------------------------------------------------
    // /glover/flexL - left hand magnitude peak
    // Six values:
    // * thumb
    // * index finger (lower)
    // * index finger (upper)
    // * middle finger (lower) 
    // * middle finger (upper) 
    // * ring finger
    // range: [0,1] for all values
    //
    if (messageType.equals("/input/analog"))     // modifed for x-OSC
    {
      int i = 0;
      flexL[0] = theOscMessage.get(1).floatValue();
      flexL[1] = theOscMessage.get(3).floatValue();
      flexL[2] = theOscMessage.get(2).floatValue();
      flexL[3] = theOscMessage.get(9).floatValue();
      flexL[4] = theOscMessage.get(10).floatValue();
      flexL[5] = theOscMessage.get(7).floatValue();
      flexL[6] = theOscMessage.get(8).floatValue();
      flexL[7] = theOscMessage.get(6).floatValue(); 

      flexL[8] = theOscMessage.get(4).floatValue(); 
      flexL[9] = theOscMessage.get(5).floatValue(); 
      flexL[10] = theOscMessage.get(11).floatValue(); 
      flexL[11] = theOscMessage.get(12).floatValue(); 
      flexL[12] = theOscMessage.get(13).floatValue(); 
      flexL[13] = theOscMessage.get(14).floatValue(); 
      flexL[14] = theOscMessage.get(15).floatValue(); 
      flexL[15] = theOscMessage.get(0).floatValue(); 

    }

    //-------------------------------------------------
    // /glover/flexR - right hand magnitude peak
    // Six values:
    // * thumb
    // * index finger (lower)
    // * index finger (upper)
    // * middle finger (lower) 
    // * middle finger (upper) 
    // * ring finger
    // range: [0,1] for all values
    //
    if (messageType.equals("/glover/flexR")) 
    {
      for (int i = 0;i < 6;i++)
      {
        flexR[i] = theOscMessage.get(i).floatValue();
      }
    }
  }
}



