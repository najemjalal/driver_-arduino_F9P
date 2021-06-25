#include "SDCARD.h"
#include "define.h"
#include <SPI.h>
#include <SD.h>

// Set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;
bool sdIn = false;

// MKRZero built-in SD port : SDCARD_SS_PIN
const int chipSelect = SDCARD_SS_PIN;
File myFile; // File handler

// Initialize the SD card, needed before any read or write operation
void sdcard_cardInit(){
  Serial.print("\nInitializing SD card...");
  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if ((!card.init(SPI_HALF_SPEED, chipSelect)) || (!SD.begin(chipSelect))) {
    sdIn=false;
    Serial.println("Initialization failed.");
    digitalWrite(OUT_SDCARDERROR_LED_PIN, HIGH);
  } else {
    Serial.println("Initialization done.");
    sdIn = true;
    sdcard_cardInfo();
    sdcard_volumeInfo();
    digitalWrite(OUT_SDCARDERROR_LED_PIN, LOW);
  }
}

// Display information about the SD card plugged in
void sdcard_cardInfo(){
  // print the type of card
  if(sdIn){
    Serial.println();
    Serial.print("Card type:         ");
    switch (card.type()) {
      case SD_CARD_TYPE_SD1:
        Serial.println("SD1");
        break;
      case SD_CARD_TYPE_SD2:
        Serial.println("SD2");
        break;
      case SD_CARD_TYPE_SDHC:
        Serial.println("SDHC");
        break;
      default:
        Serial.println("Unknown");
    }
    // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
    if (!volume.init(card)) {
      digitalWrite(OUT_SDCARDERROR_LED_PIN, HIGH);
      Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    }
  
    Serial.print("Clusters:          ");
    Serial.println(volume.clusterCount());
    Serial.print("Blocks x Cluster:  ");
    Serial.println(volume.blocksPerCluster());
  
    Serial.print("Total Blocks:      ");
    Serial.println(volume.blocksPerCluster() * volume.clusterCount());
    Serial.println();
  }
}

// Display informations about the volume size of the SD card
void sdcard_volumeInfo(){
  if(sdIn){
    // print the type and size of the first FAT-type volume
    uint32_t volumesize;
    Serial.print("Volume type is:    FAT");
    Serial.println(volume.fatType(), DEC);
  
    volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
    volumesize *= volume.clusterCount();       // we'll have a lot of clusters
    volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
    Serial.print("Volume size (Kb):  ");
    Serial.println(volumesize);
    Serial.print("Volume size (Mb):  ");
    volumesize /= 1024;
    Serial.println(volumesize);
    Serial.println("");
  }
}

// Check that the folder exists or create it
void sdcard_checkDirectory(String directory){
  if(sdIn){
    if(SD.mkdir(directory)){
        Serial.println(directory + " exists or created");
      } else {
        Serial.println(directory + " not created");
      }
  }
}

// Write data into text file
void sdcard_writeFile(String file,String data){
  if(sdIn){
    myFile = SD.open(file, FILE_WRITE);
    if (SD.exists(file)) {
//      Serial.println(file +" exists.");
      myFile.print(data);
      myFile.close();
//      Serial.println(data + " written to "+ file );
    } else {
      digitalWrite(OUT_SDCARDERROR_LED_PIN, HIGH);
//      Serial.println(file +" doesn't exist.");
    }
  }
}

// Read the content of the file f
void sdcard_readFile(String f){
  if(sdIn){
    // re-open the file for reading:
    myFile = SD.open(f);
    if (myFile) {
      Serial.println("Reading in "+f);
      // read from the file until there's nothing else in it:
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      // close the file:
      myFile.close();
    } else {
      digitalWrite(OUT_SDCARDERROR_LED_PIN, HIGH);
      // if the file didn't open, print an error:
      Serial.println("Error opening "+f);
    }
  }
}

// Delete file f
void sdcard_deleteFile(String f){
  char buf[f.length()];
  f.toCharArray(buf,f.length());
  if(sdIn){
    if (SD.remove(buf)) {
      Serial.println(f + " deleted");
    } else {
      Serial.println("Error deleting "+f);
    }
  }
}

// Display a list of the files into the SD card with their name, date and size
void sdcard_filesInfo(){
  if(sdIn){
    Serial.println("\nFiles found on the card (name, date and size in bytes): ");
    root.openRoot(volume);
  
    // list all files in the card with date and size
    root.ls(LS_R | LS_DATE | LS_SIZE);
  }
}

// Line to display on the screen with the file size
String sdcard_getFileLine(String f){
  unsigned long s=0;
  String line;
  if(sdIn){
    myFile = SD.open(f);
    s = myFile.size();
    myFile.close();
    line = "File size : " + String(s/1024.0,1)+"Kb";
  }else{
    line = "No SD card";
  }
  return line;
}
