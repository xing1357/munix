#!/bin/sh
find . -type f -execdir cat {} \; | wc -l
