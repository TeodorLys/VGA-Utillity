

#include "MovieEvents.h"
#include "GlobalVariables.h"

using namespace GV;
using namespace std;

void Movies::stop() {
	sfemov.movie->stop();
	if (mod.oneMovie->switchON)
		sfemov.movie2->stop();
}

void Movies::play() {
	sfemov.movie->play();
	if (mod.oneMovie->switchON)
		sfemov.movie2->play();
}

void Movies::pause() {
	GV::sfemov.movie->pause();
	if (GV::mod.oneMovie->switchON)
		GV::sfemov.movie2->pause();
}

void Movies::drawVol(sf::RenderWindow &window, sf::Text &t1, sf::Text &t2) {
	GV::sfm.window.draw(t1);
	if (GV::mod.oneMovie->switchON)
		GV::sfm.window.draw(t2);
}

void Movies::drawShape(sf::RenderWindow &window, sf::RectangleShape &shape1, sf::RectangleShape &shape2) {
	GV::sfm.window.draw(shape1);
	if (GV::mod.oneMovie->switchON)
		GV::sfm.window.draw(shape2);
}

void Movies::drawMovie(sf::RenderWindow &window, sfe::Movie &mov1, sfe::Movie &mov2) {
	if (GV::mod.oneMovie->switchON)
		GV::sfm.window.draw(mov2);

	GV::sfm.window.draw(mov1);
}

void Movies::drawMovieInv(sf::RenderWindow &window, sfe::Movie &mov1, sfe::Movie &mov2) {
	GV::sfm.window.draw(mov1);

	if (GV::mod.oneMovie->switchON)
		GV::sfm.window.draw(mov2);
}

void Movies::updateMovies(sf::RenderWindow &window, sfe::Movie &mov1, sfe::Movie &mov2) {
	GV::sfemov.movie->update();

	if (GV::mod.oneMovie->switchON)
		GV::sfemov.movie2->update();
}

void Movies::movieTimers() {
	GV::obj.md.Timer();

	if (mod.oneMovie->switchON)
		GV::obj.md.smallTimer();
}

void Movies::setVolume() {
	sfemov.movie->setVolume(value.mov1Vol);
	if (mod.oneMovie->switchON)
		sfemov.movie2->setVolume(value.mov2Vol);
}

void Movies::setMovieTimes() {
	sfemov.movie->setPlayingOffset(sf::seconds(value.mov1SaveTime));

	if (mod.oneMovie->switchON) {
		sfemov.movie2->setPlayingOffset(sf::seconds(value.mov2SaveTime));

		sfm.off = sf::seconds(value.mov2OffsetTime);
	}
}