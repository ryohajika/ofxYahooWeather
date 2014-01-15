#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //if you want to receive temperature information in Fahrenheit scale,
    //change 'c' to 'f'.
    
    weather.setup(osaka, 'c');
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if (key=='1'){
        weather.resetWOEID(osaka);
        ofLogNotice("WOEID = Osaka");
    }
    else if (key=='2') {
        weather.resetWOEID(tokyo);
        ofLogNotice("WOEID = Tokyo");
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    //In this case, the weather information will be updated by mouse releasing.
    
    weather.update();
    ofLogNotice(weather.getTitileOfWeatherInfo());
    ofLogNotice(weather.getCityName() + ", " + weather.getCountryName() + ": " + weather.getWeatherCondition());
    
    ofLogNotice(weather.getWeekdayTomorrow() + ": " + weather.getWeatherConditionTomorrow());
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
