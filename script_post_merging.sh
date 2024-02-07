#! /bin/sh

git switch master
git pull origin master
git push

git switch glambrig
git pull origin glambrig
git push

git switch flo_branch
git pull origin flo_branch
git push

