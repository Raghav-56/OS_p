#!/bin/bash

read -p "Enter first number (x): " x
read -p "Enter second number (y): " y

z=$((x + y))

echo "The sum of $x and $y is: $z"
