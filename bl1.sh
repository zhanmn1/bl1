#!/bin/sh

qemu-system-arm -M beagle -mtdblock bl1.bin -serial stdio
