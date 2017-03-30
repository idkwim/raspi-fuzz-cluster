HISTCONTROL=ignoreboth
shopt -s histappend
HISTSIZE=1000
HISTFILESIZE=2000

shopt -s checkwinsize

export PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w \$\[\033[00m\] '
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH=}:/usr/local/lib
export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'
export PATH=$PATH:$HOME/bin

alias ls='/bin/ls --color=always --group-directories-first'
alias l='ls'
alias ll='l -l --human-readable'
alias a='ll --all'
alias gdb="gdb -q"
