// DIY Teensy Based midi controller
// script file adds functionality for:
// 	controlling 4 sampler decks in Mixxx
// 
// Based on Numark Mixtrack Pro Mapping Script Functions
// 2/2/2014 - v0.1 - Joshua Besneatte
//
// ************* Script is Only for 1.11.0 and above *************
//	Sync:	If the other deck is stopped, only sync tempo (not fase).
//		LED Blink at Clip Gain (Peak indicator).
//


function TeensySteamKandy() {}

TeensySteamKandy.init = function(id) {	// called when the MIDI device is opened & set up
	TeensySteamKandy.id = id;	// Store the ID of this device for later use
	
	TeensySteamKandy.manualLoop = [true, true];
	TeensySteamKandy.deleteKey = [false, false];

	TeensySteamKandy.leds = [
		// Sampler 1
		{ "hotCue1" : 0x41,"hotCue2" : 0x40 },
		// Sampler 2
		{ "hotCue1" : 0x44,"hotCue2" : 0x43 },
		// Sampler 3
		{ "hotCue1" : 0x47,"hotCue2" : 0x46 },
		// Sampler 4
		{ "hotCue1" : 0x4a,"hotCue2" : 0x49 }
	];

	for (i=0x3c; i<=0x4a; i++) midi.sendShortMsg(0x90, i, 0x00); 	// Turn off all the lights

	TeensySteamKandy.hotCue = {
			//Sampler 1 
			0x41:"1",0x40:"2",
			//Sampler 2
			0x44: "1",0x43:"2",
			//Sampler 3
			0x47: "1",0x46:"2",
			//Sampler 4
			0x4a: "1",0x49:"2"
			};

	//Add event listeners
	for (var i=1; i<5; i++){
		for (var x=1; x<3; x++){
			engine.connectControl("[Sampler" + i +"]", "hotcue_" + x + "_enabled", "TeensySteamKandy.onHotCueChange");
		}
	}

}

TeensySteamKandy.shutdown = function(id) {	// called when the MIDI device is closed

	// First Remove event listeners
	for (var i=1; i<5; i++){
		for (var x=1; x<3; x++){
			engine.connectControl("[Sampler" + i +"]", "hotcue_"+ x +"_enabled", "TeensySteamKandy.onHotCueChange", true);
		}	
	}

	var lowestLED = 0x3c;
	var highestLED = 0x4b;
	for (var i=lowestLED; i<=highestLED; i++) {
		TeensySteamKandy.setLED(i, false);	// Turn off all the lights
	}

}

TeensySteamKandy.groupToDeck = function(group) {

	var matches = group.match(/^\[Sampler(\d+)\]$/);

	if (matches == null) {
		return -1;
	} else {
		return matches[1];
	}

}

TeensySteamKandy.setLED = function(value, status) {

	status = status ? 0x64 : 0x00;
	midi.sendShortMsg(0x90, value, status);
}

TeensySteamKandy.playbutton = function(channel, control, value, status, group) {

	if (!value) return;

	var deck = TeensySteamKandy.groupToDeck(group);

	if (engine.getValue(group, "play")) {
		engine.setValue(group, "play", 0);
	}else{
		engine.setValue(group, "play", 1);
	}

}

TeensySteamKandy.onHotCueChange = function(value, group, key){
	var deck = TeensySteamKandy.groupToDeck(group);
	var hotCueNum = key[7];
	TeensySteamKandy.setLED(TeensySteamKandy.leds[deck-1]["hotCue" + hotCueNum], value ? true : false);
}

TeensySteamKandy.changeHotCue = function(channel, control, value, status, group){

	var deck = TeensySteamKandy.groupToDeck(group);
	var hotCue = TeensySteamKandy.hotCue[control];

	// onHotCueChange called automatically
	if(TeensySteamKandy.deleteKey[deck-1]){
		if (engine.getValue(group, "hotcue_" + hotCue + "_enabled")){
			engine.setValue(group, "hotcue_" + hotCue + "_clear", 1);
		}
		TeensySteamKandy.toggleDeleteKey(channel, control, value, status, group);
	} else {
		if (value) {
			engine.setValue(group, "hotcue_" + hotCue + "_activate", 1);
			
		}else{

			engine.setValue(group, "hotcue_" + hotCue + "_activate", 0);
		}
	}
}

TeensySteamKandy.toggleDeleteKey = function(channel, control, value, status, group){
	if (!value) return;
	var deck = TeensySteamKandy.groupToDeck(group);
	TeensySteamKandy.deleteKey[deck-1] = !TeensySteamKandy.deleteKey[deck-1]; 
	TeensySteamKandy.setLED(TeensySteamKandy.leds[deck-1]["deleteKey"], TeensySteamKandy.deleteKey[deck-1]);
}


