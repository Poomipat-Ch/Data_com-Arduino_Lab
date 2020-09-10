import processing.serial.*;
import java.io.*;
int mySwitch=0;
int counter=0;
String [] subtext;
Serial myPort;


void setup(){
 mySwitch=1;
 myPort = new Serial(this, "COM9", 115200);
 myPort.bufferUntil('\n');
}

void draw() {
   
  background(255);
 if (mySwitch>0){
    readData("C:/Users/Kenta420/Desktop/test.txt");
    mySwitch=0;
 }
 
  
 
 if(counter<subtext.length){
     myPort.write(subtext[counter]);
     fill(0,0,0);
     text(subtext[counter], 10, 30);
     delay(500);
     myPort.write('0');
     delay(100);
     counter++;
 } else{
    delay(5000);
    mySwitch=1;
 }
} 

void readData(String myFileName){
 
 File file=new File(myFileName);
 BufferedReader br=null;
 
 try{
 br=new BufferedReader(new FileReader(file));
 String text=null;
 
while((text=br.readLine())!=null){
  subtext = splitTokens(text,"");
 }
 }catch(FileNotFoundException e){
 e.printStackTrace();
 }catch(IOException e){
 e.printStackTrace();
 }finally{
 try {
 if (br != null){
 br.close();
 }
 } catch (IOException e) {
 e.printStackTrace();
 }
 }
}
