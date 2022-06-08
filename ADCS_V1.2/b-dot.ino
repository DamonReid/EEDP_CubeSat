
float mag[3];
float maghist[3];
float curr[3];
float m[3];
float kw;

void bDot(){
  float k = (-kw/abs(magnetometer)^2)+(mag[1]^2+mag[2]^2+mag[3]^2);
  m = (mag-maghist*k;
  
}


/*m = (b(n)-b(n-1)*k)
 * 
 * k = -kw/norm(b(n))^2 (bx^2+by^2+bz^2)
 * 
 * kw = .4e-05
 * 
 * 
 */
