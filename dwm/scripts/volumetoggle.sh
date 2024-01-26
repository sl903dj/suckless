#!/bin/bash

# 只静音 Master，不静音Speaker
# amixer -q sset Master toggle
# amixer -q sset Speaker unmute

# 不静音Master，切换Speaker
amixer -q sset Master unmute
amixer -q sset Speaker toggle
amixer -q sset Headphone toggle
