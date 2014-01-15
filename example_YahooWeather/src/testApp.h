#pragma once

#include "ofMain.h"
#include "ofxYahooWeather.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofxYahooWeather weather;
    
        //requires "WOEID(Where On Earth ID)" to set location
        //you can find a WOEID of the location you want to know from an address of Yahoo! weather information.
        //E.g. : Osaka City, Osaka Pref. Japan = http://weather.yahoo.com/japan/osaka-prefecture/osaka-shi-15015370/
    
        int osaka = 15015370;
        int tokyo = 1118370;
		
};
