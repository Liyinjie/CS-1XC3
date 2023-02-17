#!/bin/bash

# Use First Argument As Working Directory
WDIR="$1"
cd "$WDIR"
FILENAME="file1.txt"
if [ "$3" ]; then
    FILENAME="$3"
fi
if [ "$2" -eq 1 ] ; then
    if [ ! -f "$FILENAME" ]; then
        touch "$FILENAME"
        echo $USER > "$FILENAME"
    fi
elif [ "$2" -eq 2 ] ; then
    if [ -f "$FILENAME" ]; then
        if [ ! -d "backup" ]; then
            mkdir backup
        fi
        cp "$FILENAME" backup/
    fi
elif [ "$2" -eq 3 ] ; then
      if [ -f "backup/$FILENAME" ]; then
          cp "backup/$FILENAME" "$FILENAME"
          rm "backup/$FILENAME"
      fi
fi
if [ "$#" -gt 3 ]; then
    echo "${@:4}" > excess.txt
fi
echo "Finished"
