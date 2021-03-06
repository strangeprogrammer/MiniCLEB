#!/usr/bin/env python3

# Copyright (C) 2020 Stephen Fedele <32551324+strangeprogrammer@users.noreply.github.com>
# See the file 'LICENSE.txt' for licensing information of this file.

### Imports

import os
import setuptools
from setuptools import Extension, Command, find_packages
from setuptools.command.build_ext import build_ext
from setuptools.command.build_py import build_py
from distutils.command.clean import clean

### Global Variables

projroot = os.path.dirname(__file__) + "/"
src = projroot + "MiniCLEB/"

### Build Management

# This is necessary since otherwise python wrapper files created by 'build_ext' and SWIG won't be included in the final product due to 'setuptools' mis-ordering sub-commands and missing the auto-generated python files
# https://stackoverflow.com/questions/50239473/building-a-module-with-setuptools-and-swig#50370153
class build_py_wrap(build_py):
	def run(self):
		self.run_command("build_ext")
		super().run()

### Useful Commands

class clean_wrap(clean):
	"""Cleanup all files generated by SWIG in the './MiniCLEB/' directory."""
	
	def run(self):
		print("removing temporary SWIG files")
		os.system("rm -f " + src + "_MiniCLEB_wrap.c")
		os.system("rm -f " + src + "MiniCLEB.py")
		print("removing dist-ish files")
		os.system("rm -rf " + projroot + "dist/")
		os.system("rm -rf " + projroot + "MiniCLEB.egg-info/")
		super().run()

### Setup

with open(projroot + "README.md", "r") as README:
	setuptools.setup(
		name = "MiniCLEB",
		version = "0.0.2",
		author = "strangeprogrammer",
		author_email = "32551324+strangeprogrammer@users.noreply.github.com",
		description = "Limited 'int'to 'LEB128' converter for 'python' using a 'C' backend.",
		long_description = README.read(),
		long_description_content_type = "text/markdown",
		url = "https://www.github.com/strangeprogrammer/MiniCLEB",
		ext_modules = [
			Extension("_MiniCLEB", [
				src + "_MiniCLEB.c",
				src + "_MiniCLEB.i",
			]),
		],
		cmdclass = {
			"build_py": build_py_wrap,
			"clean": clean_wrap,
		},
		packages = ["MiniCLEB"],
		package_dir = {"": projroot},
		python_requires = ">=3.0",
	)
