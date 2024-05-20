#!/bin/bash

message=""

git update-index --refresh

if [ $(git symbolic-ref --short HEAD) = 'develop' ];
then
    on_dev="Yes"
else
    on_dev="No"
    message="$message Make sure you are committing onto a branch named 'develop'\n"
fi

num_untrack=`git status --porcelain 2>/dev/null| grep "^??" | wc -l`
if [ $num_untrack -gt 0 ];
then
    message="$message Make sure all files you want to submit are added and committed to git\n"
fi

git diff --cached --quiet
if [ $? -ne 0 ];
then
    dirty="Yes"
    message="$message Some modifications to tracked files have not been committed\n"
else
    dirty="No"
fi

remote_status=$(git push -n --porcelain origin develop)
if [[ $remote_status = *"[up to date]"* ]];
then
    remote_utd="Yes"
else
    remote_utd="No"
    message="$message You have commits that are no pushed to github, please push\n"
fi

if [ -e latest-file.info ];
then
    ex1="Yes "
else
    ex1=" No "
    message="$message Can't find file for exercise 1, check spelling and location\n"
fi

if [ -e count.info ];
then
    ex2="Yes "
else
    ex2=" No "
    message="$message Can't find file for exercise 2, check spelling and location\n"
fi

if [ -e ls.info ];
then
    ex3="Yes "
else
    ex3=" No "
    message="$message Can't find file for exercise 3, check spelling and location\n"
fi

if [ -e find.info ];
then
    ex4="Yes "
else
    ex4=" No "
    message="$message Can't find file for exercise 4, check spelling and location\n"
fi

if [ -e taskmanager.info ];
then
    ex5="Yes "
else
    ex5=" No "
    message="$message Can't find file for exercise 5, check spelling and location\n"
fi

if [ -e report/main.tex ];
then
    exr="Yes "
    pdflatex -halt-on-error -interaction=batchmode report/main.tex -output-directory=/dev/null &>/dev/null
    if [ $? -ne 0 ];
    then
        exr_value="Latex Build Failure - check main.tex!"
        message="$message Report failed to build!\n"
    else
        exr_value="Latex Built Successfully"
    fi
else
    exr=" No "
    message="$message Can't find file for the report, check spelling and location\n"
fi

lab_url=$(git remote get-url origin | cut -d'/' -f 5)
lab_url=${lab_url:0:-4}

read -p 'Paste Token again: ' token
# Get the number of open pull requests via Github's REST API
PR_jason=$(curl -s -L \
  -H "Accept: application/vnd.github+json" \
  -H "Authorization: Bearer $token" \
  -H "X-GitHub-Api-Version: 2022-11-28" \
  https://api.github.com/repos/AERE-361/$lab_url/pulls)

open_PRs=$(echo "$PR_jason" | grep -o "\"state\": \"open\"" | wc -l)
if [ $open_PRs != "1" ];
then
    message="$message Incorrect number of open Pull Requests \n"
    pr="Not open"
else
    pr="open"
fi

printf "|--------------------------------------------\n"
printf "| Aer E 361: Lab 2 Submission Assistant\n"
printf "|--------------------------------------------\n"
printf "| On Develop Branch?  | $on_dev\n"
printf "| Untracked Files?    | $num_untrack \n"
printf "| Uncommitted changes?| $dirty \n"
printf "| Remote up-to-date?  | $remote_utd \n"
printf "|--------------------------------------------\n"
printf "|--------------------------------------------\n"
printf "| Ex. # | Found? | Value (if applicable)\n"
printf "|-------|--------|---------------------------\n"
printf "|   1   |  $ex1  | $exn_val \n"
printf "|   2   |  $ex2  | $exn_val \n"
printf "|   3   |  $ex3  | $exn_val \n"
printf "|   4   |  $ex4  | $exn_val \n"
printf "|   5   |  $ex5  | $exn_val \n"
printf "| Rprt. |  $exr  | $exn_val \n"
printf "|--------------------------------------------\n"
printf "|  PR?  | $pr \n"
printf "\n\n\n$message"
