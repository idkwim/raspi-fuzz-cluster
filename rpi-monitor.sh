#!/bin/bash

tmux split-window -h -c '#{pane_current_path}' 'mosh rpi3-1'
tmux split-window -v -c '#{pane_current_path}' 'mosh rpi3-2'
tmux select-pane  -L
tmux split-window -v -c '#{pane_current_path}' 'mosh rpi2-2'
tmux select-pane  -U
mosh rpi2-1
