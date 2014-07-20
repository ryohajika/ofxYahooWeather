//
//  ofxYahooWeather.cpp
//
//  Created by Ryo Hajika(imaginaryShort) on 1/15/14.
//
//  Work In Progress...
//  based on a library for Processing "YahooWeather"
//

#include "ofxYahooWeather.h"

//  constructor
ofxYahooWeather::ofxYahooWeather(){};
ofxYahooWeather::~ofxYahooWeather(){};

//  basic functions
void ofxYahooWeather::setup(unsigned int targetWOEID, char temperatureUnit)
{
    woeid = targetWOEID;
    tempUnit = temperatureUnit;
    url = "http://weather.yahooapis.com/forecastrss?w=" + ofToString(woeid) + "&u=" + ofToString(tempUnit);
	switchBooleanHasAttributes=false;
}

void ofxYahooWeather::refresh()
{
    urlReceiving = ofLoadURL(url);
    responseData = urlReceiving.data;
    
    if (dataContainer.size()) dataContainer.erase(dataContainer.begin(), dataContainer.end());
    
    try{
        parser.setFeature(Poco::XML::DOMParser::FEATURE_FILTER_WHITESPACE, false);
        pDoc = parser.parseString(responseData);
        
        Poco::XML::NodeIterator itr(pDoc, Poco::XML::NodeFilter::SHOW_ALL);
        pNode = itr.nextNode();
        
        while (pNode) {
            pParentNode = pNode->parentNode();
            while (0 != pParentNode) {
                pParentNode = pParentNode->parentNode();
            }
            
            //addition
            if (switchBoolean && !switchBooleanHasAttributes) {
                if(pNode->nodeValue().size() < 40) dataContainer.push_back(pNode->nodeValue());  //to avoid add huge value can't ignore
                switchBoolean = false;
            }
            
            if (pNode->nodeName() == "description") switchBoolean = true;                   //dataContainer.0
            else if (pNode->nodeName() == "lastBuildDate") switchBoolean = true;            //dataContainer.1
            else if (pNode->nodeName() == "yweather:location") switchBooleanHasAttributes = true;        //dataContainer.2(city),3(region),4(country)
            else if (pNode->nodeName() == "yweather:units") switchBooleanHasAttributes = true;           //dataContainer.5(temperature),6(distance),7(pressure),8(speed)
            else if (pNode->nodeName() == "yweather:wind") switchBooleanHasAttributes = true;            //dataContainer.9(chill),10(direction),11(speed)
            else if (pNode->nodeName() == "yweather:atmosphere") switchBooleanHasAttributes = true;      //dataContainer.12(humidity),13(visibility),14(pressure),15(rising)
            else if (pNode->nodeName() == "yweather:astronomy") switchBooleanHasAttributes = true;       //dataContainer.16(sunrise),17(sunset)
            else if (pNode->nodeName() == "geo:lat") switchBoolean = true;                  //dataContainer.18
            else if (pNode->nodeName() == "geo:long") switchBoolean = true;                 //dataContainer.19
            else if (pNode->nodeName() == "yweather:condition") switchBooleanHasAttributes = true;       //dataContainer.20(text),21(code),22(temp),23(date)
            else if (pNode->nodeName() == "yweather:forecast") switchBooleanHasAttributes = true;        //dataContainer.24(todayName),25(todayDate),26(todayLow),27(todayHigh),28(todayConditionText),29(conditionCode),+4days
            
            if (pNode->hasAttributes()) {
                for (unsigned long j = 0; j < pNode->attributes()->length(); j++) {
                    if (switchBooleanHasAttributes) dataContainer.push_back(pNode->attributes()->item(j)->nodeValue());
                }
                switchBooleanHasAttributes = false;

            }
            //////////
            
            pNode = itr.nextNode();
        }
        ofLogVerbose("Weather Data Updated!");
#ifdef TARGET_WIN32
        for (int j=1; j<dataContainer.size(); j++) {
            dataContainer[j-1]=dataContainer[j];
        }
#endif
    }
    catch(Poco::Exception &exc){
        ofLogNotice(ofToString(exc.displayText()));
    }
}

//  functions to change parameters
void ofxYahooWeather::resetWOEID(unsigned int targetWOEID)
{
    woeid = targetWOEID;
    url = "http://weather.yahooapis.com/forecastrss?w=" + ofToString(woeid) + "&u=" + ofToString(tempUnit);
}

void ofxYahooWeather::resetTempUnit(char temperatureUnit)
{
    tempUnit = temperatureUnit;
    url = "http://weather.yahooapis.com/forecastrss?w=" + ofToString(woeid) + "&u=" + ofToString(tempUnit);
}

//  functions to get values
string ofxYahooWeather::getURL()
{
    return url;
}

float ofxYahooWeather::getLongtitude()
{
    return ofToFloat(dataContainer.at(19));
}

