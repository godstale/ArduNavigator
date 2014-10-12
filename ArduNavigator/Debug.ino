void btDebug(){
          Serial.println(btMessage[0],BIN);
          Serial.println(btMessage[1],BIN);
          Serial.println(btMessage[2],BIN);
          
          Serial.println("success");
          getInfos();
          Serial.println(navDir);
          Serial.println(navUnit);
          Serial.println(navDist,DEC);
          Serial.println(navAng,DEC);
}
