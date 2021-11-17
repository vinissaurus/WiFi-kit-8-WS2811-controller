int ext_bright = 0;
int ext_speed = 0;
int ext_cycle = 0;
int current_mode = 0;
int time_on = 0;
int time_off = 0;
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
    <input type="range" name="Cycle" min="1" max="100" value=%XPRT2% class="slider" id="cycle_time">
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
    <input type="checkbox" id="timeschedule" name="Timeschedule">
    <label for="timeschedule">On/off schedule</label>
  </div>

  <div>
    <input type="checkbox" id="fadein" name="Fadein">
    <label for="fadein">Fade in</label>
  </div>

  <div>
    <input type="checkbox" id="fadeout" name="Fadeout">
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
  
  return String();
}
