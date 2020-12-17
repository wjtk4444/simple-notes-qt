# simple-notes-qt

A simple notes application written in qt.  
1 file, ~125 LOC.  
Intended for use with KDE and custom kWin rules, made to replace KDE's default 'sticky-notes' desktop widget.  

# how to build
`git clone` this repo  
`cd` into the `src` directory  
execute this command:
`moc -o main.moc main.cpp && qmake && make && make clean`  
that's it

# how to run
`./notes ~/Documents/my_notes.txt`

# how to setup
I recommend writing a single-line bash script and making it start with the system. For example:
```
#!/bin/bash
notes ~/Documents/my_notes.txt &
```
Additionally, check out my custom kWin rule settings [here](kWin_settings/)  
It's pretty much useless without them, unless you'll do some minor code edits to change window's size and properties.  
  
There is no way to customize this application other than editing the source code. And there won't be. This is not an acutal project, just a tool I made for myself to make my life easier. Feel free to modify it to you liking.

# somewhat important note
Notes are saved everytime the contents have changed *(duh)* **and** when the program window **loses it's focus**. If the process gets killed while the windows is still focused (emergency shutdown? maybe?), data could be lost. I don't think that it is something that could happen under normal circumstances.
