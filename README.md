# VGA-Utillity
This repository contains the program for FarFromSublte "Awesome Piece Theater"

When watching that show and have open two VLC player(or what ever you are using) it is annoying to Play/pause
because you have to resync the movie.

So I created this SUPER janky program that let you pause both player at the same time.

I am sorry if the code is messy, I only started working on it, like, 1 day ago.

## How it works

This program uses the Windows API, with it's SetCursorPos() function.
So this program works so, it sets the mouse cursor to the first player, left clicks and the hits "SPACE"(to play/pause),
and the does the same for the second player.
So basically what you have to do to set it ut is: Click the "Set Pos 1" and the button goes dark, then the hold the mouse cursor
over the first player until the button goes back to normal(Then the first pos is set), and do the same with "Set Pos 2" with the second player.
