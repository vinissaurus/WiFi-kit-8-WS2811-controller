int ext_bright = 0;
int ext_speed = 0;
int ext_cycle = 0;
int current_mode = 0;
int time_on = 0;
int time_off = 0;
int time_schedule = 0;
int time_fadein = 0;
int time_fadeout = 0;
String actual_anim;



const char index_html[] PROGMEM = R"rawliteral(

<meta name="viewport" content="width=device-width, initial-scale=1.0">
<!DOCTYPE html>
<html>

<body>

  <h1>WS2811 Configuration</h1>
  <h2>LED settings</h2>

  <script>
    var xhr = new XMLHttpRequest();
    function send_bright() {
      xhr.open("GET", "/set?bright=" + document.getElementById("brightness").value, true);
      xhr.send();
    }

    function send_speed() {
      xhr.open("GET", "/set?speed=" + document.getElementById("speed").value, true);
      xhr.send();
    }

    function send_cycle_time() {
      xhr.open("GET", "/set?cycle=" + document.getElementById("cycle_time").value, true);
      xhr.send();
    }

    function send_on_off(){
      xhr.open("GET", "/set?on_sched=" + document.getElementById("timeschedule").value, true);
      xhr.send();
    }
  
    function send_fade_in(){
      xhr.open("GET", "/set?fadein=" + document.getElementById("fadein").value, true);
      xhr.send();
    }

    function send_fade_out(){
      xhr.open("GET", "/set?fadeout=" + document.getElementById("fadeout").value, true);
      xhr.send();
    }

    function next_() {
      xhr.open("GET", "/anim?d=next", true);
      xhr.responseType = 'text';

      xhr.onload = function () {
        if (xhr.readyState === xhr.DONE) {
          if (xhr.status === 200) {
            console.log(xhr.response);
            console.log(xhr.responseText);
            get_response(xhr.responseText);
          }
        }
      }
      xhr.send();
    }

    function previous_() {
      xhr.open("GET", "/anim?d=prev", true);
      xhr.onload = function () {
        if (xhr.readyState === xhr.DONE) {
          if (xhr.status === 200) {
            console.log(xhr.response);
            console.log(xhr.responseText);
            get_response(xhr.responseText);
          }
        }
      }
      xhr.send();
    }

    function get_response(h_response) {
      if (h_response.includes('anim=')) {
        h_response = h_response.replace('anim=', '');
        document.getElementById("anim_mode").value = h_response;
      }
    }

    function save_time() {
      if (document.getElementById("ontime").value === "") {
        alert("Please, fill in the time to start!");
      }
      else if (document.getElementById("offtime").value === "") {
        alert("Please, fill in the time to shutdown!");
      }
      else {
        xhr.open("GET", "/time?on=" + document.getElementById("ontime").value + "&off=" + document.getElementById("offtime").value, true);
        xhr.send();
        //alert("you're good!");
      }

    }
  </script>

  <div class="slidecontainer">
    <form action="/" method="get"></form>
    <input type="range" name="Bright" min="0" max="255" value=%XPRT0% class="slider" id="brightness"
      onmouseup=send_bright()>


    </form>
    <label for="Bright">Brightness</label>
  </div>

  <div class="slidecontainer">
    <input type="range" name="Speed" min="1" max="100" value=%XPRT1% class="slider" id="speed" onmouseup=send_speed()>
    <label for="Bright">Animation speed</label>
  </div>

  <div class="slidecontainer">
    <input type="range" name="Cycle" min="30" max="250" value=%XPRT2% class="slider" id="cycle_time" onmouseup=send_cycle_time()>
    <label for="Bright">Cycle time</label>
  </div>



  <h3>Animation settings</h3>
  <p>Current mode:</p>
  <div>
    <input type="text" id="anim_mode" name="fname" value=%XPRT5% disabled="disabled"><br>
  </div>
  <div>
    <button type="button" onclick=previous_()><</button>
        <button type="button" onclick=next_()>></button>


  </div>

  <h2>Time settings</h2>
  <div>
    <input type="checkbox" id="timeschedule" %XPRT6% onclick=send_on_off() name="Timeschedule" >
    <label for="timeschedule">On/off schedule</label>
  </div>
   
  <div>
    <input type="checkbox" id="fadein" %XPRT7% onclick=send_fade_in() name="Fadein">
    <label for="fadein">Fade in</label>
  </div>

  <div>
    <input type="checkbox" id="fadeout" %XPRT8% onclick=send_fade_out() name="Fadeout">
    <label for="fadeout">Fade out</label>
  </div>

  <div>
    <input type="time" id="ontime" name="Ontime" value=%XPRT3% required>
    <small>ON time</small>
  </div>

  <div>
    <input type="time" id="offtime" name="Offtime" value=%XPRT4% required>
    <small>OFF time</small>
  </div>
  
  <div>
      <select name="timezone_offset" id="timezone-offset" class="span5">
      <option value="-12:00">(GMT -12:00) Eniwetok, Kwajalein</option>
      <option value="-11:00">(GMT -11:00) Midway Island, Samoa</option>
      <option value="-10:00">(GMT -10:00) Hawaii</option>
      <option value="-09:50">(GMT -9:30) Taiohae</option>
      <option value="-09:00">(GMT -9:00) Alaska</option>
      <option value="-08:00">(GMT -8:00) Pacific Time (US &amp; Canada)</option>
      <option value="-07:00">(GMT -7:00) Mountain Time (US &amp; Canada)</option>
      <option value="-06:00">(GMT -6:00) Central Time (US &amp; Canada), Mexico City</option>
      <option value="-05:00">(GMT -5:00) Eastern Time (US &amp; Canada), Bogota, Lima</option>
      <option value="-04:50">(GMT -4:30) Caracas</option>
      <option value="-04:00">(GMT -4:00) Atlantic Time (Canada), Caracas, La Paz</option>
      <option value="-03:50">(GMT -3:30) Newfoundland</option>
      <option value="-03:00">(GMT -3:00) Brazil, Buenos Aires, Georgetown</option>
      <option value="-02:00">(GMT -2:00) Mid-Atlantic</option>
      <option value="-01:00">(GMT -1:00) Azores, Cape Verde Islands</option>
      <option value="+00:00" selected="selected">(GMT) Western Europe Time, London, Lisbon, Casablanca</option>
      <option value="+01:00">(GMT +1:00) Brussels, Copenhagen, Madrid, Paris</option>
      <option value="+02:00">(GMT +2:00) Kaliningrad, South Africa</option>
      <option value="+03:00">(GMT +3:00) Baghdad, Riyadh, Moscow, St. Petersburg</option>
      <option value="+03:50">(GMT +3:30) Tehran</option>
      <option value="+04:00">(GMT +4:00) Abu Dhabi, Muscat, Baku, Tbilisi</option>
      <option value="+04:50">(GMT +4:30) Kabul</option>
      <option value="+05:00">(GMT +5:00) Ekaterinburg, Islamabad, Karachi, Tashkent</option>
      <option value="+05:50">(GMT +5:30) Bombay, Calcutta, Madras, New Delhi</option>
      <option value="+05:75">(GMT +5:45) Kathmandu, Pokhara</option>
      <option value="+06:00">(GMT +6:00) Almaty, Dhaka, Colombo</option>
      <option value="+06:50">(GMT +6:30) Yangon, Mandalay</option>
      <option value="+07:00">(GMT +7:00) Bangkok, Hanoi, Jakarta</option>
      <option value="+08:00">(GMT +8:00) Beijing, Perth, Singapore, Hong Kong</option>
      <option value="+08:75">(GMT +8:45) Eucla</option>
      <option value="+09:00">(GMT +9:00) Tokyo, Seoul, Osaka, Sapporo, Yakutsk</option>
      <option value="+09:50">(GMT +9:30) Adelaide, Darwin</option>
      <option value="+10:00">(GMT +10:00) Eastern Australia, Guam, Vladivostok</option>
      <option value="+10:50">(GMT +10:30) Lord Howe Island</option>
      <option value="+11:00">(GMT +11:00) Magadan, Solomon Islands, New Caledonia</option>
      <option value="+11:50">(GMT +11:30) Norfolk Island</option>
      <option value="+12:00">(GMT +12:00) Auckland, Wellington, Fiji, Kamchatka</option>
      <option value="+12:75">(GMT +12:45) Chatham Islands</option>
      <option value="+13:00">(GMT +13:00) Apia, Nukualofa</option>
      <option value="+14:00">(GMT +14:00) Line Islands, Tokelau</option>
    </select>
    <label for="timezone_offset">Timezone</label>
