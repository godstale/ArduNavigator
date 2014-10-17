void calcAng(){

  (navAng<90) ? b=270+navAng : b=navAng-90; //this is to correct the 90-degrees-clockwise shift between screen angular system and the app's one
  
  diff=abs(b-a);

  if(diff>asp){ //calculates angular speed adding to the default one the acceleration
    uasp=asp+(diff/aac);
  }
  else uasp=0;

  ar=a*1000/57296; //conversione deg->rad
  br=(float(b))*1000/57296;

  if(b>a && diff>=180) //makes the arrow rotate clockwise or countercw,given the difference between destination angle and arrow angle
    a-=uasp;

  if(b>a && diff<180)
    a+=uasp;

  if(b<a && diff>=180)
    a+=uasp;

  if(b<a && diff<180)
    a-=uasp;

  if(a>360)
    a-=360;

  if(a<0)
    a=360-abs(a);


}

void calcCoor(){ //calculates coordinates of arrow vertexes ,and of the destination point

  ax=(r-10)*cos(ar+PI/2)+ox;
  ay=(r-10)*sin(ar+PI/2)+oy;

  bx=(r-10)*cos(ar-PI/2)+ox;
  by=(r-10)*sin(ar-PI/2)+oy;

  cx=(r)*cos(ar)+ox;
  cy=(r)*sin(ar)+oy;

  mx=(r/2)*cos(ar)+ox;
  my=(r/2)*sin(ar)+oy;

  dx=(r+5)*cos(br)+ox;
  dy=(r+5)*sin(br)+oy;
}
