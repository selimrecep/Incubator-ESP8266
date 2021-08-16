#include "WifiConnection.h"
#include "ESP8266Wifi.h"

#include <vector>

WifiConnection::WifiConnection()
{
  wifiCredentialList.resize(3);
};
void WifiConnection::addCredentials()
{

  WifiCredential wifi = {
      "selimrecep",
      "shockable4869"};
  WifiCredentialsAddError err = addWifiCredential(wifi);
  if (err == WifiCredentialsAddError::success)
  {
    //Serial.print("Added first network");
  }
  else
  {
    //Serial.println("Error!");
  }
  wifi = {
      "Galaxy A10s5103",
      "ezjg7988"};
  err = addWifiCredential(wifi);

  if (err == WifiCredentialsAddError::success)
  {
    //Serial.print("Added first network");
  }
  else
  {
    //Serial.println("Error!");
  }

  wifi = {
      "LAPTOP-PPDPEMCR 6680",
      ")86l84F6"};

  err = addWifiCredential(wifi);
  if (err == WifiCredentialsAddError::success)
  {
    //Serial.print("Added first network");
  }
  else
  {
    //Serial.println("Error!");
  }
}
size_t WifiConnection::getCredentialsCount()
{
  return credentialsCount;
}
WifiCredentialsAddError WifiConnection::addWifiCredential(WifiCredential credential)
{
  if (credentialsCount >= wifiCredentialList.size())
  {
    if (wifiCredentialList.size() + 1 > MAX_WIFI_CREDENTIAL_LIST)
    {
      return WifiCredentialsAddError::tooManyWifiCredentials;
    }
    wifiCredentialList.resize(credentialsCount + 1);
  }

  if (credential.ssid.size() > MAX_WIFI_SSID_LENGTH)
  {
    return WifiCredentialsAddError::tooLongSSID;
  }
  if (credential.password.size() > MAX_WIFI_PASSWORD_LENGTH)
  {
    return WifiCredentialsAddError::tooLongPass;
  }
  wifiCredentialList[credentialsCount++] = credential;
  return WifiCredentialsAddError::success;
}
bool WifiConnection::isConnected()
{
  return WiFi.status() == WL_CONNECTED;
}
bool WifiConnection::checkWifiAndConnect()
{

  if (WiFi.status() != WL_CONNECTED)
  {
    if (credentialsCount == 0)
    {
      return false;
    }
    if (!isConnecting)
    {
      isConnecting = 1;
      //Serial.println("Wifi hasn't connected. ");
      wl_status_t status = WiFi.begin(wifiCredentialList[currentCredentialsIndex].ssid.c_str(), wifiCredentialList[currentCredentialsIndex].password.c_str());
      wifiTimeoutDelay.start(10000, AsyncDelay::MILLIS);

      if (status == WL_CONNECTED)
      {
        //Serial.println("Wifi connected. ");
        isConnecting = 0;
      }
    }
    else
    {
      if (WiFi.status() != WL_CONNECTED && wifiTimeoutDelay.isExpired())
      {
        connectionAttemptCount++;
        if (connectionAttemptCount > 3)
        {
          currentCredentialsIndex++;
          if (currentCredentialsIndex > credentialsCount - 1)
            currentCredentialsIndex = 0;
        }
        //Serial.print("Wifi connection expired: ");
        //Serial.print(WiFi.status());
        isConnecting = 0;
      }
    }
  }
  else if (isConnecting)
  {

    //Serial.println("Wifi connected. ");
    isConnecting = 0;
    connectionAttemptCount = 0;
  }

  return isConnected();
}