int bieta=145;



const char index_html[] PROGMEM = R"rawliteral(

<meta name="viewport" content="width=device-width, initial-scale=1.0">
<!DOCTYPE html>
<html>
<body>

<h1>WS2811 Configuration</h1>
<h2>LED settings</h2>



<div class="slidecontainer">
  <form action="/" method="get"></form>
    <input type="range" name="Bright" min="0"  max="255" value=%XPRT0% class="slider" id="brightness" onmouseup=send_bright()>
    <script>
    var xhr = new XMLHttpRequest();
    function send_bright() {
      
      xhr.open("GET", "/set?bright="+document.getElementById("brightness").value, true);      
      xhr.send();
    }
  </script>
      </form>
    <label for="Bright">Brightness</label>
  </div>
  
<div class="slidecontainer">
    <input type="range" name="Speed" min="1" max="100" value="50" class="slider" id="speed">
    <label for="Bright">Animation speed</label>
  </div>

  <div>
    <input type="checkbox" id="fadein" name="Fadein">
    <label for="fadein">Fade in</label>
  </div>

  <div>
    <input type="checkbox" id="fadeout" name="Fadeout">
    <label for="fadeout">Fade out</label>
  </div>

  <h3>Animation settings</h3>
  

  <h2>Time settings</h2>
  <div>
    <input type="checkbox" id="timeschedule" name="Timeschedule">
    <label for="timeschedule">On/off schedule</label>
  </div>
  
  <div>
    <input type="time" id="ontime" name="Ontime" min="09:00" max="18:00" required>
<small>ON time</small>
  </div>

  <div>
    <input type="time" id="offtime" name="Offtime" min="09:00" max="18:00" required>
<small>OFF time</small>
  </div>

  <h2>WiFi settings</h2>
  <button type="button" onclick="alert('Will do!')">Reset settings</button>

</body>
</html>

)rawliteral";

String processor(const String& var){
  //Serial.println(var);
  if(var == "XPRT0"){
    String exif = "\""+String(bieta)+"\"";
    return exif;
  }
  return String();
}