</div>
  <div>
    <button type="button" onclick=save_time()>Save time settings</button>
  </div>
  
  

  <h2>Other settings</h2>
  <div>
    <button type="button" onclick="alert('Will do!')">Reset WiFi settings</button>
  </div>

</body>

</html>

)rawliteral";

String processor(const String& var){
  //Serial.println(var);
if(var == "XPRT0"){
    String exif = "\""+String(ext_bright)+"\"";
    return exif;
  }
if(var == "XPRT1"){
    String exif = "\""+String(ext_speed)+"\"";
    return exif;
  }
if(var == "XPRT2"){
    String exif = "\""+String(ext_cycle)+"\"";
    return exif;
  }

if(var == "XPRT3"){
    int h, m;
    h=(time_on-time_on%100)/100;
    m=time_on%100;
    char buffer[10];
    sprintf(buffer, "\"%02d:%02d\"", h, m);
    return buffer;
  }

if(var == "XPRT4"){
    int h, m;
    h=(time_off-time_off%100)/100;
    m=time_off%100;
    char buffer[10];
    sprintf(buffer, "\"%02d:%02d\"", h, m);
    return buffer;
  }  
  if(var == "XPRT5"){
    return actual_anim;
  } 
    if(var == "XPRT6"){
    if(time_schedule==1){
    return "checked";
    }else{
    return "";
    }
  } 
      if(var == "XPRT7"){
    if(time_fadein==1){
    return "checked";
    }else{
    return "";
    }
  }
      if(var == "XPRT8"){
    if(time_fadeout==1){
    return "checked";
    }else{
    return "";
    }
  }
  
  return String();
}
