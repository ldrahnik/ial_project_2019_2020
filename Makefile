# Name: Drahník Lukáš
# Project: IAL: náhradní projekt: 2. Hamiltonova cesta a cyklus v grafu
# Date: 20.10.2019
# Email: <xdrahn00@stud.fit.vutbr.cz>
# File: Makefile

################# PROJECT #########################

P_NAME = hpac
P_DOC = doc/hamilton_path_doc.pdf
P_DOC_SOURCE = doc/hamilton_path_doc.tex
P_DOC_MAKEFILE = doc/Makefile
P_SOURCES = src/*.c
P_HEADERS = src/*.h
P_TESTS = tests/tests.sh tests/ref_paths_out/* tests/params_in/* tests/graphs_in/* 
P_TIME_COMPLEXITY = time_complexity/*
P_GRAPHVIZ = graphviz/*

################# FLAGS ###########################

CC = gcc
CFLAGS = -std=gnu99 -Wextra -Werror -pedantic -g -Wall
P_FLAGS = -lm

################# BUILD ###########################

all: $(P_NAME)

$(P_NAME): $(P_SOURCES) $(P_HEADERS)
	$(CC) $(CFLAGS) $(P_SOURCES) -o $(P_NAME) $(P_FLAGS)

################# ARCHIVE #########################

A_NAME = xdrahn00
A_FILES = Makefile $(P_DOC) $(P_DOC_MAKEFILE) $(P_DOC_MAKEFILE) $(P_SOURCES) $(P_HEADERS) $(P_TESTS) $(P_TIME_COMPLEXITY) $(P_GRAPHVIZ)

zip:
	zip $(A_NAME).zip $(A_FILES)

rmzip:
	rm -f $(A_NAME).zip

################### DOC ############################

tex:
	cd doc && make doc

################# TESTS ############################

test: $(P_NAME)
	bash ./tests/tests.sh $(PWD)/$(P_NAME)

################# CLEAN ############################

clean:
	# clean test temporary folders
	rm -rf ./tests/diff ./tests/output

	# clean binary
	rm -f $(P_NAME)

	# clean doc
	cd ./doc/ && make clean
