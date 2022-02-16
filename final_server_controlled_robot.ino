#include <ESP8266WiFi.h>
 
const char* ssid = "Prakhar";
const char* password = "750510847";
 
; // 
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(0, LOW);
  digitalWrite(13, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
 
  if (request.indexOf("Forwardon") > 0)  {
    digitalWrite(5, HIGH);
     digitalWrite(4, HIGH);
   
  }
  if (request.indexOf("/Forwardoff") >0)  {
    digitalWrite(5, LOW);
   digitalWrite(4, LOW);
  }

   if (request.indexOf("/Backwardon") > 0)  {
    digitalWrite(12, HIGH);
     digitalWrite(13, HIGH);
   
  }
  if (request.indexOf("/Backwardoff") >0)  {
    digitalWrite(12, LOW);
   digitalWrite(13, LOW);
   
  }
    if (request.indexOf("/Righton") >0)  {
    digitalWrite(5, HIGH);
   
  }
  if (request.indexOf("/Rightoff") > 0)  {
    digitalWrite(5, LOW);
   
  }
   if (request.indexOf("/Lefton") > 0)  {
    digitalWrite(4, HIGH);
   
  }
  if (request.indexOf("/Leftoff") > 0)  {
    digitalWrite(4, LOW);
   
  }
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
  client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
 client.println("</head>");
  client.println("<body bgcolor = \"#f7e6ec\">"); 
  client.println("<hr/><hr>");
  client.println("<h4><center> robot control pannel </center></h4>");
  client.println("<hr/><hr>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("forward");
  client.println("<a href=\"/Forwardon\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/Forwardoff\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>");   
  client.println("<br><br>");
   client.println("<center>");
   client.println("backward");
  client.println("<a href=\"/Backwardon\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/Backwardoff\"\"><button>Turn Off </button></a><br />");  
client.println("</center>"); 
  client.println("<br><br>");
    client.println("<center>");
   client.println("left");
  client.println("<a href=\"/Righton\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/Rightoff\"\"><button>Turn Off </button></a><br />");  
client.println("</center>"); 
  client.println("<br><br>");
   client.println("<center>");
   client.println("right");
  client.println("<a href=\"/Lefton\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/Leftoff\"\"><button>Turn Off </button></a><br />");  
client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");
  client.println("<table border=\"5\">");
 client.println("<tr>");
  if (digitalRead(5))
         { 
           client.print("<td>robot is moving forward</td>");
        
         }
          else
          {
            client.print("<td>robot stopped</td>");
      
        }
     
        client.println("<br />");
             
         if (digitalRead(4))
          { 
           client.print("<td>robot is moving backward</td>");

         }
          else
          {

            client.print("<td>robot stopped</td>");

          }
          client.println("</tr>");


          client.println("<tr>");

          if (digitalRead(12))

          { 
           client.print("<td>robot is turning to left</td>");

          }

          else

          {
            client.print("<td>robot is stable</td>");
          }


          if (digitalRead(13))


          { 


           client.print("<td>robot is turning to right</td>");

          }


          else


          {


            client.print("<td>robot is stable </td>");


          }

          client.println("</tr>");


          client.println("</table>");

          client.println("</center>");
             client.println("</tbody> </table> <p style=\"text-align: center;\">Turn all: <a href=\"/Emergency==ON\">ON</a> <a href=\"/Emergeny=OFF\">OFF</a> <br> </p> <form style= \"width:450px; margin-left: auto; margin-right: auto; text-align: center;\" method=\"GET\"> Refresh: <input style=\"width:50px;\" title=\"Please enter a number\" type=\"number\" name=\"refresh\"/> <input type=\"submit\" value=\"SET\" /> </form> <br> <hr /> <h5 style=\"text-align: center;\"><a title=\"Made by Prakhar Awasthi\" href=\"https://goo.gl/yP90fX\" target=\"_blank\">Made By Prakhar Awasthi!</a></h5> </html>");

  client.println("</html>"); 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
