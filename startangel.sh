sudo chmod o+rw /dev/ttyUSB0
jpnevulator --timing-print --tty /dev/ttyUSB0:SB9600d --read &
/opt/sdrangel/bin/sdrangel

sudo pkill jpnevulator
