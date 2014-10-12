boolean receiveBluetoothData() {

  if(BTSerial.available()) {

    if(BTSerial.read()==TR_START_BYTE_1){

      if(BTSerial.read()==TR_START_BYTE_2){
        
        if(DEBUG)Serial.println("transmitting");

        clearMessage();
        
        for(int i=0;i<5;i++){
          btMessage[i]=byte(BTSerial.read());
        }


        if(btMessage[3]==TR_END_BYTE_1 && btMessage[4]==TR_END_BYTE_2){
          
          if(DEBUG)btDebug();
          
          return true;
        }

        if(DEBUG)Serial.println("bad transmission");


      }
    }
  }

  return false;
} 

void getInfos(){
  getMode();
  getDir();
  getUnit();
  getDist();
  getAngle();
}


boolean getMode(){
  navMode = (btMessage[0] & 0x80)>>7;
}

char getUnit(){

  switch(btMessage[0] & 0x60){
  case 0x00 :
    navUnit = 'm';
    break;
  case 0x20 :
    navUnit = 'k';
    break;
  case 0x40 :
    navUnit = 'f';
    break;
  case 0x60 :
    navUnit = 'n';
    break;
  }

}

char getDir(){

  switch(btMessage[0] & 0x18){
  case 0x08 :
    navDir = 'r';
    break;
  case 0x18 :
    navDir = 'b';
    break;
  case 0x00 :
    navDir = 'l';
    break;
  case 0x10 :
    navDir = 'f';
    break;
  }

}

unsigned int getDist(){
  navDist = 0;
  navDist+=int( (btMessage[0] & 0x07) << 7);
  navDist+=int( (btMessage[1] & 0x7f) );
}

unsigned int getAngle(){
  navAng = 0;
  navAng+=int( (btMessage[1] & 0x80) << 8);
  navAng+=int( (btMessage[2] & 0xff) );

}

void clearMessage(){

  for(int i=0;i<5;i++){
    btMessage[i] &= 0;
  }

}













