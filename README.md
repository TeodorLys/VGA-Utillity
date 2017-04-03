# VGA-Utillity
This repository contains the program for FarFromSublte's "Awesome Piece Theater"

When watching that show with two VLC player's open(the movie and the show) it is annoying to Play/pause
because then you have to resync the movie.

So I created this SUPER janky program that let you pause both player at the same time.

/*the code is abit messy, I only started working on it, like, a day ago... if you have any ideas on making the program better, hit me up!*/

## How it works

This program uses the Windows API, with it's SetCursorPos() function.
So it sets the mouse cursor to the first player, left clicks and the hits "SPACE"(to play/pause),
and the does the same for the second player.

I used SFML for the UI, because I couldnt be bothered to use windows convoluted functions and variables.

## Setting it up

So basically what you have to do to set it ut is: Click the "Set Pos 1" and the button goes dark, then the hold the mouse cursor
over the first player until the button goes back to normal, Then the first mouse position is set, and do the same with "Set Pos 2" with the second player.

## WHY

I have tried to use VLC's own API, but...(IT SUCKS!!). Trying to gets it's handle (EVEN IF YOU CREATE IT!!) you cant get any result... Trying to "SetForegroundWindow()" DOES NOT WORK!... anyways, rant over.
So this is the only "reliable" way I could find.
