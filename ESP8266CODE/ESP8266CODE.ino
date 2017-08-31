#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);
#define LED LED_BUILTIN;

const char* ssid = "ESP_IOT";
const char* password = "123456789";
unsigned char status_led = 0;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println("");
  lcd.begin();
  delay(10);


  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  // Connect to WiFi network
  lcd.clear();
  lcd.print("Connecting to ");
  lcd.setCursor(0, 1);
  lcd.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

  }
  lcd.setCursor(0, 0);
  lcd.println("WiFi connected");

  // Start the server
  server.begin();
  lcd.setCursor(0, 0);
  lcd.println("Server started");

  // Print the IP address
  lcd.clear();
  lcd.print(" ");
  lcd.println(WiFi.localIP());
  lcd.setCursor(0, 1);
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  lcd.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  lcd.setCursor(0, 1);
  lcd.print(req);
  client.flush();

  // Match the request
  int i = 0;
  int val = 0;
  //////////////////////////WETBLUE/////////////////////////
  if (req.indexOf("/wetblue/1") != -1) {
    val = 1;
    Serial.print("lp01");
  } else if (req.indexOf("/wetblue/2") != -1) {
    val = 2;
    Serial.print("lp03");
  } else if (req.indexOf("/wetblue/3") != -1) {
    val = 3;
    Serial.print("lp05");
  } else if (req.indexOf("/wetblue/4") != -1) {
    val = 4;
    Serial.print("lp07");
  } else if (req.indexOf("/wetblue/5") != -1) {
    val = 5;
    Serial.print("lp09");
  } else if (req.indexOf("/wetblue/6") != -1) {
    val = 6;
    Serial.print("lp11");
  } else if (req.indexOf("/wetblue/7") != -1) {
    val = 7;
    Serial.print("lp13");
  } else if (req.indexOf("/wetblue/8") != -1) {
    val = 8;
    Serial.print("lp15");
  } else if (req.indexOf("/wetblue/9") != -1) {
    val = 9;
    Serial.print("lp17");
  } else if (req.indexOf("/wetblue/A") != -1) {
    val = 10;
    Serial.print("lp19");
  } else if (req.indexOf("/wetblue/PB7") != -1) {
    val = 11;
    Serial.print("ep27");
  } else if (req.indexOf("/wetblue/PB9") != -1) {
    val = 12;
    Serial.print("ep29");
  } else
    //////////////////////////Crush////////////////////////////

    if (req.indexOf("/crush/1") != -1) {
      val = 1;
      Serial.print("lp02");
    } else if (req.indexOf("/crush/2") != -1) {
      val = 2;
      Serial.print("lp04");
    } else if (req.indexOf("/crush/3") != -1) {
      val = 3;
      Serial.print("lp06");
    } else if (req.indexOf("/crush/4") != -1) {
      val = 4;
      Serial.print("lp08");
    } else if (req.indexOf("/crush/5") != -1) {
      val = 5;
      Serial.print("lp10");
    } else if (req.indexOf("/crush/6") != -1) {
      val = 6;
      Serial.print("lp12");
    } else if (req.indexOf("/crush/7") != -1) {
      val = 7;
      Serial.print("lp14");
    } else if (req.indexOf("/crush/8") != -1) {
      val = 8;
      Serial.print("lp16");
    } else if (req.indexOf("/crush/9") != -1) {
      val = 9;
      Serial.print("lp18");
    } else if (req.indexOf("/crush/A") != -1) {
      val = 10;
      Serial.print("lp28");
    } else if (req.indexOf("/crush/B") != -1) {
      val = 11;
      Serial.print("lp32");
    } else if (req.indexOf("/crush/C") != -1) {
      val = 12;
      Serial.print("lp38");
    } else if (req.indexOf("/crush/D") != -1) {
      val = 13;
      Serial.print("lp41");
    } else  if (req.indexOf("/crush/P2") != -1) {
      val = 13;
      Serial.print("ep02");
    } else if (req.indexOf("/crush/PB5") != -1) {
      val = 13;
      Serial.print("ep25");
    } else
      /////////////////////////Finishing//////////////////////////
      if (req.indexOf("/finishing/1") != -1) {
        val = 1;
        Serial.print("lp21");
      } else  if (req.indexOf("/finishing/2") != -1) {
        val = 2;
        Serial.print("lp23");
      } else if (req.indexOf("/finishing/3") != -1) {
        val = 3;
        Serial.print("lp25");
      } else if (req.indexOf("/finishing/4") != -1) {
        val = 4;
        Serial.print("lp27");
      } else if (req.indexOf("/finishing/5") != -1) {
        val = 5;
        Serial.print("lp29");
      } else if (req.indexOf("/finishing/6") != -1) {
        val = 6;
        Serial.print("lp31");
      } else if (req.indexOf("/finishing/7") != -1) {
        val = 7;
        Serial.print("lp33");
      } else if (req.indexOf("/finishing/8") != -1) {
        val = 8;
        Serial.print("lp35");
      } else if (req.indexOf("/finishing/9") != -1) {
        val = 9;
        Serial.print("lp37");
      } else if (req.indexOf("/finishing/A") != -1) {
        val = 10;
        Serial.print("lp39");
      } else if (req.indexOf("/finishing/B") != -1) {
        val = 11;
        Serial.print("lp40");
      }else  if (req.indexOf("/finishing/P4") != -1) {
    val = 10;
    Serial.print("ep04");
  } else  if (req.indexOf("/finishing/P6") != -1) {
    val = 10;
    Serial.print("ep06");
  } else  if (req.indexOf("/finishing/PA8") != -1) {
    val = 10;
    Serial.print("ep18");
  } else
    ///////////////////////////Retanning////////////////////////
    if (req.indexOf("/retan/8") != -1) {
      val = 10;
      Serial.print("ep33");
    } else  if (req.indexOf("/retan/1") != -1) {
      val = 10;
      Serial.print("ep15");
    } else  if (req.indexOf("/retan/2") != -1) {
      val = 10;
      Serial.print("ep17");
    } else  if (req.indexOf("/retan/3") != -1) {
      val = 10;
      Serial.print("ep19");
    } else  if (req.indexOf("/retan/4") != -1) {
      val = 10;
      Serial.print("ep21");
    } else  if (req.indexOf("/retan/5") != -1) {
      val = 10;
      Serial.print("ep23");
    } else  if (req.indexOf("/retan/6") != -1) {
      val = 10;
      Serial.print("ep28");
    } else  if (req.indexOf("/retan/7") != -1) {
      val = 10;
      Serial.print("ep31");
    }
  ///////////////////////////End APP//////////////////////////
    else {
      lcd.setCursor(0, 1);
      lcd.println("invalid request");
      client.stop();
      return;
    }

  // Set GPIO2 according to the request
  digitalWrite(LED_BUILTIN, i);

  client.flush();

  // Prepare the response
  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  web += "<html>\r\n";
  web += "<body>\r\n";
  web += "<h1>ECCO Light Control</h1>\r\n";
  web += "<p></p>";
  web += "<p>\r\n"; 
  web += "<p>Please Contact Maintenance Department to Get appication</p>";
  web += "</body>\r\n";
  web += "</html>\r\n";
  client.print(web);
  delay(50);

  

  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed


}

