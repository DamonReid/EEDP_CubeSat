
float mag[3];
float maghist[3];
float curr[3];
const float kw = 2.3809*1/100000;
const float N = 2000;
const float A = 0.0001;

void bDot(){
  if(magHist != null){
    float k = -kw/(mag[1]^2+mag[2]^2+mag[3]^2);
    for(int axis = 0; axis<3; axis++){
      float m = (((mag[axis]-maghist[axis])*k);
      curr[axis] = m/(N*A);
    }
  }
  maghist = mag;
}


/*m = (b(n)-b(n-1))*k
 * 
 * k = -kw/norm(b(n))^2 (bx^2+by^2+bz^2)
 * 
 * kw = .4e-05
 * 
 * I = m/(N*A*an)
 * 
 */
