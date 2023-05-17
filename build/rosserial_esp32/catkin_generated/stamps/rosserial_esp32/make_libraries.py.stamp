#!/usr/bin/env python3

import os
import sys
import shutil

from rospkg import RosPack

from rosserial_client import make_library
from rosserial_client.make_library import (
    PrimitiveDataType,
    TimeDataType,
    StringDataType,
    MessageDataType,
)

THIS_PACKAGE = "rosserial_esp32"

__usage__ = """
make_libraries.py generates the ESP32 rosserial library files for ESP32 (ESP-IDF).
It requires the location of your esp-idf/components folder.

rosrun rosserial_esp32 make_libraries.py $IDF_PATH/components
"""

# for copying files

# need correct inputs
if len(sys.argv) < 2:
    print(__usage__)
    exit()

# get output path
path = sys.argv[1]

if path[-1] == "/":
    path = path[0:-1]
print("\nExporting to %s" % path)

rospack = RosPack()

# Create rosserial_esp32 component folder if it doesn't exist
if not os.path.exists(path + "/rosserial_esp32/"):
    os.makedirs(path + "/rosserial_esp32/include/")
    with open(path + "/rosserial_esp32/component.mk", "w") as file:
        pass

# copy ros_lib stuff in
rosserial_esp32_dir = rospack.get_path(THIS_PACKAGE)
files = os.listdir(rosserial_esp32_dir + "/src/ros_lib")
for f in files:
    if os.path.isfile(rosserial_esp32_dir + "/src/ros_lib/" + f):
        if f.endswith(".h"):
            shutil.copy(rosserial_esp32_dir + "/src/ros_lib/" + f, path + "/rosserial_esp32/include/")
        else:
            shutil.copy(rosserial_esp32_dir + "/src/ros_lib/" + f, path + "/rosserial_esp32/")

make_library.rosserial_client_copy_files(rospack, path + "/rosserial_esp32/include/")

# Define ROS_TO_EMBEDDED_TYPES dictionary
ROS_TO_EMBEDDED_TYPES = {
    'bool': ('bool', 1, PrimitiveDataType, []),
    'byte': ('int8_t', 1, PrimitiveDataType, []),
    'int8': ('int8_t', 1, PrimitiveDataType, []),
    'char': ('char', 1, PrimitiveDataType, []),
    'uint8': ('uint8_t', 1, PrimitiveDataType, []),
    'int16': ('int16_t', 2, PrimitiveDataType, []),
    'uint16': ('uint16_t', 2, PrimitiveDataType, []),
    'int32': ('int32_t', 4, PrimitiveDataType, []),
    'uint32': ('uint32_t', 4, PrimitiveDataType, []),
    'int64': ('int64_t', 8, PrimitiveDataType, []),
    'uint64': ('uint64_t', 8, PrimitiveDataType, []),
    'float32': ('float', 4, PrimitiveDataType, []),
    'float64': ('double', 8, PrimitiveDataType, []),
    'time': ('ros::Time', 8, TimeDataType, ['ros/time']),
    'duration': ('ros::Duration', 8, TimeDataType, ['ros/duration']),
   
'string': ('char*', 0, StringDataType, []),
'Header': ('std_msgs::Header', 0, MessageDataType, ['std_msgs/Header'])
}


make_library.rosserial_generate(rospack, path + "/rosserial_esp32/include/", ROS_TO_EMBEDDED_TYPES)


src_files = os.listdir(path + "/rosserial_esp32/include/")
for f in src_files:
    if f.endswith(".cpp"):
        shutil.move(path + "/rosserial_esp32/include/" + f, path + "/rosserial_esp32/")

