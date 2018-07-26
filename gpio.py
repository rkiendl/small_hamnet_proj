#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# readout state of the element switches, oe6rke, 2017-06-28
# add another ports , 2018-02-25
# corretion after sdr swith , 2018-06-23

import cgi
import datetime
import RPi.GPIO as GPIO

#prepare cgi readout
form = cgi.FieldStorage() # only once

relais = cgi.escape(form.getfirst('relais', '0')) # Avoid script injection escaping the user input
mode = cgi.escape(form.getfirst('mode', 'NC'))


# RPi.GPIO Layout verwenden (wie Pin-Nummern)
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False) #to prevent errors of already set gpio.setup commands

# elements are defined as
# relais 1: PIN 5:      2m preamp Power (braunes Kabel)
# relais 2: PIN 6:      2m preamp H/V Switch (gelb/gruen Kabel)
# relais 3: PIN 13:     70m preamp Power (braunes Kabel)
# relais 4: PIN 19:     70m preamp H/V (gelb/gruenes Kabel)
# relais 5: PIN 26:     2m transverter
# relais 6: PIN 20:     ptt transverter
# relais 7: PIN 21:     sdr switch, powered on active
# relais 8: PIN 16:     Spannungsversorung CAM

# set it to output state
GPIO.setup(5, GPIO.OUT)
GPIO.setup(6, GPIO.OUT)
GPIO.setup(13, GPIO.OUT)
GPIO.setup(19, GPIO.OUT)
GPIO.setup(26, GPIO.OUT)
GPIO.setup(20, GPIO.OUT)
GPIO.setup(21, GPIO.OUT)
GPIO.setup(16, GPIO.OUT)




# header stuff
print("Content-type: text/html\n\n")
print("<!DOCTYPE html>")
print("<html lang=\"en-US\">")
print("<html><head><title>PiSwitch</title><meta http-equiv=\"refresh\" content=\"300\"></head><body>")
print("<h2>PiSwitch OE8RKE - GPIO Status</h2></br></br>")

# readout the values and show
print("<p>")

# switch matrix
# debug
# print("relais:"+relais+" mode:"+relaismode)

if relais == "01": #relais1: GPIO5
        if mode == "ON":
                GPIO.output(5, True)
        elif mode == "OFF":
                GPIO.output(5, False)
elif relais     == "02": # relais2: GPIO6
        if mode == "ON":
                GPIO.output(6, True)
        elif mode == "OFF":
                GPIO.output(6, False)
elif relais     == "03": # relais3: GPIO13
        if mode == "ON":
                GPIO.output(13, True)
        elif mode == "OFF":
                GPIO.output(13, False)
elif relais     == "04":  # relais4: GPIO19
        if mode == "ON":
                GPIO.output(19, True)
        elif mode == "OFF":
                GPIO.output(19, False)
elif relais     == "05":  # relais5: GPIO26
        if mode == "ON":
                GPIO.output(26, True)
        elif mode == "OFF":
                GPIO.output(26, False)
elif relais     == "06":  # relais6: GPIO20
        if mode == "ON":
                GPIO.output(20, True)
        elif mode == "OFF":
                GPIO.output(20, False)
elif relais     == "07":  # relais7: GPIO21
        if mode == "ON":
                GPIO.output(21, True)
        elif mode == "OFF":
                GPIO.output(21, False)
elif relais     == "08":  # relais8: GPIO16
        if mode == "ON":
                GPIO.output(16, True)
        elif mode == "OFF":
                GPIO.output(16, False)
elif relais     == "99":  # all relais toggle
        if mode == "ON":
                GPIO.output(5, True)
                GPIO.output(6, True)
                GPIO.output(13, True)
                GPIO.output(19, True)
                GPIO.output(26, True)
                GPIO.output(20, True)
                GPIO.output(21, True)
                GPIO.output(16, True)
        elif mode == "OFF":
                GPIO.output(5, False)
                GPIO.output(6, False)
                GPIO.output(13, False)
                GPIO.output(19, False)
                GPIO.output(26, False)
                GPIO.output(20, False)
                GPIO.output(21, False)
                GPIO.output(16, False)

