//
//  ofxYahooWeather.h
//
//  Created by Ryo Hajika(imaginaryShort) on 1/15/14.
//
//  Work In Progress...
//  based on a library for Processing "YahooWeather"
//

#pragma once

#include "ofMain.h"

#define MILWAUKEE_WOEID 2451822
#define CHICAGO_WOEID 2379574
#define NEW_YORK_WOEID 2459115
#define LOS_ANGELES_WOEID 2442047
#define HOUSTON_WOEID 2424766
#define SAN_FRANSISCO_WOEID 2487956
#define PHILADELPHIA_WOEID 2471217
#define LONDON_WOEID 44418
#define PARIS_WOEID 615702
#define FAHRENHEIT 'f'
#define CELSIUS 'c'



class ofxYahooWeather {
    
    public:
        ofxYahooWeather();
        ~ofxYahooWeather();
    
        /*  basic functions */
        //targetWOEID : WOEID
        //temperatureUnit : 'f' or 'c' (Fahrenheit or Celsius)
        void setup(unsigned int targetWOEID, char temperatureUnit = 'c');
        void refresh();
    
        /*  change parameters   */
        void resetWOEID(unsigned int targetWOEID);
        void resetTempUnit(char temperatureUnit);
    
        /*  get values  */
        string getURL();
        float getLongtitude();
        float getLatitude();
        int getWindTemperature();
        float getWindSpeed();
        int getWindDirection();
        string getCityName();
        string getCountryName();
        string getRegionName();
        int getHumidity();
        float getVisibleDistance();
        float getPressure();
    
        /**
         * 0 = steady
         * 1 = rising
         * 2 = falling
         */
        int getRising();
        string getSunrise();
        string getSunset();
        int getTemperature();
        string getWeatherCondition();
        int getWeatherConditionCode();
        string getLastUpdated();        //returns last updated date by string
    
        int getTemperatureLowTomorrow();
        int getTemperatureHighTomorrow();
        string getWeatherConditionTomorrow();
        int getWeatherConditionCodeTomorrow();
        string getWeekdayTomorrow();    //output: "day, date"
    
        int getTemperatureLowDayAfterTomorrow();
        int getTemperatureHighDayAfterTomorrow();
        string getWeatherConditionDayAfterTomorrow();
        int getWeatherConditionCodeDayAfterTomorrow();
        string getWeekdayDayAfterTomorrow();
    
        //additions
        int getTemperatureLowThreeDaysLater();
        int getTemperatureHighThreeDaysLater();
        string getWeatherConditionThreeDaysLater();
        int getWeatherConditionCodeThreeDaysLater();
        string getWeekdayThreeDaysLater();
    
        int getTemperatureLowFourDaysLater();
        int getTemperatureHighFourDaysLater();
        string getWeatherConditionFourDaysLater();
        int getWeatherConditionCodeFourDaysLater();
        string getWeekdayFourDaysLater();
    
        string getTempUnit();
        string getDistanceUnit();
        string getPressureUnit();
        string getSpeedUnit();
        string getTitileOfWeatherInfo();    //like: Yahoo! Weather for Osaka-shi, JP
    
    private:
        unsigned int woeid;
        char tempUnit;
        string url;
    
        ofHttpResponse urlReceiving;
        string responseData;
        vector<string> dataContainer;
    
        Poco::XML::DOMParser parser;
        ::Poco::AutoPtr<Poco::XML::Document> pDoc;
        Poco::XML::Node* pNode;
        Poco::XML::Node* pParentNode;
    
        bool switchBoolean, switchBooleanHasAttributes;
    
};