void keyPressed() {
  if (key == 'c') {
    myPort.write('c');
    mode = 'c'; 
    println("Mode C");
  }

  if (key == 'g') {
    myPort.write('g');
    mode = 'g'; 
    println("Mode G");
  }
  
  if (key == 'p') {
    myPort.write('p');
    mode = 'p';
    println("Mode P");
  }
}