float ofxYahooWeather::getLatitude()
{
    return ofToFloat(dataContainer.at(18));
}

int ofxYahooWeather::getWindTemperature()
{
    return ofToInt(dataContainer.at(9));
}

float ofxYahooWeather::getWindSpeed()
{
    return ofToFloat(dataContainer.at(11));
}

int ofxYahooWeather::getWindDirection()
{
    return ofToInt(dataContainer.at(10));
}

string ofxYahooWeather::getCityName()
{
    return dataContainer.at(2);
}

string ofxYahooWeather::getCountryName()
{
    return dataContainer.at(4);
}

string ofxYahooWeather::getRegionName()
{
    return dataContainer.at(3);
}

int ofxYahooWeather::getHumidity()
{
    return ofToInt(dataContainer.at(12));
}

float ofxYahooWeather::getVisibleDistance()
{
    return ofToFloat(dataContainer.at(13));
}

float ofxYahooWeather::getPressure()
{
    return ofToFloat(dataContainer.at(14));
}


int ofxYahooWeather::getRising()
{
    return ofToInt(dataContainer.at(15));
}

string ofxYahooWeather::getSunrise()
{
    return dataContainer.at(16);
}

string ofxYahooWeather::getSunset()
{
    return dataContainer.at(17);
}

int ofxYahooWeather::getTemperature()
{
    return ofToInt(dataContainer.at(22));
}

string ofxYahooWeather::getWeatherCondition()
{
    return dataContainer.at(20);
}

int ofxYahooWeather::getWeatherConditionCode()
{
    return ofToInt(dataContainer.at(21));
}

string ofxYahooWeather::getLastUpdated()
{
    return dataContainer.at(1);
}

int ofxYahooWeather::getTemperatureLowTomorrow()
{
    return ofToInt(dataContainer.at(32));
}

int ofxYahooWeather::getTemperatureHighTomorrow()
{
    return ofToInt(dataContainer.at(33));
}

string ofxYahooWeather::getWeatherConditionTomorrow()
{
    return dataContainer.at(34);
}

int ofxYahooWeather::getWeatherConditionCodeTomorrow()
{
    return ofToInt(dataContainer.at(35));
}

string ofxYahooWeather::getWeekdayTomorrow()
{
    return dataContainer.at(30) + ", " + dataContainer.at(31);
}

int ofxYahooWeather::getTemperatureLowDayAfterTomorrow()
{
    return ofToInt(dataContainer.at(38));
}

int ofxYahooWeather::getTemperatureHighDayAfterTomorrow()
{
    return ofToInt(dataContainer.at(39));
}

string ofxYahooWeather::getWeatherConditionDayAfterTomorrow()
{
    return dataContainer.at(40);
}

int ofxYahooWeather::getWeatherConditionCodeDayAfterTomorrow()
{
    return ofToInt(dataContainer.at(41));
}

string ofxYahooWeather::getWeekdayDayAfterTomorrow()
{
    return dataContainer.at(36) + ", " + dataContainer.at(37);
}

//additions
int ofxYahooWeather::getTemperatureLowThreeDaysLater()
{
    return ofToInt(dataContainer.at(44));
}

int ofxYahooWeather::getTemperatureHighThreeDaysLater()
{
    return ofToInt(dataContainer.at(45));
}

string ofxYahooWeather::getWeatherConditionThreeDaysLater()
{
    return dataContainer.at(46);
}

int ofxYahooWeather::getWeatherConditionCodeThreeDaysLater()
{
    return ofToInt(dataContainer.at(47));
}

string ofxYahooWeather::getWeekdayThreeDaysLater()
{
    return dataContainer.at(42) + ", " + dataContainer.at(43);
}


int ofxYahooWeather::getTemperatureLowFourDaysLater()
{
    return ofToInt(dataContainer.at(50));
}

int ofxYahooWeather::getTemperatureHighFourDaysLater()
{
    return ofToInt(dataContainer.at(51));
}

string ofxYahooWeather::getWeatherConditionFourDaysLater()
{
    return dataContainer.at(52);
}

int ofxYahooWeather::getWeatherConditionCodeFourDaysLater()
{
    return ofToInt(dataContainer.at(53));
}

string ofxYahooWeather::getWeekdayFourDaysLater()
{
    return dataContainer.at(48) + ", " + dataContainer.at(49);
}


string ofxYahooWeather::getTempUnit()
{
    return dataContainer.at(5);
}

string ofxYahooWeather::getDistanceUnit()
{
    return dataContainer.at(6);
}

string ofxYahooWeather::getPressureUnit()
{
    return dataContainer.at(7);
}

string ofxYahooWeather::getSpeedUnit()
{
    return dataContainer.at(8);
}

string ofxYahooWeather::getTitileOfWeatherInfo()
{
    return dataContainer.at(0);
}


