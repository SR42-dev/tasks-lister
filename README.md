# tasks-lister
A kernel module that prints all the tasks currently existing on the system from init in a tree structure.

Steps to execute :

cd <directory of project.c>

make				# make module

insmod project.ko		# install module

dmesg				# show message

rmmod project 			# remove module

dmesg				# show message

dmesg -C			# clear message

Reference : https://github.com/lukyth/tasks-lister
