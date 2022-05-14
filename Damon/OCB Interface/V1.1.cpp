// OBC Interface Draft Program
// 05 May 2022
// Version 1.0

int xnum,ynum,znum;

string gpx = "get pmag x /n";
string gpy = "get pmag y /n";
string gpz = "get pmag z /n";
string gsx = "get smag x /n";
string gsy = "get smag y /n";
string gsz = "get smag z /n";
string smt = "set mode test /n";
string smr = "set mode run /n";
string mtrx = ;
string mtry = ;
string mtrz = ;
string css = "get css";
string temp = "get temp";

string command;

cout << "Please type in Your Command (Make sure you put /n at the end of your command): ";
cin >> command;


switch (command){
  case gpx:
    cout << "ok, "+ px;
    break;
  case gpy:
    cout << "ok, "+ py;
    break;
  case gpz:
    cout << "ok, " + pz;
    break;
  case gsx:
    cout << "ok, " + sx;
    break;
  case gsy:
    cout << "ok, " + sy;
    break;
  case gsz:
    cout << "ok, " + sz;
    break;
  case smt:
    cout << "ok, test";
    break;
  case smr:
    cout << "ok, run";
    break;
  case mtrx:
    cout << "ok, " + mx;
    break;
  case mtry:
    cout << "ok, " + my;
    break;
  case mtrz:
    cout << "ok, " + mz;
    break;
  case css:
    cout << "ok, " + V_css;
    break;
  case temp:
    cout << "ok, " + Temp_S;
    break;
  default:
    cout << "fail, 1"
}


void getPMAG(string str){

}
void getSMAG(string str){

}
void setMode(string str){

}
void setMTR(string str){

}
void getCSS(string str){

}
void getTemp(string str){
  
}
