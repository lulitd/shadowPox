#pragma once

#include "ofMain.h"
#include "ofxKinectForWindows2.h"
#include "ofxRay.h"
#include "ofxOpenCv.h"

#include "ofxSvg.h"
#include "GuiApp.h"
#include "cellCluster.h"
#include "cell.h"
#include "miniFigs.h"
#include "ofxTextAlignTTF.h"
#include "ofxCSV.h"
#include "poxemon.h"

//#include "country.h"
class ofApp : public ofBaseApp {

public:

	// open frameworks default!
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void exit();
	void SaveData();
	void drawHuman(int color, bool showCursor=false);
	void pointsOnCirleFromLine(ofPoint, ofPoint, float, ofPoint&, ofPoint&, ofPoint&, ofPoint&);


	
	ofPath polyBody;

	ofxTextAlignTTF text;

	ofxTextAlignTTF largeText;
	ofxKFW2::Device kinect;
	ofxRay::Camera projector;
	float gameTimer = 0;
	shared_ptr<GuiApp> gui;
	std::vector<cellCluster> patients;
	std::vector<miniFig> figures;

	std::vector<ofVec2f> leftLocations;
	std::vector<ofVec2f> rightLocations;
	std::vector<ofVec2f> flagLocations;
	std::vector<ofVec3f> jointsInScreenSpace;
	std::vector<ofImage> regions;
	std::vector<ofImage> flags;
	std::vector<ofImage> hands;

	ofPoint regionCenter[11];
	struct countryInfo {
		int index;
		ofImage* flagImage = nullptr;
		ofRectangle bounds;
	};

	int selectedCountryInRegion = -1;
	map<int, vector<countryInfo>> countriesInRegion;
	vector<countryInfo>* selectedRegion = nullptr;
	ofImage* displayRegion = nullptr;
	int infectionScore = 0;
	bool isVaccine = false;
	ofxTextAlignTTF text_;
	ofVec2f p1;
	ofVec2f p2;

	ofPoint handR;
	HandState handState;
	HandState prevState;
	int HandStateCounter;

	bool MANUAL_SELECTION = true;

	struct handPointer {
		ofPoint pos;
		HandState currentHandState;
		HandState prevHandState;
		int HandStateCounter = 0;
		ofImage cursor;

	} rightHand,leftHand;

	int handPointerStateCounterThres = 2;
	countryInfo* selectedCountry = nullptr;

	bool chooseRegion = false;
	bool tracking = false;
	string availablePatients = "";
	int selected = -1;

	int handStateCounterL = 0;
	int handStateCounterR = 0;

	int alpha = 255;
	float alphaTimer;
	float spawnTimer;

	float transitionTimer = 0;
	bool  countrySelect = false;

	ofPoint flagOrgSize;

	ofVideoPlayer screenSaverPlayer;
	ofVideoPlayer introTextPlayer;

	ofVideoPlayer demoPushPlayer;
	ofFbo skeletonFBO;

	enum class sequenceMode {
		SCREENSAVER,
		INTRO,
		COUNTRYCHOICE,
		VACCINECHOICE,
		GAMEPLAY,
		END
	};
	sequenceMode currentState = sequenceMode::GAMEPLAY;

	ofxCsv sourceData;
	ofxCsv logData;
	//ofxCsvRow selectedCountry;

	bool displaySkipButton = false; 
	bool displayBackButton = false; 
	int regSel = -1;
	int pastRegSel = -1;
	
private:
	int framerate = 25;
	void figureSetup(int amount, int percent);
	int figureAmount = 99;
	bool dataIsLoaded = false;

	ofImage worldMap;
	ofxSVG bounds;
	std::vector<ofPolyline> boundaries;
	enum sourceCol {
		REGIONCODE = 0,
		COUNTRYNUMBER,
		COUNTRY,
		STARTINGVACCINATIONRATE,
		STARTINGSEVERITYSCORE,
		CHANGEINSEVERITY,
		MAXIMUMSEVERITYSCORE,
		CURRENTSEVERITY,
		CURRENTVACCINATIONRATE,
	};
	struct imageButton {
		ofRectangle bounds;
		ofImage image;
		int index;
		ofPoint size;
		bool event = true; 
		float timeStamp;
	} vaccineButton, virusButton, backButton,backButtonAlt,skipButton,newGameButton,forwardButton,backwardButton;

	ofImage* selectedCardImage;

	int choiceSeqVaccine = -1;

	string displayText = "";
	string warningText = "One player at a time, please!";

	unsigned int textAlignFlag = 0;
	unsigned int vaccineDialog = -1;
	unsigned int endDialog = -1;
	string fileName = "";
	unsigned int modInfectionScore = 0;
	bool scoreCalculated = false; 
	bool prevFlipTextStatus = false;
	int numOfBodiesTracked = 0; 
	float lastBodyTrackTime = 0; 
	bool displayDemoVid = false; 

	int textAlignmentX = 0; 
	int selectedCard = 0; 
	// Default code to pass into poxemon code function.
	char code[4] = "???";
	bool shouldFlipCard = true; 
	bool setupCardsDisplay = true; 

};
	
