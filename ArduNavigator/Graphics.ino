void compassMode(){
  calcAng();
  calcCoor();
  
  display.clearDisplay();
  dispInfos();
  drawArrow();
  display.display();
  
}

void directionsMode(){
}

void dispInfos(void){
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(1, 1);
  //display.print("Dist: ");
  display.print(navDist);

  switch(navUnit){
  case 'k':
    display.print(" km");
    break;
  case 'm':
    display.print(" mt");
    break;
  case 'f':
    display.print(" ft");
    break;
  case 'n':
    display.print(" ml");
    break;
  }
  
  display.setCursor(1,30);
  display.print(navAng);
  display.print("'");

}


void drawArrow(void){

  display.drawCircle(dx,dy,2,WHITE);

  //display.drawCircle(ox,oy,r);
  display.drawLine(ax,ay,mx,my,WHITE);
  display.drawLine(mx,my,bx,by,WHITE);
  display.drawLine(bx,by,cx,cy,WHITE);
  display.drawLine(cx,cy,ax,ay,WHITE);



}

