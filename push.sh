#!/bin/bash

# Add all files in the current directory
git add .

# Commit with a default message (you can modify or pass as argument)
git commit -m "commit"

# Push changes to the remote 'main' branch
git push origin main
