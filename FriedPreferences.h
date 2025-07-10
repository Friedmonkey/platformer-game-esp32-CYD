
#ifndef FRIEDPREFERENCES_H
#define FRIEDPREFERENCES_H

#include <Preferences.h>

#define ESP_DRD_USE_EEPROM true
#define ESP_DRD_USE_SPIFFS false
#include <ESP_DoubleResetDetector.h>

class FriedPreferences {
public:
  // Initialize with namespace and DRD timeout (seconds), returns Preferences&
  static Preferences& init(const char* namespaceName, unsigned int drdTimeoutSeconds = 10) {
    ns = namespaceName;

    drd = new DoubleResetDetector(drdTimeoutSeconds, 0);
    drdDetected = drd->detectDoubleReset();

    prefs.begin(ns, false);

    if (drdDetected) {
      drd->stop();
      prefs.clear();
    }

    return prefs;
  }

  static void loop()
  {
    drd->loop();
  }
  // Check if double reset happened (true only once per init)
  static bool isDoubleReset() {
    return drdDetected;
  }

private:
  static Preferences prefs;
  static DoubleResetDetector* drd;
  static bool drdDetected;
  static const char* ns;
};

Preferences FriedPreferences::prefs;
DoubleResetDetector* FriedPreferences::drd = nullptr;
bool FriedPreferences::drdDetected = false;
const char* FriedPreferences::ns = nullptr;

#endif
