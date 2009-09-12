
#From time to time, we release ZIP files which contains a part of 
#the LibInteract for AVR/Arduino. 

#Below is some code to do it.
#---------------------------------------

# the dir to release
ORIG=Tween
ARCHIV=Tween_01

all: clean
	cp -R ${ORIG} ${ARCHIV}
	find ${ARCHIV} -name .svn | xargs rm -rf 
	find ${ARCHIV} -name .DS_Store | xargs rm -rf
	zip -r ${ARCHIV}.zip ${ARCHIV}

clean:
	rm -rf ${ARCHIV}
	rm -rf ${ARCHIV}.zip

