#include "movieDuration.h"
#include "GlobalVariables.h"
#include <iostream>

using namespace std;
using namespace GV;

void movieDuration::Timer() {

	if (bools.movieIsPlaying) {

		if (value.currentSecond >= 60) {
			if (value.currentMinute == 59) {
				value.currentHour += 1;
				value.currentMinute = 0;
			}
			else {
				value.currentMinute += 1;
			}
			value.currentSecond = 0;
		}
		else {
			value.currentSecond = (int)sfemov.movie.getPlayingOffset().asSeconds() -
				((value.currentMinute * 60) + ((value.currentHour * 60) * 60));
		}

		str.strTime = to_string(value.currentHour) + ":" + to_string(value.currentMinute) + ":" + to_string(value.currentSecond) + "  /  " +
			to_string(value.hour) + ":" + to_string(value.minute) + ":" + to_string(value.second);

		sfm.tTimer.setString(str.strTime);
	}
}//Timer Function END

void movieDuration::smallTimer() {

	if (bools.movieIsPlaying) {

		////////////////////////////////////////////////////////////////////////////////
		///Timer for the smaller movie
		if (mod.oneMovie->switchON) {
			if (value.smallcurrentSecond >= 60) {
				if (value.smallcurrentMinute == 59) {
					value.smallcurrentHour += 1;
					value.smallcurrentMinute = 0;
				}
				else {
					value.smallcurrentMinute += 1;
				}
				value.smallcurrentSecond = 0;
			}
			else {
				value.smallcurrentSecond = (int)sfemov.movie2.getPlayingOffset().asSeconds() - ((value.smallcurrentMinute * 60) + ((value.smallcurrentHour * 60) * 60));
			}

			str.smallstrTime = to_string(value.smallcurrentHour) + ":" + to_string(value.smallcurrentMinute) + ":" + to_string(value.smallcurrentSecond) + "  /  " +
				to_string(value.smallhour) + ":" + to_string(value.smallminute) + ":" + to_string(value.smallsecond);

			sfm.smalltTimer.setString(str.smallstrTime);
		}
	}
}//SmallTimer Function END