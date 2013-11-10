/* 
 *                                !
 *            H|H|H|H|H           H__________________________________
 *            H|H|H|H|H           H|* * * * * *|---------------------|
 *            H|H|H|H|H           H| * * * * * |---------------------|
 *            H|H|H|H|H           H|* * * * * *|---------------------|
 *            H|H|H|H|H           H| * * * * * |---------------------|
 *            H|H|H|H|H           H|---------------------------------|
 *         ===============        H|---------------------------------|
 *           /| _   _ |\          H|---------------------------------|
 *           (| O   O |)          H|---------------------------------|
 *           /|   U   |\          H-----------------------------------
 *            |  \=/  |           H
 *             \_..._/            H
 *             _|\I/|_            H
 *     _______/\| H |/\_______    H
 *    /       \ \   / /       \   H
 *   |         \ | | /         |  H
 *   |          ||o||          |  H
 *   |    |     ||o||     |    |  H
 *   |    |     ||o||     |    |  H  
 *
 * +++++++++++++++++++++++++++++++++++++++
 *         MAPPING ESPIONAGE : 
 * INDIVIDUALS IN THE PERSEREC ESPIONAGE 
 *             DATABASE
 * +++++++++++++++++++++++++++++++++++++++
 */

import de.bezier.data.*;

XlsReader reader;
int numRows;
int startRow = 1;
int volunteer;
int recruit;
PFont fontA;
String[] countries;

void setup() {
  size(600, 400);
  reader = new XlsReader(this, "perserec.xls");
  numRows = reader.getLastRowNum();
  fontA = loadFont("AmericanTypewriter-48.vlw");
  textFont(fontA, 32);
}

void draw() {
  //differentCountries();
  volVSrec();
}


void differentCountries() {
  //hashmap
  //keyvaluepad
  background(0);
  for (int i=0; i<numRows;i++) {
    String country = getCountry(i);
    for (int j=0; j<i;j++) {
      //if(country == countries[j])
    }
    
      for (int h=0; h<numRows;h++) {
    text("Names of Countries: " + countries[h], 100, 100);
  }
}



  void volVSrec() {
    background(0);
    volunteer = 0;
    recruit=0;
    for (int i=0; i<numRows;i++) {
      String test = getType(i);
      if (test == "Volunteer") volunteer++;
      if (test == "Recruit") recruit++;
    }
    text("Number of Volunteers: " + volunteer, 100, 100);
    text("Number of Recruits: " + recruit, 100, 200);
  }


  /** GET FUNCTIONS **/

  String getSurname(int id) {
    return reader.getString(id, 0);
  }

  String getFirstName(int id) {
    return reader.getString(id, 1);
  }

  String getAffiliation(int id) {
    return reader.getString(id, 2);
  }

  String getStartDate(int id) {
    return reader.getString(id, 3);
  }

  int getStartYear(int id) {
    return int(split(reader.getString(id, 3), "/")[0]);
  }

  int getStartMonth(int id) {
    return int(split(reader.getString(id, 3), "/")[1]);
  }

  String getArrestDate(int id) {
    return reader.getString(id, 4);
  }

  int getArrestYear(int id) {
    return int(split(reader.getString(id, 4), "/")[0]);
  }

  int getArrestMonth(int id) {
    return int(split(reader.getString(id, 4), "/")[1]);
  }

  String getType(int id) {
    String type = reader.getString(id, 5);
    if (match(type, "V")!=null) {
      return "Volunteer";
    }
    else if (match(type, "R")!=null) {
      return "Recruit";
    }
    else {
      return "Unknown";
    }
  }

  String getCountry(int id) {
    return reader.getString(id, 6);
  }

