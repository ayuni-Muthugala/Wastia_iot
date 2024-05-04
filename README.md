# Wastia_IOT

### Replace your wifi name and password to below varibales.

#define WIFI_SSID "Wifi_Name" 
#define WIFI_PASSWORD "Wifi_Password" 

### Define ultrasonic pins here.

#define TRIG_PIN D1
#define ECHO_PIN D2

### Define battry measurement analog pin here.

#define BATTERY_PIN A0 // Analog pin to read battery voltage

### If code runs but database didn't update follow below steps.

Go to https://www.grc.com/fingerprints.htm
Enter "test.firebaseio.com"
Record the fingerprint (e.g. it is old one 6F:D0:9A:52:C0:E9:E4:CD:A0:D3:02:A4:B7:A1:92:38:2D:CA:2F:26)
OpenC:\Users<User>\Documents\Arduino\libraries\firebase-arduino-\src\FirebaseHttpClient.h
Replace value of kFirebaseFingerprint with the fingerprint Recompile

### Library files add here.

![image](https://github.com/Hashx-Developments/Wastia_IOT/assets/37227365/d6bdd76c-e7cb-4897-b50f-ec6bdac4660b)
