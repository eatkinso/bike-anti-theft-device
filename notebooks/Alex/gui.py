import json
from PyQt5 import QtCore, QtWidgets, QtWebEngineWidgets, QtWebChannel, QtNetwork
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *

from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
import matplotlib.pyplot as plt

import sys
import random
import serial

def exit():
  sys.exit(app.exec_())

def show_map():
    "Need to implement"
    return None

def data_windows():
  listWidget = QListWidget()
  listWidget.resize(300,120)
  for idx in range(4):
    listWidget.addItem("idx")
  listWidget.show()

def start_button():
  msg = QMessageBox()
  msg.setWindowTitle("Bike Data")
  msg.setStandardButtons(QMessageBox.Ok | QMessageBox.Cancel)
  l = []
  for idx in range(1000):
    l += [idx]
  msg.setText('Bike Position History:')
  msg.setDetailedText('Position at:\n ' + str(l))
  msg.exec()


if __name__ == '__main__':
  app = QApplication([])
  window = QWidget()
  label = QLabel("Welcome to Bike Anti-Theft GUI")
  button1 = QPushButton('Start')
  button2 = QPushButton('Documentation')
  button3 = QPushButton('Map (CURRENTLY DEFUNCT)')
  exit_but = QPushButton('Exit')
  layout = QVBoxLayout()
  layout.addWidget(label)
  layout.addWidget(button1)
  layout.addWidget(button3)
  layout.addWidget(button2)
  layout.addWidget(exit_but)
  button1.clicked.connect(start_button)
  button3.clicked.connect(show_map)
  exit_but.clicked.connect(exit)
  rev = QLabel('#45          vs 1.0.0')
  layout.addWidget(rev)
  window.setLayout(layout)
  window.show()
  
  app.exec()
