#!/bin/bash

tmux split-window -h -c '#{pane_current_path}' 'ssh -t rpi3-1 "htop --user=pi"'
tmux split-window -v -c '#{pane_current_path}' 'ssh -t rpi3-2 "htop --user=pi"'
tmux select-pane  -L
tmux split-window -v -c '#{pane_current_path}' 'ssh -t rpi2-2 "htop --user=pi"'
tmux select-pane  -U
ssh -t rpi2-1 "htop --user=pi"
