#!/bin/bash
url="$1"
word="$2"

wget -r $url | grep $word >> word.txt
echo $word
