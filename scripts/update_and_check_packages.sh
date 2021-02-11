#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

force_install_package_list=""
skip_pkg_list=""
user=""

if [ "$USER" = "$user" ]; then
    echo -e "${RED}You must run this script on the external PC ${NC}"
    exit
fi

echo "Performing apt update... "

if ! sudo apt update &>/dev/null; then
    echo -e "${RED}There was a problem performing apt update! Error $? ${NC}"
    exit
fi

#This should be changed depending on the repo you want to iterate
avaiable_pkgs=$(grep ^Package: /var/lib/apt/lists/robotics.upo.es_repos_apt_haru_dists_"$(lsb_release -c -s)"*_Packages | awk '{gsub("Package: ", "");print}')

#If you are installing local debian files
for i in $avaiable_pkgs; do
    
    if [[ "$skip_pkg_list" =~ $i ]]; then
        continue
    fi

    if [ "$(dpkg -s "$i" 2>/dev/null | grep "Status" | awk '{print $4}')" = "installed" ] || [[ "$force_install_package_list" =~ $i ]]; then
        
        installed_version=$(apt-cache policy "$i" | grep Installed | awk '{print $2}')
        candidate_version=$(apt-cache policy "$i" | grep Candidate | awk '{print $2}')
        #If you are using local debians instead of remote apt installed debians:
        #candidate_version=$(dpkg-deb -I ./debians/"$i"_* | grep Version |  awk '{print $2}' )

        if [ "$installed_version" != "$candidate_version" ]; then
            echo -e "${GREEN}Updating $i from $installed_version to $candidate_version...${NC}"

            if ! sudo apt install "$i" -y &>/dev/null; then
                echo -e "${RED}There was a problem detected updating $i, Error $?  !!!${NC}"
            fi
            
            installed_version=$(apt-cache policy "$i" | grep Installed | awk '{print $2}')
            
            if [ "$installed_version" != "$candidate_version" ]; then
                echo -e "${RED}There was an error updating package $i, installed and candidate version does not match!${NC}"
            fi

        else
            echo "Skipping $i update, current version ($installed_version) is the latest available"
        fi
    fi
done
