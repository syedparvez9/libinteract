See each subdirectory for informations on each subproject of
the LibInteract library for Arduino/AVR.

From time to time, we release ZIP files which contains a part of 
the LibInteract for AVR/Arduino. 

Below is some code to do it.
---------------------------------------

ORIG=foo
ARCHIV=foo_01

cp -R $ORG $ARCHIV
find $ARCHIV -name .svn | xargs rm -rf 
find $ARCHIV -name .DS_STORE | xargs rm -rf
zip -r $ARCHIV.zip $ARCHIV