# display the state with toggle link
print("<table>")

# relais 1
if GPIO.input(5) == GPIO.HIGH:
        print("<tr><td>Relais1: 2m Preamp </td><td>ON</td><td><a href=\"gpio.py?relais=01&mode=OFF\">Toggle to OFF</a></td></tr>")
else:
        print("<tr><td>Relais1: 2m Preamp </td><td>OFF</td><td><a href=\"gpio.py?relais=01&mode=ON\">Toggle to ON</a></td></tr>")

# relais 2
if GPIO.input(6) == GPIO.HIGH:
        print("<tr><td>Relais2: 2m Antenna Switch</td><td>ON - vertical</td><td><a href=\"gpio.py?relais=02&mode=OFF\">Toggle to OFF</a></td></tr>")
else:
        print("<tr><td>Relais2: 2m Antenna Switch</td><td>OFF - horizontal</td><td><a href=\"gpio.py?relais=02&mode=ON\">Toggle to ON</a></td></tr>")

# relais 3
if GPIO.input(13) == GPIO.HIGH:
        print("<tr><td>Relais3: 70cm Preamp </td><td>ON</td><td><a href=\"gpio.py?relais=03&mode=OFF\">Toggle to OFF</a></td></tr>")
else:
        print("<tr><td>Relais3: 70cm Preamp </td><td>OFF</td><td><a href=\"gpio.py?relais=03&mode=ON\">Toggle to ON</a></td></tr>")

# relais 4
if GPIO.input(19) == GPIO.HIGH:
        print("<tr><td>Relais4: 70cm Antenna Switch</td><td>ON - vertical</td><td><a href=\"gpio.py?relais=04&mode=OFF\">Toggle to OFF</a></td></tr>")
else:
        print("<tr><td>Relais4: 70cm Antenna Switch</td><td>OFF - horizontal</td><td><a href=\"gpio.py?relais=04&mode=ON\">Toggle to ON</a></td></tr>")

# relais 5
if GPIO.input(26) == GPIO.HIGH:
        print("<tr><td>Relais5: 2m Transverter</td><td>ON</td><td><a href=\"gpio.py?relais=05&mode=OFF\">Toggle to OFF</a></td></tr>")
else:
        print("<tr><td>Relais5: 2m Transverter</td><td>OFF</td><td><a href=\"gpio.py?relais=05&mode=ON\">Toggle to ON</a></td></tr>")

# relais 6
if GPIO.input(20) == GPIO.HIGH:
        print("<tr><td>Relais6: PTT Transverter</td><td>ON</td><td><a href=\"gpio.py?relais=06&mode=OFF\">Toggle to OFF</a></td></tr>")
else:
        print("<tr><td>Relais6: PTT Transverter</td><td>OFF</td><td><a href=\"gpio.py?relais=06&mode=ON\">Toggle to ON</a></td></tr>")

# relais 7
if GPIO.input(21) == GPIO.HIGH:
        print("<tr><td>Relais7: SDR Switch (active=on)</td><td>ON</td><td><a href=\"gpio.py?relais=07&mode=OFF\">Toggle to OFF</a></td></tr>")
else:
        print("<tr><td>Relais7: 23cm Transverter</td><td>OFF</td><td><a href=\"gpio.py?relais=07&mode=ON\">Toggle to ON</a></td></tr>")

# relais 8
if GPIO.input(16) == GPIO.HIGH:
        print("<tr><td>Relais8: Camera</td><td>ON</td><td><a href=\"gpio.py?relais=08&mode=OFF\">Toggle to OFF</a></td></tr>")
else:
        print("<tr><td>Relais8: Camera</td><td>OFF</td><td><a href=\"gpio.py?relais=08&mode=ON\">Toggle to ON</a></td></tr>")

print("</table></br>")
print("<a href=\"gpio.py?relais=99&mode=ON\">Toggle ALL to ON</a></br>")
print("<a href=\"gpio.py?relais=99&mode=OFF\">Toggle ALL to OFF</a></br>")

#end of html
print("</p></body></html>")

# end of program, gpio cleanup not needed
