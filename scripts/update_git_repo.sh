#!/bin/bash
#This is a base script than can be used to update a whole bunch of repos using a loop etc.

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

git_repo_path=""

if ! cd "$git_repo_path"; then
    echo -e "${RED}Couldn't go to the haru reception package path ${NC}"
    exit
fi

git fetch

if git checkout master; then
    echo "Checked out to master branch"
    if git pull; then
        echo -e "${GREEN}Changes pulled sucessfully from remote master. Your package $git_repo_path is up-to-date ${NC}"
    else
        echo -e "${RED}Couldn't pull changes!! Your package $git_repo_path is not up to date!${NC}"
    fi
else
    echo -e "${RED}Couldn't check out to master branch!${NC}"
    echo -e "${RED}It seems you have changes not committed in your local repo. Commit or stash them and relaunch script!${NC}"
fi
