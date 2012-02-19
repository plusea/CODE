void serialEvent(int serialINPUT){
  if(myCatch == true) {
    if(serialINPUT != 10) {        
      // add event to buffer
      buffer += char(serialINPUT); 
      //println(serialINPUT);      
    }
    else {
      // if serial is line break set value to buffer value and clear buffer
      value = int(buffer);
      xPosArr[(prefix-1)] = value;
      myCatch = false;     
      buffer="";
      println(xPosArr[1]);
    }
  } 
  //myCatch is the beginging of the each sended number used to define the port
  // myCatch gets true if serial is less than 10 since header is 1-9
  if (!myCatch && serialINPUT < 10) { 
    myCatch = true;
    prefix = int(serialINPUT);
  }
}
