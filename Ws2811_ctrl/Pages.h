int ext_bright = 0;
int ext_speed = 0;
int ext_cycle = 0;
int current_mode = 0;
int time_on = 0;
int time_off = 0;
int time_schedule = 0;
int time_fadein = 0;
int time_fadeout = 0;
int h_offset = 0;

String actual_anim;


String tz_place;
void get_tz_placeholder(){
  char tz_placeholder[10];
  if(h_offset<0){
  sprintf(tz_placeholder, "h%d",h_offset);
  }else{
    sprintf(tz_placeholder, "h+%d",h_offset);
    }  
    tz_place=tz_placeholder;
    //Serial.println(tz_place);
  }

String processor(const String& var){
  //Serial.println(var);
if(var == F("XPRT0")){
    String exif = "\""+String(ext_bright)+"\"";
    return exif;
  }
if(var == F("XPRT1")){
    String exif = "\""+String(ext_speed)+"\"";
    return exif;
  }
if(var == F("XPRT2")){
    String exif = "\""+String(ext_cycle)+"\"";
    return exif;
  }

if(var == F("XPRT3")){
    int h, m;
    h=(time_on-time_on%100)/100;
    m=time_on%100;
    char buffer[10];
    sprintf(buffer, "\"%02d:%02d\"", h, m);
    return buffer;
  }

if(var == F("XPRT4")){
    int h, m;
    h=(time_off-time_off%100)/100;
    m=time_off%100;
    char buffer[10];
    sprintf(buffer, "\"%02d:%02d\"", h, m);
    return buffer;
  }  
  if(var == F("XPRT5")){
    return actual_anim;
  } 
    if(var == F("XPRT6")){
    if(time_schedule==1){
    return "checked";
    }else{
    return "";
    }
  } 
      if(var == F("XPRT7")){
    if(time_fadein==1){
    return "checked";
    }else{
    return "";
    }
  }
      if(var == F("XPRT8")){
    if(time_fadeout==1){
    return "checked";
    }else{
    return "";
    }
  }
  
  if(var==tz_place){
    //Serial.println(tz_place);
    return "selected";
    }
  
  return String();
}
