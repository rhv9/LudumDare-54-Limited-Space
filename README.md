# How much space does your RAM have?

This is a game created for the 54th running of Ludum Dare.

The theme is Limited Space. You can find the full description of the game over at the submission page. 

Before the link, I would like to thank and say that the Game Engine Gonk used is essentially a complete rote copy of [Hazel-2D Engine](https://github.com/TheCherno/Hazel), created by following TheCherno's Game Engine series (up to episode 80).

Link: https://ldjam.com/events/ludum-dare/54/$374776 

## Compiling/Running from source files yourself

To build the solution yourself, you won't be able to (at least without a few major issues). 

Problem is that there are 2 premake files missing, that are required when creating the Visual Studio .sln file so that you can compile and link to the final executable yourself. 

The two missing premake files are I believe `Gonk/vendor/imgui` and `Gonk/vendor/GLFW`, although I am not quite sure. These premake files are included into the main premake file (that is ran when running project build batch script). These files are not there/not latest version because I am lazy to figure out git submodules.   

If you want the premake files for some reason (I have no clue why on Earth - or any planet really - you would do this), you could open up issues to ask for the files from me and I can help you.

If you are still stubborn, or got the premake files from me, or you think you can figure it out yourself (very impressive!), the steps are as follows:
(Note. If it doesn't work, maybe check the latest commit if I have made any changes and/or corrected the steps.)

1. Clone the repository with all submodules.
   ```
   git clone --recurse-submodules https://github.com/rhv9/LudumDare-54-Limited-Space
   ```

2. Add premake binary to folder `~\vendor\premake`. Get the executable online.

3. Open the scripts directory inside and run the generate project .bat file. This will create a Visual Studio Solution file.
   ```
   cd LudumDare-54-Limited-Space\scripts
   ./Win-Gen-Projects.bat
   ```

Done! Now you should have errors since you do not have the necessary premake files!
