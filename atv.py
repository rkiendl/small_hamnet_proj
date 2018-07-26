#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# ATV Mode switch, via IR Codes
# send via code irsend SEND_ONCE avmatrix_SZ KEY_F3
# 2018-07-22

import cgi
import datetime
import subprocess

#prepare cgi readout
form = cgi.FieldStorage() # only once
mode = cgi.escape(form.getfirst('mode', '0'))

# elements are defined as
# mode 01: 1. matrix , irsend SEND_ONCE avmatrix_SZ KEY_F2
# mode 02: 2. matrix , irsend SEND_ONCE avmatrix_SZ KEY_F3


# header stuff
print("Content-type: text/html\n\n")
print("<!DOCTYPE html>")
print("<html lang=\"en-US\">")
print("<html><head><title>ATV Switch-OE6XFE</title><meta http-equiv=\"refresh\" content=\"300\"></head><body>")
print("<h2>ATV-Switch OE6XFE</h2></br></br>")

# readout the values and show
print("<p>")

# switch matrix
# debug
# print("mode:"+relaismode)

if mode == "01": #1. matrix - 4 bilder
	subprocess.call('irsend SEND_ONCE avmatrix_SZ KEY_F2', shell=True)
elif mode == "02": # 2.matrix - 4 bilder
	subprocess.call('irsend SEND_ONCE avmatrix_SZ KEY_F3', shell=True)
elif mode == "05": # alle bilder
	subprocess.call('irsend SEND_ONCE avmatrix_SZ KEY_F5', shell=True)
elif mode == "06": # alle bilder spezial
	subprocess.call('irsend SEND_ONCE avmatrix_SZ KEY_F6', shell=True)
	
elif mode == "11": # 1. bild voll matrix
	subprocess.call('irsend SEND_ONCE avmatrix_SZ KEY_1', shell=True)
elif mode == "12": # 2. bild voll matrix
	subprocess.call('irsend SEND_ONCE avmatrix_SZ KEY_2', shell=True)
elif mode == "13": # 3. bild voll matrix
	subprocess.call('irsend SEND_ONCE avmatrix_SZ KEY_3', shell=True)
elif mode == "14": # 4. bild voll matrix
	subprocess.call('irsend SEND_ONCE avmatrix_SZ KEY_4', shell=True)	
	

# display the state with toggle link
print("<table>")

# nice selection table
print("<tr><td>1. Matrix - 4 Bilder</td><td><a href=atv.py?mode=01>switch to mode</a></td></tr>")
print("<tr><td>2. Matrix - 4 Bilder</td><td><a href=atv.py?mode=02>switch to mode</a></td></tr>")
print("<tr><td>1.Bild voll in aktueller Matrix</td><td><a href=atv.py?mode=11>switch to mode</a></td></tr>")
print("<tr><td>2.Bild voll in aktueller Matrix</td><td><a href=atv.py?mode=12>switch to mode</a></td></tr>")
print("<tr><td>3.Bild voll in aktueller Matrix</td><td><a href=atv.py?mode=13>switch to mode</a></td></tr>")
print("<tr><td>4.Bild voll in aktueller Matrix</td><td><a href=atv.py?mode=14>switch to mode</a></td></tr>")
print("<tr><td>Alle Bilder</td><td><a href=atv.py?mode=05>switch to mode</a></td></tr>")
print("<tr><td>Alle Bilder Spezial</td><td><a href=atv.py?mode=06>switch to mode</a></td></tr>")

print("</table>")
#end of html
print("</p></body></html>")

# end of program, cleanup not needed

