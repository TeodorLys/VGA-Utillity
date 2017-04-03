# VGA-Utillity
This repository contains the program for FarFromSublte's "Awesome Piece Theater"

When watching that show with two VLC player's open(the movie and the show) it is annoying to Play/pause
because then you have to resync the movie.

So I created this SUPER janky program that let you pause both player at the same time.

/*I am sorry if the code is messy, I only started working on it, like, a day ago...*/

## How it works

This program uses the Windows API, with it's SetCursorPos() function.
So it sets the mouse cursor to the first player, left clicks and the hits "SPACE"(to play/pause),
and the does the same for the second player.

## Setting it up

So basically what you have to do to set it ut is: Click the "Set Pos 1" and the button goes dark, then the hold the mouse cursor
over the first player until the button goes back to normal(Then the first pos is set), and do the same with "Set Pos 2" with the second player.
