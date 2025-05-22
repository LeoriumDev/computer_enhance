#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <number>"
    exit 1
fi

MAX_SET="$1"

gcc decoder.c -o decoder || { echo "Failed to compile decoder.c"; exit 1; }

get_prefixes_for_set() {
    case "$1" in
        1) echo "listing_0037 listing_0038" ;;
        2) echo "listing_0039 listing_0040" ;;
        3) echo "listing_0051 listing_0061" ;;
        4) echo "listing_0062 listing_0063" ;;
    esac
}

echo

for (( i=1; i<=MAX_SET; i++ )); do
    PREFIXES=$(get_prefixes_for_set "$i")
    echo "Running Test Set $i ($PREFIXES)"

    if [ -z "$PREFIXES" ]; then
        echo "No prefixes defined for test set $i"
        continue
    fi

    for prefix in $PREFIXES; do
        for file in ${prefix}*; do
            [ ! -f "$file" ] && continue

            if [[ "$file" == *.* ]]; then
                continue
            fi

            ./decoder "$file" > tmp.asm
            nasm -f bin tmp.asm -o tmp_out.bin || {
                echo
                echo "❌ NASM failed on $file";
                echo
                rm tmp.asm;
                continue;
            }

            xxd "$file" > orig.hex
            xxd tmp_out.bin > out.hex

            if diff -q orig.hex out.hex > /dev/null; then
                echo "✅ $file matches"
            else
                echo "❌ $file does NOT match"
                echo "🔍 Showing differences:"
                grep -v '^\s*;' tmp.asm | grep -v '^\s*$' > tmp_clean.asm
                grep -v '^\s*;' "$file.asm" | grep -v '^\s*$' > file_clean.asm
                diff -u file_clean.asm tmp_clean.asm | head -20
                rm -f tmp_clean.asm file_clean.asm
            fi
            
            rm -f orig.hex out.hex

            rm -f tmp.asm tmp_out.bin
        done
    done

    echo
done

rm decoder