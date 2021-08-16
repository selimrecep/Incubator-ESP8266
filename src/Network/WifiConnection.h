#ifndef WIFI_CONN_H
#define WIFI_CONN_H
#include "AsyncDelay.h"
#include <vector>
#include <string>

constexpr int MAX_WIFI_SSID_LENGTH = 32;
constexpr int MAX_WIFI_PASSWORD_LENGTH = 32;
constexpr int MAX_WIFI_CREDENTIAL_LIST = 5;

struct WifiCredential
{
  std::string ssid;
  std::string password;
};

enum WifiCredentialsAddError
{
  success,
  tooManyWifiCredentials,
  tooLongSSID,
  tooLongPass
};

class WifiConnection
{
public:
  WifiConnection();
  void addCredentials();
  WifiCredentialsAddError addWifiCredential(WifiCredential credential);
  bool checkWifiAndConnect();
  bool isConnected();
  size_t getCredentialsCount();

private:
  std::vector<WifiCredential> wifiCredentialList;
  size_t credentialsCount = 0;
  size_t currentCredentialsIndex = 0;
  int connectionAttemptCount = 0;
  AsyncDelay wifiTimeoutDelay;
  bool isConnecting = 0;
};

#endif