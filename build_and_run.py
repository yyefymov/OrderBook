#!/usr/bin/env python3

import os
import platform
import argparse

# TODO: add option to run a clean build (remove the existing container and start the new one)


def check_image_exists(tag):
	return os.popen("docker images").read().find(tag) != -1

def get_source_dir():
	if platform == "Linux":
		return os.popen("echo ${pwd}").read()[:-1]
	if platform == "Windows":
		return os.popen("echo %cd%").read()[:-1]
	print("Unknown platform")
	return None

parser = argparse.ArgumentParser(description="Build the OrderBook application and run tests in the container")
image_tag = "qt-orderbook"
cont_name = "orderbook_tests"
platform = platform.system()

# add arguments
parser.add_argument("-r", "--rebuild", action="store_true", help="Rebuild the image")
parser.add_argument("-s", "--silent", action="store_true", help="Hide the build output")
parser.add_argument("-c", "--clean", action="store_true", help="Remove the existing container and start a new one")

# parse arguments
args = parser.parse_args()
rebuild = args.rebuild
silent_build = args.silent
clean_build = args.clean

if platform != "Windows" and platform != "Linux":
	print("Platform {} is not supported".format(platform))
	exit()

# check if qt-orderbook exists; if not - build
if rebuild or check_image_exists(image_tag) == False:
	print("Building image")
	os.system("docker build -t {} .".format(image_tag))
	os.system("docker image prune -f") # remove dangling images

if check_image_exists(image_tag) == False:
	print("Failed to build image. Check the Dockerfile for errors")
	exit()

# start the stopped container (or run a new one)
source_dir = get_source_dir()

cont_id = os.popen('docker ps -aqf "name={}"'.format(cont_name)).read()[:-1]
if clean_build or not cont_id:
	print("Clean build")
	os.system("docker container prune -f")
	cont_id = os.popen("docker run -itd --name={} --mount type=bind,source={},dst=/tmp/OrderBook/source,readonly {}".format(cont_name, source_dir, image_tag)).read()[:-1]
else:
	os.system("docker start {}".format(cont_name))
build_dir = os.popen("docker exec {} printenv BUILD_DIR".format(cont_id)).read()[:-1]

print("Container ID is", cont_id)

# build
print("Start build")
make_args = "> ./log_file" if silent_build else ""
error_code = os.system('docker exec -it {} bash -c "cd $BUILD_DIR && qmake -makefile $SOURCE_DIR && make {} 2>&1"'.format(cont_id, make_args))
if error_code:
	print("Build failed")
	if silent_build:
		os.system('docker exec {} bash -c "cat $BUILD_DIR/log_file"'.format(cont_id))
	os.system('docker stop {}'.format(cont_id))
	exit()	
print("Build is successful")

# run
print("Run tests")
os.system('docker exec -it {} {}/OrderBook'.format(cont_id, build_dir))

# cleanup
os.system('docker stop {}'.format(cont_id))