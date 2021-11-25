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



const char index_html[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html>
<meta name="viewport" content="width=device-width, initial-scale=1.0">

<head>
  <title>WS2811 Configuration</title>

  <style type="text/css" rel="stylesheet">
    body {
      font-family: Arial, Helvetica, sans-serif;
      background-image: linear-gradient(to bottom, rgb(100, 100, 100), rgb(29, 29, 29));
      padding: 0 2%;
      width: 45%;

      margin: auto;
      position: center;

    }

    :root {}

    .mainframe {

      border-style: solid;
      border-width: 1px;
      background-image: linear-gradient(to bottom, rgb(7, 7, 7), rgb(218, 218, 218));

      margin: auto;
      position: center;
    }

    .header_bar {
      color: rgba(172, 172, 172, 0.842);
      background-color: rgba(8, 8, 8, 0.479);
      /* display: flex; */
      width: 100%;
      justify-content: center;
      font-size: 80%;
      text-align: center;
      margin: auto;
    }

    .led_settings {
      display: grid;
      grid-template-rows: 8vh 5vh 2vh 5vh;
      text-align: center;
      border-style: solid;
      border-width: 1px;
      width: 90%;
      position: relative;
      margin-left: auto;
      margin-right: auto;
    }

    .anim_settings {

      border-style: solid;
      border-width: 1px;
      width: 90%;
      height: 18vh;
      position: relative;
      margin-left: auto;
      margin-right: auto;
    }

    .change_buttons {
      justify-content: center;
      display: grid;
      height: 3vh;
      grid-template-columns: 20vw 20vw;
      grid-template-rows: 2vh 2vh;
    }

    .time_settings {
      border-style: solid;
      border-width: 1px;
      width: 90%;
      position: relative;
      margin-left: auto;
      margin-right: auto;
    }

    .on_off {
      width: 80%;
      margin: auto;
      display: grid;
      /* height: 3vh; */
      grid-template-columns: 16vw 16vw;
      /* flex-wrap: nowrap; */
      /* justify-content: center;*/
    }

    .change_buttons {
      display: grid;
      height: 3vh;
      grid-template-columns: 40% 40%;
      grid-template-rows: 3vh 3vh;
    }

    .p_button {
      width: 100%;
    }

    .f_label {
      font-size: 2vw;
    }

    .f_timezone {
      text-align: center;
    }

    .other_stuff {
      border-style: solid;
      border-width: 1px;
      width: 90%;
      /* height: 17vh; */
      /* position: relative; */
      margin-left: auto;
      margin-right: auto;
      text-align: center;
      padding: 1px;
    }
  </style>

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

    function send_on_off() {
      xhr.open("GET", "/set?on_sched=" + document.getElementById("timeschedule").value, true);
      xhr.send();
    }

    function send_fade_in() {
      xhr.open("GET", "/set?fadein=" + document.getElementById("fadein").value, true);
      xhr.send();
    }

    function send_fade_out() {
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

    function send_timezone() {
      xhr.open("GET", "/set?timezone=" + document.getElementById("timezone-offset").value, true);
      xhr.send();
    }

    function delete_credentials() {
      if (window.confirm("Are you sure?You know, if you delete my credentials I won't remember them later...")) {
        xhr.open("GET", "/reset", true);
        xhr.send();
      }

    }
  </script>
</head>

<body>
  <div class="mainframe">
    <div class="header_bar">
      <h1>WS2811 CONFIGURATION</h1>
    </div>
    <div class="led_settings">
      <h2>LED settings</h2>



      <div class="slidecontainer">
        <label for="Bright">Brightness</label><br>
        <input type="range" style="width: 80%;" name="Bright" min="0" max="255" value=%XPRT0% class="slider"
          id="brightness" onmouseup=send_bright()>

      </div><br>

      <div class="slidecontainer">
        <label for="Bright">Animation speed</label><br>
        <input type="range" style="width: 80%;" name="Speed" min="1" max="100" value=%XPRT1% class="slider" id="speed"
          onmouseup=send_speed()>

      </div><br>

      <div class="slidecontainer">
        <label for="Bright">Cycle period</label><br>
        <input type="range" style="width: 80%;;" name="Cycle" min="30" max="250" value=%XPRT2% class="slider"
          id="cycle_time" onmouseup=send_cycle_time()>

      </div>
    </div>

    <div class="anim_settings">
      <h3 style="font-size: 100%; text-align: center;">Animation mode</h3>
      <div>
        <input type="text"
          style="width: 79%; font-family: fantasy; text-align: center;display: block;margin-left: auto; margin-right: auto;"
          id="anim_mode" name="fname" value=%XPRT5% disabled="disabled">
      </div>
      <div class="change_buttons">
        <div>
          <button class="p_button" type="button" onclick=previous_()>&#11013;</button>
        </div>
        <div>
          <button class="p_button" type="button" onclick=next_()>&#10145;</button>
        </div>
        <div>
          <input type="checkbox" id="fadein" %XPRT7% onclick=send_fade_in() name="Fadein">
          <label class="f_label" for="fadein">Fade in</label>
        </div>

        <div>
          <input type="checkbox" id="fadeout" %XPRT8% onclick=send_fade_out() name="Fadeout">
          <label class="f_label" for="fadeout">Fade out</label>
        </div>
      </div>
    </div>


    <div class="time_settings">
      <h2 style="font-size: 100%;text-align: center;">Time settings</h2>

      <div style="font-size: 2vw; text-align: center;">
        <input type="checkbox" id="timeschedule" %XPRT6% onclick=send_on_off() name="Timeschedule">
        <label for="timeschedule">On/off schedule</label>
      </div>

      <div class="on_off">

        <div>
          <input type="time" id="ontime" name="Ontime" value=%XPRT3% required>
          <small style="font-size: 1.4vw;">&#128339 ON</small>
        </div>

        <div>
          <input type="time" id="offtime" name="Offtime" value=%XPRT4% required>
          <small style="font-size: 1.4vw;">&#128339 OFF</small>
        </div>

      </div>


      <div class="f_timezone">
        <div>
          <label for="timezone_offset">Timezone</label><br>
        </div>
        <select name="timezone_offset" id="timezone-offset" class="timezone_sel" style="width: 80%;;"
          onchange="send_timezone()">
          <option value="-12" %h-12%>(GMT -12:00) Eniwetok, Kwajalein</option>
          <option value="-11" %h-11%>(GMT -11:00) Midway Island, Samoa</option>
          <option value="-10" %h-10%>(GMT -10:00) Hawaii</option>
          <option value="-09" %h-9%>(GMT -9:00) Alaska</option>
          <option value="-08" %h-8%>(GMT -8:00) Pacific Time (US &amp; Canada)</option>
          <option value="-07" %h-7%>(GMT -7:00) Mountain Time (US &amp; Canada)</option>
          <option value="-06" %h-6%>(GMT -6:00) Central Time (US &amp; Canada), Mexico City</option>
          <option value="-05" %h-5%>(GMT -5:00) Eastern Time (US &amp; Canada), Bogota, Lima</option>
          <option value="-04" %h-4%>(GMT -4:00) Atlantic Time (Canada), Caracas, La Paz</option>
          <option value="-03" %h-3%>(GMT -3:00) Brazil, Buenos Aires, Georgetown</option>
          <option value="-02" %h-2%>(GMT -2:00) Mid-Atlantic</option>
          <option value="-01" %h-1%>(GMT -1:00) Azores, Cape Verde Islands</option>
          <option value="00" %h0%>(GMT) Western Europe Time, London, Lisbon, Casablanca</option>
          <option value="+01" %h+1%>(GMT +1:00) Brussels, Copenhagen, Madrid, Paris</option>
          <option value="+02" %h+2%>(GMT +2:00) Kaliningrad, South Africa</option>
          <option value="+03" %h+3%>(GMT +3:00) Baghdad, Riyadh, Moscow, St. Petersburg</option>
          <option value="+04" %h+4%>(GMT +4:00) Abu Dhabi, Muscat, Baku, Tbilisi</option>
          <option value="+05" %h+5%>(GMT +5:00) Ekaterinburg, Islamabad, Karachi, Tashkent</option>
          <option value="+06" %h+6%>(GMT +6:00) Almaty, Dhaka, Colombo</option>
          <option value="+07" %h+7%>(GMT +7:00) Bangkok, Hanoi, Jakarta</option>
          <option value="+08" %h+8%>(GMT +8:00) Beijing, Perth, Singapore, Hong Kong</option>
          <option value="+09" %h+9%>(GMT +9:00) Tokyo, Seoul, Osaka, Sapporo, Yakutsk</option>
          <option value="+10" %h+10%>(GMT +10:00) Eastern Australia, Guam, Vladivostok</option>
          <option value="+11" %h+11%>(GMT +11:00) Magadan, Solomon Islands, New Caledonia</option>
          <option value="+12" %h+12%>(GMT +12:00) Auckland, Wellington, Fiji, Kamchatka</option>
          <option value="+13" %h+13%>(GMT +13:00) Apia, Nukualofa</option>
          <option value="+14" %h+14%>(GMT +14:00) Line Islands, Tokelau</option>
        </select>

        <div>
          <button type="button" style="width: 80%;" onclick=save_time()>Save time settings</button>
        </div>
      </div>


    </div>

    <div class="other_stuff">
      <h2>Other settings</h2>
      <div>
        <button type="button" style="width: 80%;" onclick="delete_credentials()">Reset WiFi settings</button>
      </div>
    </div>
  </div>

</body>

</html>

)rawliteral";


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

  
  if(var==tz_place){
    //Serial.println(tz_place);
    return "selected";
    }
  
  return String();
}
