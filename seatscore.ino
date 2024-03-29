/* SmartSeat Sketch
 */
 
 
int L1pin = 0; int L2pin = 1; int L3pin = 2; int R1pin = 3; int R2pin = 4; int R3pin = 5; int Bpin = 6; //Pins where our pressure pads are located, haven't made the model yet but change these to wherever the pins are for the sensors
double L1; double L2; double L3; double R1; double R2; double R3; double B; // INT variable for storing our readings

void setup(void) {
  Serial.begin(9600);
}
double rec(double a, double b)
{
  if(a > b)
    return a;
  else
    return 1.0/a;
}
void loop(void) {
  L1 = analogRead(L1pin);
  L2 = analogRead(L2pin);
  L3 = analogRead(L3pin);
  R1 = analogRead(R1pin);
  R2 = analogRead(R2pin);
  R3 = analogRead(R3pin);
  B = analogRead(Bpin);
  //the seat score scoring is going to be divided into three categories: weight on back, weight on front, and weight distribution between left and right
  double frontscore = 0.0;
  if(L2/L3 > 0.666)
    frontscore+=(L3/L2)*8.333*2.0/3.0;
  else 
    frontscore+=(L2/L3)*8.333*3.0/2.0;
  if(R2/R3 > 0.666)
    frontscore+=(R3/R2)*8.333*2.0/3.0;
  else 
    frontscore+=(R2/R3)*8.333*3.0/2.0;
  if(L1/L2 > 0.82)
    frontscore+=(L3/L2)*8.333*0.82;
  else 
    frontscore+=(L2/L3)*8.333/0.82;
  if(R1/R2 > 0.82)
    frontscore+=(L3/L2)*8.333*0.82;
  else 
    frontscore+=(L2/L3)*8.333/0.82;
  double backscore = 0.0;
  if((L3+R3)*0.5/B < 1.5) 
    backscore+= ((L3+R3)*0.5/B)*0.6666*33.33;
  else
    backscore+= 1.0/(((L3+R3)*0.5/B)*0.6666*33.33);
  double leftrightscore = 0.0;

 
  bool l1bias = (1.15*L1 > R1); bool l2bias = (1.15*L2 > R2); bool l3bias = (1.15*L3 > R3); bool r1bias = (1.15*R1 > L1); bool r2bias = (1.15*R2 > L2); bool r3bias = (1.15*R3 > L3);
  double avg = (rec(L1/R1,1.0)+rec(L2/R2,1.0)+rec(L3/R3,1.0))/3.0;
  leftrightscore = 33.33*(avg*avg);


  



  Serial.print("Seat Score = ");
  Serial.println(int(frontscore+backscore+leftrightscore));
  Serial.print("Front of Seat Score = ");
  Serial.println(int(3.0*frontscore));
  Serial.print("Back Pressure Score = ");
  Serial.println(int(3.0*backscore));
  Serial.print("Left Right Distribution Score = ");
  Serial.println(int(3.0*leftrightscore));
  
  
  
  delay(10000);
}