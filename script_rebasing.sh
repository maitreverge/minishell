#! /bin/sh

git switch solving_master
git rebase master
git push
git switch norm_flo
git rebase master
git push
git switch glambrig
git rebase master
git push
git switch flo_branch
git rebase master
git push
git switch master







