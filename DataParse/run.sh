#!/bin/bash
#
# A script to compile and run programs for CS 236. See below for options.
#
# AUTHOR: Dan Mercer
#
# Licensed under the MIT license:
#-------------------------------------------------------------------------
#     The MIT License (MIT)
#
#     Copyright (c) 2016 Dan Mercer
#
#     Permission is hereby granted, free of charge, to any person obtaining
#     a copy of this software and associated documentation files (the
#     "Software"), to deal in the Software without restriction, including
#     without limitation the rights to use, copy, modify, merge, publish,
#     distribute, sublicense, and/or sell copies of the Software, and to
#     permit persons to whom the Software is furnished to do so, subject to
#     the following conditions:
#
#     The above copyright notice and this permission notice shall be
#     included in all copies or substantial portions of the Software.
#
#     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#     EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#     MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
#     IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
#     CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
#     TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
#     SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#-------------------------------------------------------------------------
#
# OPTIONS:
#		-d Debug with GDB
#		-c Compile, but don't run.
#		-n Don't recompile; use the existing compilation of program
#		-p Run complexity test (doesn't compile unless -c is specified)
#		-v Run in Valgrind, to test complexity
#		-z Compile, test complexity, and zip for submission. (Deletes any old zip file and increments the number)
#
#	Enjoy!

# =========== TWEAKABLE VARIABLES ==========

# A suffix that is appended to the generated zip files:
nameSuffix="_$USER" # change this to whatever you want. E.g. "_yournamehere"

# A pattern that matches all desired input files:
input='*.txt'

# A pattern or listing of files to display complexity readouts for:
filesToCheckComplexity='*.h *.cpp'

# =========================================

# Default options
debug=0
onlyCompile=0
noRecompile=0
testComplex=0
runValgrind=0
zipForSubmission=0

# Get options
while getopts 'dcnpvz' flag; do
	case "${flag}" in
		d) debug=1 ;;
		c) onlyCompile=1 ;;
		n) noRecompile=1 ;;
		p) testComplex=1 ;;
		v) runValgrind=1 ;;
		z) zipForSubmission=1 ;;
		*) echo "Unexpected option ${flag}"; exit ;;
	esac
done

# Prepare name of zip file
if [ $zipForSubmission -eq 1 ]; then
	labNum=$(echo "$PWD" | grep -oE "lab[0-9]" | grep -oE "[0-9]")
	previousZip=$(ls -1 | grep -m 1 -E "lab${labNum}${nameSuffix}[0-9]+\.zip")
	if [ -n "$previousZip" ]; then
		# Get previous submission number
		subNum=$(echo "$previousZip" | grep -oE [0-9]+\\. | grep -oE [0-9])
		# increment number
		subNum=$((subNum + 1));
	else
		subNum=0
	fi
	# Create new zip name
	zipName="lab${labNum}${nameSuffix}${subNum}.zip"
	echo "Preparing for zip to: $zipName"
fi

# Option safety checking
if [ $noRecompile -eq 1 ]
then
	if [ $onlyCompile -eq 1 \
		-o $zipForSubmission -eq 1 ]
	then

		echo "-n and -c or -z are mutually exclusive."
		exit
	fi
fi
if [ $testComplex -eq 1 \
	-a $onlyCompile -eq 0 ]
then
	noRecompile=1 # Don't recompile when checking complexity (unless -c is specified)
fi

# ============ COMPILATION =====================

if [ $noRecompile -eq 1 ]; then
	# Assert that a program already exists
	if [ ! -x program ]; then
		echo "Existing program not found"
		exit
	fi
	echo "Using existing program, compiled at" $(stat -c %y program | awk -F "[ .]" '{printf $2 "\n" }')
else
	# Remove the old program if it exists
	if [ -x program ]
	then
		rm program
	fi
	# Compile the new program
	echo "Compiling..."
	g++ -g -Wall -fmax-errors=1 -std=c++11 *.cpp -o program

	# Check compilation
	if [ ! -x program ]
	then
		# Program not compiled properly
		echo "!!! Program didn't compile."
		exit
	fi

	# Tell the user it successfully compiled
	echo "Compilation successful!"

fi

# ============= COMPLEXITY TESTING ===============

if [ $testComplex -eq 1 \
	-o $zipForSubmission -eq 1 ]
then
	# Default setting for $filesToCheckComplexity:
	if [ -z "$filesToCheckComplexity" ]; then
		filesToCheckComplexity='*.cpp *.h'
	fi
	# Run complexity test
	badComplexities=$(pmccabe *.cpp *.h | grep -E "^([9]|[1-9][1-9]+)")
	if [ -n "$badComplexities" ]
	then
		echo "COMPLEXITY PROBLEMS:"
		echo "$badComplexities"
		exit
	else
		if [ $testComplex -eq 1 ]; then
			# Show complexity results
			pmccabe $filesToCheckComplexity | sort -n # sort Numerically
		fi
		echo "Complexity looks good!"
	fi

	if [ $testComplex -eq 1 \
		-a $zipForSubmission -eq 0 ]
	then
		exit # exit for -p parameter if -z is absent
	fi
fi

# ============= ZIP FOR SUBMISSION ================

if [ $zipForSubmission -eq 1 ]
then
	echo "ZIPPING TO: $zipName"
	zip "$zipName" *.h *.cpp *.txt run.sh
	exit
fi


# Exit at this point for -c parameter
if [ $onlyCompile -eq 1 ]
then
	exit
fi

# ================ RUN / DEBUG ====================

# Helper function
runFunc () {
	echo "~~~ PROGRAM START: $1 ~~~"
	./program $1
	echo "~~~ PROGRAM END: $1 ~~~"
}

# Run the program
if [ $debug -eq 1 \
	-o $runValgrind -eq 1 ]; then
	# Get the first input file
	input=$(ls -1d $input | head -n 1);
	if [ $debug -eq 1 ] ; then
		if [ -z $(which gdb) ]; then
			echo "ERROR: GDB is not installed."
			exit
		fi
		# Debug the program with that input file
		echo "~~~ DEBUG START: $input ~~~"
		gdb program -q -ex "run \"$input\""
		echo "~~~ DEBUG END ~~~"
	else
		# Valgrind the program!
		if [ -z $(which valgrind) ]; then
			echo "ERROR: Valgrind is not installed. Maybe try running 'apt-get install valgrind'?"
			exit
		fi
		echo "~~~ VALGRIND START: $input ~~~"
		valgrind ./program $input
		echo "~~~ VALGRIND END ~~~"
	fi
else
	for file in $input ; do
		runFunc $file
	done
fi
