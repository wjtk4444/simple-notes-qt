# simple_notes_qt
Simple notes application

A really, really, really (!) simple notes application written in qt.  
1 file, ~125 LOC.  
Intended for use with KDE and custom kWin rules, made to replace KDE's default 'sticky-notes' desktop widget.  

# how to build
`git clone` this repo
`cd` into the src directory
execute this command:
`moc -o main.moc main.cpp && qmake && make && make clean`
that's it

# how to run
`./notes ~/Documents/my_notes.txt`

# how to setup
I do recommend to write a single-line bash script, and make it start with the system. For example:
```
#!/bin/bash
notes ~/Documents/my_notes.txt &
```
Additionally, check my custom kWin rule settings [here](kWinSettings/)

# somewhat important note
Notes are saved everytime the contents changed *duh* and when the program window **loses it's focus!** Make sure you won't make some important notes and then shut down the pc while keeping notes window focused. I don't think that it is something that could happen under normal circumstances, but better safe than sorry.



