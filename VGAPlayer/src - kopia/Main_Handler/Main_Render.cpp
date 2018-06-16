#include "Main_Render.h"
#include "Objects\Buttons.h"
#include "Objects\Switch.h"
#include "Write_Field.h"
#include "Events\Animation.h"
#include "Handlers\Context_Handler.h"
#include "Events\Debugging.h"
#include "Objects\Play_Pause_Icon.h"
#include "Events\MovieEvents.h"

#include "Shared\Shared_sfml_Objects.h"
#include "Shared\Shared_Modules.h"
#include "Shared\Shared_Boolean.h"
#include "Shared\Shared_sfe_Movie.h"


/////////////////////////////////////////////////////////////
/// \Renders the menu objects							  ///
/////////////////////////////////////////////////////////////
void Main_Render::Local_Menu_Render(Context_Handler &context_Handle, Debugging &debug) {
 Shared_sf::window.clear();   //Clears the RAM of all unused stuff /*I think*/

 Shared_sf::window.draw(Shared_sf::b);   //Draws the background
 Shared_sf::window.draw(Shared_sf::theCrew);
 Shared_Mod::play->draw();   //Draws the play button 
 Shared_Mod::ffstv->draw();   //Draws the OPEN FFSTV VIDEO button
 Shared_Mod::film->draw();   //Draws the OPEN MOVIE FILE button

 Shared_Mod::oneMovie->draw();

 context_Handle.basic.contextMenuShown ? context_Handle.basic.draw(Shared_sf::window) : 0;

 debug.writing ? debug.draw() : 0;

 Shared_sf::window.display();   //Display what was just drawn
}


/////////////////////////////////////////////////////////////
/// \Renders the movie(s) Locally                         ///
/////////////////////////////////////////////////////////////
void Main_Render::Local_Movie_Render(Play_Pause_Icon *play, movBase *movie, Context_Handler *context_Handle, Debugging &debug) {
 //Updates only the active movies.
 movie->updateMovies(*Shared_sfe::movie, *Shared_sfe::movie2);

 //
 //TODO: Should probably have all of the popout stuff in a seperate class/file *Thought?*
 //

 if (Shared_bool::second_Movie_Popout)
  Shared_sf::second_Window.clear();
 Shared_sf::window.clear();

 //You can put the second movie behind the first movie
 if (Shared_bool::behind)
  movie->drawMovieInv(*Shared_sfe::movie, *Shared_sfe::movie2);
 else
  movie->drawMovie(*Shared_sfe::movie, *Shared_sfe::movie2);

 //
 //Only renders the active objects
 //

 movie->Draw_Text(Shared_sf::vol1, Shared_sf::vol2);
 movie->Draw_Text(Shared_sf::tTimer, Shared_sf::smalltTimer);

 play->Draw();

 if (context_Handle->mainMovie.contextMenuShown) {
  context_Handle->mainMovie.draw(Shared_sf::window);
 }

 //
 //Debugging rendering stuff...
 //

 if (debug.writing) {
  debug.draw();
 }
 else if (Write_Field::write().is_Writing) {
  Write_Field::write().setOpacity(255);
 }

 if (!Write_Field::write().Is_Invisible()) {
  if (!Write_Field::write().is_Writing)
   Write_Field::write().setOpacity(Animation::Lerp_Opacity(Write_Field::write().getColor().a, 10));
  Write_Field::write().Draw();
 }
 if (Shared_bool::second_Movie_Popout)
  Shared_sf::second_Window.display();
 Shared_sf::window.display();
}