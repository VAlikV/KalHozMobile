// function val(id){
//  var v = document.getElementById(id).value;
//  return v;
// }

function createXmlHttpObject(){
  if(window.XMLHttpRequest){
    xmlHttp = new XMLHttpRequest();
  }else{
    xmlHttp = new ActiveXObject('Microsoft.XMLHTTP');
  }
  return xmlHttp;
}

// function loadBlock(data) {
//   for (var key in data) {
//     if (document.getElementById(key)){
//       document.getElementById(key).value = Number(data[key])/100000;
//     }
//   }
// }

// ------------------------------------------------------------------------------------------------------ Загрузка

function load(){

  window.leftSlider = document.getElementById('l');
  window.rightSlider = document.getElementById('r');

  // Добавляем обработчики событий для слайдеров
  leftSlider.addEventListener('input', function(){
    sendSpeed()
  });
  rightSlider.addEventListener('input', function(){
    sendSpeed()
  });

  // var xmlHttp=createXmlHttpObject();
  // if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
  //   xmlHttp.open('GET','/configs.json',true);
  //   xmlHttp.responseType = "json";
  //   xmlHttp.onload = () => {
  //     console.log(xmlHttp.response);
  //     //data = JSON.parse(xmlHttp.response);
  //     loadBlock(xmlHttp.response);
  //   }
  //   xmlHttp.send()
  // }
}

// ------------------------------------------------------------------------------------------------------ Автообновление

// setInterval(WebRefresh,3000);

// function WebRefresh(){
//   var xml=createXmlHttpObject();
//   xml.responseType = "json";
//   xml.open('GET', '/Refresh', true);
//   xml.onreadystatechange = function() {
//     if (xml.readyState == 4 && xml.status == 200) {
//       //document.getElementById("test").value = xmlHttp.responseText;
//       //console.log(xml.responseText);
//       console.log(xml.response);
//       loadBlock(xml.response);
//     }
//   }
//   xml.send();
// }

// ------------------------------------------------------------------------------------------------------ Для слайдера



// ------------------------------------------------------------------------------------------------------

function sendSpeed(){
  // json_str = "{left: " + leftSlider.value + "," + "right: " + rightSlider.value + "}"
  server = "/speed?vel=" + leftSlider.value + "=" + rightSlider.value;
  send_request(server);
}

function send_request(server){
  request = new XMLHttpRequest();
  request.open("GET", server, true);
  request.send();
}
