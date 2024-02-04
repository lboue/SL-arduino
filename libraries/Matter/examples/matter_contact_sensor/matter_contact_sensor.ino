/*
   Matter contact sensor example

   The example shows how to create an contact sensor with the Arduino Matter API.

   The example creates a Matter contact sensor device and publishes contact information through it.
   The contact changes every 10 seconds.
   The device has to be commissioned to a Matter hub first.

   Compatible boards:
   - SparkFun Thing Plus MGM240P
   - xG24 Explorer Kit

   Author: Tamas Jozsi (Silicon Labs)
 */
#include <Matter.h>
#include <MatterContact.h>

MatterContact matter_contact_sensor;

void setup()
{
  Serial.begin(115200);
  Matter.begin();
  matter_contact_sensor.begin();

  Serial.println("Matter contact sensor");

  if (!Matter.isDeviceCommissioned()) {
    Serial.println("Matter device is not commissioned");
    Serial.println("Commission it to your Matter hub with the manual pairing code or QR code");
    Serial.printf("Manual pairing code: %s\n", Matter.getManualPairingCode().c_str());
    Serial.printf("QR code URL: %s\n", Matter.getOnboardingQRCodeUrl().c_str());
  }
  while (!Matter.isDeviceCommissioned()) {
    delay(200);
  }

  if (!Matter.isDeviceConnected()) {
    Serial.println("Waiting for network connection...");
  }
  while (!Matter.isDeviceConnected()) {
    delay(200);
  }
  Serial.println("Device connected");
}

void loop()
{
  static uint32_t last_action = 0;
  // Wait 10 seconds
  if ((last_action + 10000) < millis()) {
    last_action = millis();
    // Toggle the state of the contact sensor
    bool new_state = !matter_contact_sensor.get_contact();
    // Publish the contact value - you can also use 'matter_contact_sensor.set_contact(new_state)'
    matter_contact_sensor = new_state;
    Serial.printf("Current contact state: %s\n", new_state ? "close" : "open");
  }
}
