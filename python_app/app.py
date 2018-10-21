# Code by   : LKBrilliant
# Date      : 19.10.2018
# Project   : Motor-Driver-with-Firebase-and-ESP8266
# Python version 3.6.2
# This code will connect to the firebase real time database and create/update a child 'Slider' 
# and change its value according to the slider value in the app
#****only dragging and releasing the slider by mouse will send data to the database

import sys
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QSlider, QWidget, QLCDNumber, QApplication, QVBoxLayout

from firebase import firebase
firebase = firebase.FirebaseApplication('https://dld-v3.firebaseio.com/',None)
firebase.put('/','Slider', 0)  # Initialize the session with value 0 

class Slider(QWidget):
    
    def __init__(self):
        super().__init__()
        self.initUI()
        
    def initUI(self):
    
        def changeValue():     # only run when value changed on the slider
            firebase.put('/','Slider', slider.value())

        lcd = QLCDNumber(self)
        slider = QSlider(Qt.Horizontal, self)
        slider.setRange(0, 1023)
        slider.sliderReleased.connect(changeValue)

        vbox = QVBoxLayout()
        vbox.addWidget(lcd)
        vbox.addWidget(slider)

        self.setLayout(vbox)
        slider.valueChanged.connect(lcd.display)

        self.setFixedSize(400, 200)
        self.setWindowTitle('Motor Controller')
        self.setWindowIcon(QIcon('icon.png'))
        self.show()
        
    def keyPressEvent(self, e):
        if e.key() == Qt.Key_Escape:    # Escape key to exit
            self.close()    

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Slider()
    sys.exit(app.exec_())
    firebase.put('/','Slider', 0)   # upon exiting change the value to 0
