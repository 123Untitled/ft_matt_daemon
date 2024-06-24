#!/usr/bin/env -S zsh --no-rcs --no-globalrcs


# launch 6 tmux panes in a 2x3 grid
tmux new-session -d -s mysession

tmux split-window -v
tmux split-window -v
tmux split-window -h
tmux split-window -h


tmux select-layout tiled


# attach to the session
tmux attach-session -t mysession

