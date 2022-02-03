/*
 This code runs a program that detects the temperature of a cup of tea and displays it on 
 a LCD while also displaying a pre-set alarm temperature. When the detected temperature of the 
 tea equals the alarm temperature then a Piezo capsule transducer plays the Star Wars theme
 until the tea temperature goes to 15 degrees or lower. Once at this point the LCD is wiped
 and the message "Tea ruined" is displayed on it and the program terminates
 */

 #include <LiquidCrystal.h>   //library file for the LCD
 LiquidCrystal lcd(12,11,5,4,3,2);  //defining the LCD pins used
 
 int sensor_pin = A0;   //setting the analogue input pin for the TMP36
 int sensor_data;   //variable used to contain the data from the TMP36
 int alarm_temp = 40;   //setting the temperature that the music will start to play at
 int tea_cold = 15;   //setting the temperature for when the tea is ruined
 double temp_value;   //setting the variable used that contains the current tea temperature as a double

 //buzzer notes - setting the frequency value for each
 const int c = 261;
 const int d = 294;
 const int e = 329;
 const int f = 349;
 const int g = 391;
 const int gS = 415;
 const int a = 440;
 const int aS = 455;
 const int b = 466;
 const int cH = 523;
 const int cSH = 554;
 const int dH = 587;
 const int dSH = 622;
 const int eH = 659;
 const int fH = 698;
 const int fSH = 740;
 const int gH = 784;
 const int gSH = 830;
 const int aH = 880;

 const int buzzerPin = 9;   //sets the digital output for the buzzer
 int counter = 0;   //setting the start counter to zero


 //setup function
 void setup(){
  lcd.begin(16,2);  //define the LCD display type
  Serial.begin(9600);   //sets data rate to 9600 bits per second for serial data transmission
  pinMode(buzzerPin, OUTPUT);   //sets the buzzer pin to act as an OUTPUT
 }

 //main  that loops until the program ends updating the temp_value every 25ms
 void loop(){
  lcd.clear();  //clears the LCD
  temperature();  //calls the function temperature

  //an if statement to determine if the tea is ready to be drunk/ruined
  if(temp_value <= alarm_temp && temp_value > tea_cold){  //setting conditions for if the music will play

    //the functions that run the code that enables the music to be played
    //calls the functions that play the music
    firstSection();   //called the function firstSection
    secondSection();  //called the function secondSection
 
    //slight varient to the music
    beep(f, 250);   //calls the beep function passing in the note frequency and its duration
    beep(gS, 500);  
    beep(f, 350);  
    beep(a, 125);
    beep(cH, 500);
    beep(a, 375);  
    beep(cH, 125);
    beep(eH, 650);
    delay(500);   //delay in the music
 
    secondSection();    //repeats the second section again
 
  //slight varient to the music again
    beep(f, 250);   //calls the beep function passing in the note frequency and its duration
    beep(gS, 500);  
    beep(f, 375);  
    beep(cH, 125);
    beep(a, 500);  
    beep(f, 375);  
    beep(cH, 125);
    beep(a, 650);  
    delay(650);   //delay in the music
  }
  
  //stops the music and prints a message when the tea expires
  else if(temp_value < tea_cold){
    lcd.clear();  //clears the LCD
    lcd.print("Tea is ruined");   //displays a message on the LCD
    exit(1);
  }

  delay(25);  //delay of 25ms before the function loops round again
 }


//function to read the temperature then display it on the LCD
 void temperature(){
  sensor_data = analogRead(A0);   //reads the value from the specified analogue pin
  //the following lines of code convert the input voltage of the TMP36 to a value in Celsius
  temp_value = (double)sensor_data/1024;  //divide by 1024 to give integer values between 0-1023
  temp_value = temp_value*5;  //x5 to find the percentage of 5V for each integer value. About 0.01V equals 1 degree C
  temp_value = temp_value-0.5;  //subtract 0.5 so that the voltage range is between -50 to 125 degrees C in line with the TMP36 specs
  temp_value = temp_value*100;  //x100 to convert mV to degrees C

  lcd.print("Tea Temp: "); //print text on first line of LCD
  lcd.print(temp_value);  //prints the current temp_value
  lcd.setCursor(0,1); //set to print on the second line of LCD
  lcd.print("Alarm Temp: "); //print text on second line of LCD
  lcd.print(alarm_temp);  //prints the alarm_temp value
 }

//function that runs the buzzer using the inputs note frequency and its duration
void beep(int note, int duration){

  tone(buzzerPin, note, duration);  //plays the tone of the note for the set duration
 
  //plays durations based on the value of counter
  if(counter % 2 == 0)
  {
    delay(duration);  
  }
  else
  {
    delay(duration);
  }

  noTone(buzzerPin);   //stop tone on buzzerPin
  delay(50);  //delays the program by 50ms
  counter++;  //increment counter
}

//firstSection function that sets the notes played and the duration of each
//calls beep which runs the buzzer passing the note and duration to it
void firstSection(){
  beep(a, 500);   //calls the beep function passing in the note frequency and its duration
  beep(a, 500);    
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);  
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  delay(500);   //delay in the music
 
  beep(eH, 500);  //calls the beep function passing in the note frequency and its duration
  beep(eH, 500);
  beep(eH, 500);  
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  delay(500);   //delay in the music
}

//secondSection function that sets the notes played and the duration of each
//calls beep which runs the buzzer passing the note and duration to it
void secondSection(){
  beep(aH, 500);  //calls the beep function passing in the note frequency and its duration
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);    
  beep(fSH, 250);
 
  delay(325);   //delay in the music
 
  beep(aS, 250);  //calls the beep function passing in the note frequency and its duration
  beep(dSH, 500);
  beep(dH, 325);  
  beep(cSH, 175);  
  beep(cH, 125);  
  beep(b, 125);  
  beep(cH, 250);  
 
  delay(350);   //delay in the music
}
