# Emacs-C-CPP-IDE
A spacemacs configuration for a fully featured C/CPP IDE 

## Installation

1. Place .emacs.d at ~
2. Copy cc-args.py to /usr/local/bin and make it executable
3. copy .spacemacs to ~
4. Install adobe source pro fonts for a cleaner truetype experience
5. Install clang
6. Install emacs or emacs-noX

## To-Do
1. Make an automation script to set it all up. 
2. Release a lightweight version keeping packages used to a bare minimum.(Stripping stuff off Spacemacs that we won't need)
3. Add detailed usage to setup projects and using CMake to enhance auto completions and also use make an automation script for this.
4. Add a graphical illustration here

### Auto-competion and error checking
![Auto-competion and error checking](https://github.com/another-dark-knight/Emacs-C-CPP-IDE/blob/master/gifs/cv2-error.gif)

1. The autocompletions are from OpenCV4
2. Note that when a=4 is written there is a sign in the status bar below right after C++//1 which shows the number of errors.
3. If you hover at a=4 the error message is shown right below the status bar.
